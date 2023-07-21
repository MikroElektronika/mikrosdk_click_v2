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

#include "rtd.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define RTD_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtd_cfg_setup ( rtd_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->drdy = HAL_PIN_NC;

    cfg->spi_speed = 1000000; 
    cfg->spi_mode = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t rtd_init ( rtd_t *ctx, rtd_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, RTD_DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Input pins
    digital_in_init( &ctx->drdy, cfg->drdy );
    
    return RTD_OK;
}

void rtd_write_register ( rtd_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t tmp[ 2 ] = { 0 };

    tmp[ 0 ] = reg_address | 0x80;
    tmp[ 1 ] = write_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 2 );
    spi_master_deselect_device( ctx->chip_select );    
}

uint8_t rtd_read_register ( rtd_t *ctx, uint8_t reg_address )
{
    uint8_t tmp = 0;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &reg_address, 1, &tmp, 1 );
    spi_master_deselect_device( ctx->chip_select );  

    return tmp;
}

uint16_t rtd_read_temperature ( rtd_t *ctx )
{
    uint16_t raw_temp = 0;

    raw_temp = rtd_read_register( ctx, 0x01 );
    raw_temp <<= 8;
    raw_temp |= rtd_read_register( ctx, 0x02 );

    return raw_temp;
}

float rtd_convert_temperature ( rtd_t *ctx, uint16_t input_data, uint16_t referent_resistance )
{
    float float_value = 0;
    float coefficient = 0;
    coefficient = ( referent_resistance / 400.0 );

    input_data >>= 1;
    float_value = ( float ) input_data * coefficient;
    float_value /= 32;
    float_value -= 256;

    return float_value;
}

// ------------------------------------------------------------------------- END

