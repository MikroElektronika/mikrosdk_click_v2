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
 * @file watchdog.c
 * @brief Watchdog Click Driver.
 */

#include "watchdog.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Delay milliseconds function.
 * @param[in] ms_delay : Duration of the delay in milliseconds.
 */
static void dev_ms_delay ( uint16_t ms_delay );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void watchdog_cfg_setup ( watchdog_cfg_t *cfg ) 
{
    cfg->s0 = HAL_PIN_NC;
    cfg->s1   = HAL_PIN_NC;
    cfg->wdi = HAL_PIN_NC;
    cfg->wdo = HAL_PIN_NC;
}

err_t watchdog_init ( watchdog_t *ctx, watchdog_cfg_t *cfg ) 
{
    err_t return_flag = 0;
   
    return_flag |= digital_out_init( &ctx->s0, cfg->s0 );
    return_flag |= digital_out_init( &ctx->s1, cfg->s1 );
    return_flag |= digital_out_init( &ctx->wdi, cfg->wdi );
    
    return_flag |= digital_in_init( &ctx->wdo, cfg->wdo );

    return return_flag;
}

err_t watchdog_default_cfg ( watchdog_t *ctx ) 
{
    digital_out_low( &ctx->s0 );
    digital_out_low( &ctx->s1 );
    digital_out_low( &ctx->wdi );
    return WATCHDOG_OK;
}

uint8_t watchdog_get_wdo ( watchdog_t *ctx ) 
{
    return digital_in_read( &ctx->wdo );
}

void watchdog_set_set0 ( watchdog_t *ctx, uint8_t set0_state )
{
    if ( set0_state == 1 ) {
        digital_out_high( &ctx->s0 );
    } else {
        digital_out_low( &ctx->s0 );
    }
}

void watchdog_set_set1 ( watchdog_t *ctx, uint8_t set1_state )
{
    if ( set1_state == 1 ) {
        digital_out_high( &ctx->s1 );
    } else {
        digital_out_low( &ctx->s1 );
    }
}

void watchdog_set_wdi ( watchdog_t *ctx, uint8_t wdi_state )
{
    if ( wdi_state == 1 ) {
        digital_out_high( &ctx->wdi );
    } else {
        digital_out_low( &ctx->wdi );
    }
}

void watchdog_send_pulse ( watchdog_t *ctx, uint16_t p_duration_ms )
{
    watchdog_set_wdi( ctx, 1 );
    dev_ms_delay( p_duration_ms );
    watchdog_set_wdi( ctx, 0 );
    dev_ms_delay( p_duration_ms );
}

void watchdog_setup_time ( watchdog_t *ctx, uint8_t setup_time_mode )
{
    switch ( setup_time_mode ) {
        case WATCHDOG_SETUP_TIME_MODE_0: {
            watchdog_set_set0( ctx, 0 );
            watchdog_set_set1( ctx, 0 );
            break;
        }
        case WATCHDOG_SETUP_TIME_MODE_1: {
            watchdog_set_set0( ctx, 0 );
            watchdog_set_set1( ctx, 1 );
            break;
        }
        case WATCHDOG_SETUP_TIME_MODE_2: {
            watchdog_set_set0( ctx, 1 );
            watchdog_set_set1( ctx, 1 );
            break;
        }
        case WATCHDOG_SETUP_TIME_MODE_DISABLE: {
            watchdog_set_set0( ctx, 1 );
            watchdog_set_set1( ctx, 0 );
            break;
        }
        default: {
            watchdog_set_set0( ctx, 0 );
            watchdog_set_set1( ctx, 0 );
            break;
        }
    }
}


// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_ms_delay ( uint16_t ms_delay )
{
    while ( ms_delay ) {
        ms_delay--;
        Delay_1ms( );
    }
}

// ------------------------------------------------------------------------- END
