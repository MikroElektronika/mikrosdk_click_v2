/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file timerrelay.c
 * @brief Timer Relay Click Driver.
 */

#include "timerrelay.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void timerrelay_cfg_setup ( timerrelay_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->trg  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t timerrelay_init ( timerrelay_t *ctx, timerrelay_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->trg, cfg->trg );
    
    ctx->vcc_sel = TIMERRELAY_VCC_3V3;

    return SPI_MASTER_SUCCESS;
}

err_t timerrelay_default_cfg ( timerrelay_t *ctx ) 
{
    err_t error_flag = TIMERRELAY_OK;
    
    timerrelay_set_vcc_sel( ctx, TIMERRELAY_VCC_3V3 );
    
    error_flag |= timerrelay_set_delay( ctx, 0 );
    
    timerrelay_set_trg_pin( ctx, TIMERRELAY_PIN_STATE_HIGH );
    timerrelay_set_rst_pin( ctx, TIMERRELAY_PIN_STATE_HIGH );

    timerrelay_activate_reset( ctx );
    timerrelay_activate_trigger( ctx );
    
    return error_flag;
}

err_t timerrelay_generic_write ( timerrelay_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void timerrelay_set_vcc_sel ( timerrelay_t *ctx, uint8_t vcc_sel )
{
    ctx->vcc_sel = vcc_sel;
}

err_t timerrelay_set_wiper_pos ( timerrelay_t *ctx, uint8_t wiper_pos )
{
    err_t error_flag = TIMERRELAY_OK;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &wiper_pos, 1 );
    spi_master_deselect_device( ctx->chip_select );   
    
    return error_flag;
}

err_t timerrelay_set_delay ( timerrelay_t *ctx, uint8_t delay )
{
    err_t error_flag = TIMERRELAY_OK;
    uint8_t tmp_data = 0;
    
    if ( TIMERRELAY_VCC_3V3 == ctx->vcc_sel )
    {
        if ( TIMERRELAY_3V3_MAX_DELAY < delay )
        {
            return TIMERRELAY_ERROR;
        }
    
        tmp_data = ( uint8_t ) ( TIMERRELAY_3V3_MAX_DELAY - delay ) / TIMERRELAY_3V3_CALCULATION_MULTIPLIER;
    }
    else
    {
         if ( TIMERRELAY_5V_MAX_DELAY < delay )
        {
            return TIMERRELAY_ERROR;
        }
    
        tmp_data = ( uint8_t ) ( TIMERRELAY_5V_MAX_DELAY - delay ) / TIMERRELAY_5V_CALCULATION_MULTIPLIER;    
    }
    
    error_flag |= timerrelay_set_wiper_pos( ctx, tmp_data );
    
    return error_flag;
}

void timerrelay_set_rst_pin ( timerrelay_t *ctx, uint8_t pin_state )
{
    if ( TIMERRELAY_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void timerrelay_set_trg_pin ( timerrelay_t *ctx, uint8_t pin_state )
{
    if ( TIMERRELAY_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->trg );
    }
    else
    {
        digital_out_low( &ctx->trg );
    }
}

void timerrelay_activate_reset ( timerrelay_t *ctx )
{
    timerrelay_set_rst_pin( ctx, TIMERRELAY_PIN_STATE_LOW );
    Delay_1ms( );
    timerrelay_set_rst_pin( ctx, TIMERRELAY_PIN_STATE_HIGH );
}

void timerrelay_activate_trigger ( timerrelay_t *ctx )
{
    timerrelay_set_trg_pin( ctx, TIMERRELAY_PIN_STATE_LOW );
    Delay_1ms( );
    timerrelay_set_trg_pin( ctx, TIMERRELAY_PIN_STATE_HIGH );
}

// ------------------------------------------------------------------------- END
