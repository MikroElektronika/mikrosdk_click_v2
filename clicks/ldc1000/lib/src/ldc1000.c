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

#include "ldc1000.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LDC1000_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ldc1000_cfg_setup ( ldc1000_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

LDC1000_RETVAL ldc1000_init ( ldc1000_t *ctx, ldc1000_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = LDC1000_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return LDC1000_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, LDC1000_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LDC1000_OK;
}

void ldc1000_default_cfg ( ldc1000_t *ctx )
{
    ldc1000_write_byte( ctx, LDC1000_CMD_RPMAX, LDC1000_RPMAX_38_785K );
    ldc1000_write_byte( ctx, LDC1000_CMD_RPMIN, LDC1000_RPMIN_2_39K );
    ldc1000_write_byte( ctx, LDC1000_CMD_SENSORFREQ, LDC1000_SENSORFREQ_N217_F20 );
    ldc1000_write_byte( ctx, LDC1000_CMD_LDCCONFIG, LDC1000_LDCCONFIG_A2V_T6144 );
    ldc1000_write_byte( ctx, LDC1000_CMD_CLKCONFIG, LDC1000_CLKCONFIG_EC_ET_ENABLE );
    ldc1000_write_byte( ctx, LDC1000_CMD_PWRCONFIG, LDC1000_PWRCONFIG_ACTIVE_MODE );
}

void ldc1000_write_byte ( ldc1000_t *ctx, uint8_t address, uint8_t input_data )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &address, 1 );
    spi_master_write( &ctx->spi, &input_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t ldc1000_read_byte ( ldc1000_t *ctx, uint8_t address )
{
    uint8_t output_data;
    uint8_t tmp;

    spi_master_select_device( ctx->chip_select );
    tmp = address | LDC1000_CMD_SPI_READ;
    spi_master_write( &ctx->spi, &tmp, 1 );
    spi_master_read( &ctx->spi, &output_data, 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    return output_data;
}

uint16_t ldc1000_get_proximity_data ( ldc1000_t *ctx )
{
    uint16_t output_data;

    output_data = ldc1000_read_byte( ctx, LDC1000_CMD_PROXMSB | LDC1000_CMD_SPI_READ );
    output_data <<= 8;
    output_data |= ldc1000_read_byte( ctx, LDC1000_CMD_PROXLSB | LDC1000_CMD_SPI_READ );
    
    return output_data;
}

float ldc1000_get_inductance_data ( ldc1000_t *ctx )
{
    uint32_t value_frequency_count;
    float function_frequency_count;
    float output_data;

    value_frequency_count = ldc1000_read_byte( ctx, LDC1000_CMD_FREQCTRMSB |
                                                    LDC1000_CMD_SPI_READ );
    value_frequency_count <<= 8;
    value_frequency_count |= ldc1000_read_byte( ctx, LDC1000_CMD_FREQCTRMID | 
                                                    LDC1000_CMD_SPI_READ );
    value_frequency_count <<= 8;
    value_frequency_count |= ldc1000_read_byte( ctx, LDC1000_CMD_FREQCTRLSB | 
                                                    LDC1000_CMD_SPI_READ );

    function_frequency_count = ( 1.0 / 3.0 ) * ( 8000000.0 /
                             ( ( float ) value_frequency_count ) ) * 6144.0;
    
    output_data = 1000000.0 / ( 0.0000000001 * pow( 2.0 * 3.14 * function_frequency_count, 2 ) );                                        
    return output_data;
}

uint8_t ldc1000_get_int_input ( ldc1000_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
