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

#include "ammeter.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define AMMETER_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void ammeter_generic_transfer ( ammeter_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

static void ammeter_calc_delay ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ammeter_cfg_setup ( ammeter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

AMMETER_RETVAL ammeter_init ( ammeter_t *ctx, ammeter_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = AMMETER_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
    {
        return AMMETER_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, AMMETER_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    return AMMETER_OK;
}

uint16_t ammeter_data_read ( ammeter_t *ctx )
{
    uint8_t rx_buf[ 2 ];
	uint16_t result;

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
	result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    
    return result;
}

uint16_t ammeter_get_raw_data ( ammeter_t *ctx )
{
    uint16_t result = 0;

    result = ammeter_data_read( ctx );
    result &= AMMETER_FILTER_USEFULL_DATA;
    result >>= 1;

    return result;
}

float ammeter_get_avg_data ( ammeter_t *ctx )
{
    uint16_t temp;
    float sum = 0;
    float result;
    uint8_t n_cnt;
    

    for ( n_cnt = 0; n_cnt < AMMETER_SAMPLE_NUM; n_cnt++ )
    {
        temp = ammeter_get_raw_data( ctx );
        ammeter_calc_delay( );
        sum += temp;
    }

    sum /= AMMETER_SAMPLE_NUM;
    result = sum / AMMETER_STABULISATION_COEF;

    return result;
}

float ammeter_amperage ( ammeter_t *ctx )
{
    float result;
    
    result = ammeter_get_avg_data(ctx);
    result -= AMMETER_CALC_COEF;

    return result;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void ammeter_generic_transfer ( ammeter_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

static void ammeter_calc_delay ( )
{
    Delay_10ms();
}

// ------------------------------------------------------------------------- END

