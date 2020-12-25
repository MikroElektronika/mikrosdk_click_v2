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

#include "stepup.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define STEPUP_DUMMY                0

#define STEPUP_DAC_RESOLUTION       4095

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stepup_cfg_setup ( stepup_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mod = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->dac_config.buf  = STEPUP_CFG_VREF_BUFFERED;
    cfg->dac_config.ga   = STEPUP_CFG_GAIN_1X;
    cfg->dac_config.shdn = STEPUP_CFG_POWER_OUT_ON;

}

STEPUP_RETVAL stepup_init ( stepup_t *ctx, stepup_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = STEPUP_DUMMY;

    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return STEPUP_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, STEPUP_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // Output pins 
    
    digital_out_init( &ctx->mod, cfg->mod );
    digital_out_init( &ctx->en, cfg->en );

    digital_out_high( &ctx->mod );
    digital_out_high( &ctx->en );

    ctx->dac_config.buf  = cfg->dac_config.buf;
    ctx->dac_config.ga   = cfg->dac_config.ga;
    ctx->dac_config.shdn = cfg->dac_config.shdn;

    return STEPUP_OK;

}

void stepup_default_cfg ( stepup_t *ctx )
{
    // Click default configuration 
    digital_out_low( &ctx->mod );
    digital_out_high( &ctx->en );

    ctx->dac_config.buf  = STEPUP_CFG_VREF_BUFFERED;
    ctx->dac_config.ga   = STEPUP_CFG_GAIN_1X;
    ctx->dac_config.shdn = STEPUP_CFG_POWER_OUT_ON;
}

void stepup_mod_set ( stepup_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->mod, pin_state );
}

void stepup_en_set ( stepup_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->en, pin_state );
}

void stepup_dac_setup ( stepup_t *ctx, stepup_dac_cfg_t *cfg )
{
    ctx->dac_config.buf  = cfg->buf;
    ctx->dac_config.ga   = cfg->ga;
    ctx->dac_config.shdn = cfg->shdn;
}

err_t stepup_dac_write ( stepup_t *ctx, uint16_t dac_val )
{
    if ( dac_val > STEPUP_DAC_RESOLUTION )
    {
        return STEPUP_ERROR;
    }

    uint8_t write_buf[ 2 ];

    write_buf[ 0 ] = dac_val >> 8;
    write_buf[ 1 ] = dac_val;

    write_buf[ 0 ] |= ( ctx->dac_config.buf & 1 ) << 6;
    write_buf[ 0 ] |= ( ctx->dac_config.ga & 1 ) << 5;
    write_buf[ 0 ] |= ( ctx->dac_config.shdn & 1 ) << 4;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, write_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );  

    return STEPUP_OK;
}

err_t stepup_set_percentage ( stepup_t *ctx, float percentage )
{
    uint16_t setter = 0;
    float temp = 0.0;
    
    if ( ( percentage > 100.0 ) || ( percentage < 0.0 ) )
        return STEPUP_ERROR;
    
    temp = ( percentage * STEPUP_DAC_RESOLUTION ) / 100.0;
    
    setter = STEPUP_DAC_RESOLUTION - ( uint16_t )temp;
    
    stepup_dac_write( ctx, setter );
    
    return STEPUP_OK;
}

// ------------------------------------------------------------------------- END

