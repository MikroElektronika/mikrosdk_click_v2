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

#include "adc2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADC2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc2_cfg_setup ( adc2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000;
}

ADC2_RETVAL adc2_init ( adc2_t *ctx, adc2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ADC2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ADC2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    return ADC2_OK;

}

void adc2_generic_transfer ( adc2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );    
}

uint32_t adc2_read_4bytes ( adc2_t *ctx )
{
    uint8_t read_reg[ 4 ];
    uint32_t result;

    result = 0x00000000;

    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_read( &ctx->spi, read_reg, 4 );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms( );

    result = read_reg[ 0 ];
    result <<= 8;
    result |= read_reg[ 1 ];
    result <<= 8;
    result |= read_reg[ 2 ];
    result <<= 8;
    result |= read_reg[ 3 ];
    
    result >>= 7;

    return result;
}

uint32_t adc2_adc_value_read ( adc2_t *ctx )
{
    uint32_t result;
    result = adc2_read_4bytes( ctx );

    while ( result >= 0x01FFFFFF )
    {
        result = adc2_read_4bytes( ctx );
        Delay_10us( );
    }
    result &= 0x003FFFFF;

        if ( result > 0x1FFFFF )
        {
            result = ~result;
            result *= -1;
        }

    return result;
}

uint8_t adc2_check_over_low ( adc2_t *ctx )
{
    uint32_t check;
    uint8_t result;

    check = adc2_read_4bytes( ctx );
    
    check >>= 23;
    result = ( uint8_t ) check ;
    result &= 0x01;

    return result;
}

uint8_t adc2_check_over_high ( adc2_t *ctx )
{
    uint32_t check;
    uint8_t result;

    check = adc2_read_4bytes( ctx );

    check >>= 22;
    result = ( uint8_t ) check ;
    result &= 0x01;

    return result;
}
// ------------------------------------------------------------------------- END

