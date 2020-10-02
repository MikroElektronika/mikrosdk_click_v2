/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "voltmeter.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define VOLTMETER_DUMMY 0

void voltmeter_cfg_setup ( voltmeter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

VOLTMETER_RETVAL voltmeter_init ( voltmeter_t *ctx, voltmeter_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = VOLTMETER_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return VOLTMETER_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, VOLTMETER_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 

    digital_out_high( &ctx->cs );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );

    return VOLTMETER_OK;
}

void voltmeter_generic_transfer 
( 
    voltmeter_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void voltmeter_write_data ( voltmeter_t *ctx, uint16_t write_data )
{
    uint8_t buffer[ 2 ];

     buffer[ 1 ] = ( uint8_t ) ( write_data & VOLTMETER_VALUE_5_BIT );
     buffer[ 0 ] = write_data  >> 7;

    voltmeter_generic_transfer( ctx, buffer, 2, 0, 0 ); 
}

uint8_t voltmeter_read_byte ( voltmeter_t *ctx )
{
    uint8_t buffer[ 1 ];

    voltmeter_generic_transfer ( ctx, 0, 0,  buffer, 1 );
    
    return buffer[ 0 ];
}

uint16_t voltmeter_read_data ( voltmeter_t *ctx )
{
    uint16_t result;
    uint8_t buffer[ 2 ];

    result = 0;

    voltmeter_generic_transfer ( ctx, 0, 0, buffer, 2 );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];
    result >>= 1;
    result &= VOLTMETER_VALUE_12_BIT;

    return result;
}

void voltmeter_calibration ( voltmeter_t *ctx )
{
    uint16_t read_adc;
    uint8_t cnt;
    float calibration;

    read_adc = 0;
    
    for ( cnt = 0; cnt < 10; cnt++ )
    {
        read_adc = voltmeter_read_data( ctx );
    }
    
    calibration = ( float ) read_adc;
}

float voltmeter_get_voltage ( voltmeter_t *ctx, uint8_t coefficient )
{
    float voltage;
    float sum;
    uint16_t adc_value;
    uint8_t cnt;
    float calibration;
    
    sum = 0;

    for ( cnt = 0; cnt < 10; cnt++ )
    {
        adc_value = voltmeter_read_data( ctx );
        sum += ( float ) adc_value;
        sum -= calibration;
    }

    voltage = sum / 10.0;

    if ( coefficient == VOLTMETER_VCC_5V_COEFF_0 )
    {
        voltage *= VOLTMETER_VCC_5V_COEFF_VAL;
    }
    else if ( coefficient == VOLTMETER_VCC_5V_COEFF_1 )
    {
        voltage *= VOLTMETER_VCC_5V_COEFFICIENT_VAL;
    }
    else if ( coefficient == VOLTMETER_VCC_5V_COEFF_2 )
    {
        voltage *= VOLTMETER_VCC_5V_COEFF_PIC32_VAL;
    }

    return voltage;
}
// ------------------------------------------------------------------------- END

