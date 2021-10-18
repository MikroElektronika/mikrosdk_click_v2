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
 * @file headphoneamp.c
 * @brief Headphone AMP Click Driver.
 */

#include "headphoneamp.h"

static void dev_clk_delay ( void );

static void dev_clk ( headphoneamp_t *ctx );

static void dev_set_delay ( void );

void headphoneamp_cfg_setup ( headphoneamp_cfg_t *cfg ) 
{
    cfg->shdn = HAL_PIN_NC;
    cfg->clk = HAL_PIN_NC;
    cfg->ud = HAL_PIN_NC;
}

err_t headphoneamp_init ( headphoneamp_t *ctx, headphoneamp_cfg_t *cfg ) 
{
    err_t return_flag = 0;
   
    return_flag |= digital_out_init( &ctx->shdn, cfg->shdn );
    return_flag |= digital_out_init( &ctx->clk, cfg->clk );
    return_flag |= digital_out_init( &ctx->ud, cfg->ud );

    return return_flag;
}

err_t headphoneamp_default_cfg ( headphoneamp_t *ctx ) 
{
    digital_out_low( &ctx->clk ); 
    digital_out_low( &ctx->ud ); 

    headphoneamp_shutdown( ctx );
    
    return HEADPHONEAMP_OK;
}

err_t headphoneamp_shutdown ( headphoneamp_t *ctx ) 
{
    digital_out_high( &ctx->shdn );
   
    return HEADPHONEAMP_OK;
}

err_t headphoneamp_power_up ( headphoneamp_t *ctx ) 
{
    digital_out_low( &ctx->shdn );
    
    return HEADPHONEAMP_OK;
}

err_t headphoneamp_volume_down ( headphoneamp_t *ctx ) 
{
    digital_out_low( &ctx->ud );
    dev_set_delay( );
    
    dev_clk( ctx );
    
    return HEADPHONEAMP_OK;
}

err_t headphoneamp_volume_up ( headphoneamp_t *ctx ) 
{
    digital_out_high( &ctx->ud );
    dev_set_delay( );
    dev_clk( ctx );
    
    return HEADPHONEAMP_OK;
}

err_t headphoneamp_set_sound_volume ( headphoneamp_t *ctx, uint8_t sound_volume ) 
{
    if ( sound_volume > HEADPHONEAMP_SOUND_VOLUME_POS_12_dB ) {
        return HEADPHONEAMP_ERROR;    
    }
    
    for ( uint8_t n_clk = 0; n_clk < HEADPHONEAMP_SOUND_VOLUME_POS_12_dB; n_clk++ ) {
        headphoneamp_volume_down( ctx );
    }
    
    for ( uint8_t n_clk = 0; n_clk < sound_volume; n_clk++ ) {
        headphoneamp_volume_up( ctx );
    }
    
    return HEADPHONEAMP_OK;
}

static void dev_set_delay ( void ) 
{
    Delay_1ms( );
}

static void dev_clk_delay ( void ) 
{
    Delay_500us( );
}

static void dev_clk ( headphoneamp_t *ctx ) 
{
    digital_out_high( &ctx->clk );
    dev_clk_delay( );
    digital_out_low( &ctx->clk ); 
    dev_clk_delay( );
}

// ------------------------------------------------------------------------- END
