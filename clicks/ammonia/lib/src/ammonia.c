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

#include "ammonia.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define AMMONIA_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ammonia_cfg_setup ( ammonia_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
     
    // Additional gpio pins

    cfg->pwm = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

AMMONIA_RETVAL ammonia_init ( ammonia_t *ctx, ammonia_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    digital_in_init( &ctx->miso, cfg->miso );
    
    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = AMMONIA_DUMMY;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return AMMONIA_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, AMMONIA_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->pwm, cfg->pwm );

    // Input pins

    return AMMONIA_OK;
}

void ammonia_generic_transfer ( ammonia_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

void ammonia_heater ( ammonia_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->pwm, state );
}

uint32_t ammonia_data_read ( ammonia_t *ctx )
{
    uint8_t rx_buf[ 3 ];
    uint32_t adc_val = 0;

    while ( 1 )
    {
        spi_master_select_device( ctx->chip_select );
        Delay_10us( );
        if ( digital_in_read( &ctx->miso ) == 0 )
        {
            break;
        }
        spi_master_deselect_device( ctx->chip_select ); 
        Delay_1us( );
    }

//     Delay_1ms( );
    
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );
    spi_master_read( &ctx->spi, &rx_buf[ 0 ], 3 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1us( ); 


    adc_val= rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 2 ];
    adc_val &= 0x003FFFFF;

    return adc_val;
}

// ------------------------------------------------------------------------- END

