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

#include "buck13.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BUCK13_DUMMY         0
#define BUCK13_ADC_RESOL     1024
#define BUCK13_ADC_VREF      4096

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck13_cfg_setup ( buck13_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins

    cfg->en = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

BUCK13_RETVAL buck13_init ( buck13_t *ctx, buck13_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BUCK13_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BUCK13_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BUCK13_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->en, cfg->en );

    return BUCK13_OK;
}

void buck13_default_cfg ( buck13_t *ctx )
{
    buck13_enable( ctx, BUCK13_DISABLE );
    buck13_enable( ctx, BUCK13_ENABLE );
}

void buck13_generic_transfer 
( 
    buck13_t *ctx, 
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

void buck13_enable ( buck13_t *ctx, uint8_t pwr_state )
{
    if ( pwr_state == BUCK13_ENABLE )
    {
        digital_out_write( &ctx->en, 1 );
    }
    else if ( pwr_state == BUCK13_DISABLE )
    {
        digital_out_write( &ctx->en, 0 );
    }
}

uint16_t buck13_get_adc ( buck13_t *ctx )
{

    uint8_t data_out[ 2 ];
    uint16_t ret_val;

   // buck13_generic_transfer( ctx, 0, 0, data_out, 2 );
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, data_out, 2 );
    spi_master_deselect_device( ctx->chip_select );   
    
    ret_val = data_out[ 0 ];
    ret_val <<= 8;
    ret_val |= data_out[ 1 ];
    ret_val >>= 3;
    ret_val &= 0x03FF;
    
    return ret_val;
}

uint16_t buck13_get_voltage ( buck13_t *ctx )
{
    uint16_t adc_data;
    float tmp;
    
    adc_data = buck13_get_adc( ctx );
    
    tmp = adc_data;
    tmp /= BUCK13_ADC_RESOL;
    tmp *= BUCK13_ADC_VREF;
    adc_data = tmp;
    
    return adc_data;
}

// ------------------------------------------------------------------------- END

