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

#include "current.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CURRENT_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void current_cfg_setup ( current_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

CURRENT_RETVAL current_init ( current_t *ctx, current_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = CURRENT_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CURRENT_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CURRENT_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    return CURRENT_OK;
}

uint16_t current_data_read ( current_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t result;

    spi_master_select_device( ctx->chip_select );
    Delay_1ms();
    spi_master_read( &ctx->spi, rx_buf, 2 );
    Delay_1ms();
    spi_master_deselect_device( ctx->chip_select );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    return result;
}

uint16_t current_get_raw_data ( current_t *ctx )
{
    uint16_t result;

    result = current_data_read(ctx );

    result >>= 1;
    result &= CURRENT_FILTER_USEFULL_DATA;

    return result;
}

float current_avg_rata ( current_t *ctx )
{
    uint16_t temp;
    float sum;
    uint8_t n_cnt;
    
    sum = 0;

    for ( n_cnt = 0; n_cnt < CURRENT_SAMPLE_NUM; n_cnt++ )
    {
        temp = current_get_raw_data( ctx );
        Delay_10ms();
        sum += temp;
    }

    sum /= CURRENT_SAMPLE_NUM;

    return sum;
}

float current_get_current_data ( current_t *ctx, float r_shunt )
{
    float result;
    float avg_data;

    avg_data = current_get_raw_data( ctx );

    if( avg_data < RFMETER_DEF_LIMIT_HIGH && avg_data > RFMETER_DEF_LIMIT_LOW )
    {
        result = ( float ) avg_data;
        result *= CURRENT_CAL_COEF;
        result /= r_shunt;
    }
    else
    {
        result = CURRENT_OUT_OF_RANGE;
    }

    return result;
}

// ------------------------------------------------------------------------- END

