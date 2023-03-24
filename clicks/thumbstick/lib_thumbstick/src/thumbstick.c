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

#include "thumbstick.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define THUMBSTICK_DUMMY    0

#define POSTION_MIDDLE          2047

// ------------------------------------------------------------- PRIVATE VARIABLES

static uint16_t thumbstick_sensitivity = 0;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thumbstick_cfg_setup ( thumbstick_cfg_t *cfg )
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

THUMBSTICK_RETVAL thumbstick_init ( thumbstick_t *ctx, thumbstick_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = THUMBSTICK_DUMMY;

    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return THUMBSTICK_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, THUMBSTICK_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );  

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    thumbstick_sensitivity = POSTION_SENS_DEFAULT;

    return THUMBSTICK_OK;
}

void thumbstick_generic_transfer 
( 
    thumbstick_t *ctx, 
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

uint16_t thumbstick_read_rawadc ( thumbstick_t *ctx, uint8_t type, uint8_t channel )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 2 ];

    uint16_t result;

    result = 0x00;
    tx_buf[ 0 ] = type;
    spi_master_set_default_write_data( &ctx->spi, channel );
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );  
    
    spi_master_set_default_write_data( &ctx->spi, THUMBSTICK_DUMMY );

    result = rx_buf[ 0 ] & 0x0F;
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

uint8_t thumbstick_get_single_axis_postion ( thumbstick_t *ctx, uint8_t axis )
{
    volatile uint16_t adc_raw;

    if ( ( axis != THUMBSTICK_VERTICAL ) && ( axis != THUMBSTICK_HORIZONTAL ) )
    {
        return THUMBSTICK_FUNCTION_ERROR;
    }
    
    adc_raw = thumbstick_read_rawadc( ctx, THUMBSTICK_START_SINGLE_CONV, axis );
    
    if ( axis == THUMBSTICK_VERTICAL )
    {
        if ( adc_raw > ( POSTION_MIDDLE + thumbstick_sensitivity ) )
        {
            return THUMBSTICK_POSITION_BOTTOM;
        }
        else if ( adc_raw < ( POSTION_MIDDLE - thumbstick_sensitivity ) )
        {
            return THUMBSTICK_POSITION_TOP;
        }
        else
        {
            return THUMBSTICK_POSITION_DEFAULT;
        }
    }
    else if ( axis == THUMBSTICK_HORIZONTAL )
    {
        if ( adc_raw > ( POSTION_MIDDLE + thumbstick_sensitivity ) )
        {
            return THUMBSTICK_POSITION_RIGHT;
        }
        else if ( adc_raw < ( POSTION_MIDDLE - thumbstick_sensitivity ) )
        {
            return THUMBSTICK_POSITION_LEFT;
        }
        else
        {
            return THUMBSTICK_POSITION_DEFAULT;
        }
    }

    return THUMBSTICK_FUNCTION_ERROR;
}

void thumbstick_get_position ( thumbstick_t *ctx, thumbstick_position_t *position )
{
    position->horizontal = thumbstick_get_single_axis_postion( ctx, THUMBSTICK_HORIZONTAL );
    position->vertical = thumbstick_get_single_axis_postion( ctx, THUMBSTICK_VERTICAL );
}

uint8_t thumbstick_button_state ( thumbstick_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t thumbstick_set_sensitivity ( uint16_t sensitivity )
{
    if ( sensitivity >= POSTION_MIDDLE )
        return THUMBSTICK_FUNCTION_ERROR;
    
    thumbstick_sensitivity = sensitivity;
    
    return THUMBSTICK_OK;
}

// ------------------------------------------------------------------------- END

