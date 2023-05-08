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

#include "accurrent.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCURRENT_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accurrent_cfg_setup ( accurrent_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 1000000; 
}

err_t accurrent_init ( accurrent_t *ctx, accurrent_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ACCURRENT_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) )
    {
        return ACCURRENT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ACCURRENT_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    digital_in_init( &ctx->an, cfg->an );
    spi_master_deselect_device( ctx->chip_select );  

    return ACCURRENT_OK;
}

void accurrent_generic_transfer ( accurrent_t *ctx, uint8_t *wr_buf, uint16_t wr_len, 
                                  uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

float accurrent_get_a ( accurrent_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    float avg = 0;
    uint32_t sum = 0;

    // SPI reading
    for( uint8_t cnt = 0; cnt < ACCURRENT_ADC_ITERATIONS; cnt++ )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_read( &ctx->spi, data_buf, 2 );
        spi_master_deselect_device( ctx->chip_select );
        
        // Sum of the ADC readings
        sum += ( ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) & ACCURRENT_ADC_RESOLUTION ); 
    }
    
    // Average ADC value based on sum of the ADC readings
    avg = ( float ) ( sum / ACCURRENT_ADC_ITERATIONS );
    avg = ( ( avg / ACCURRENT_ADC_RESOLUTION ) / ACCURRENT_AC_TO_DC_V_SCALE ) * ACCURRENT_SENSOR_RESOLUTION;

    return avg; // Returns the average ADC value
}

float accurrent_get_ma ( accurrent_t *ctx )
{
    return accurrent_get_a ( ctx ) * ACCURRENT_A_TO_MA_SCALE;
}

// ------------------------------------------------------------------------- END

