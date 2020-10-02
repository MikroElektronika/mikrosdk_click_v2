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

#include "buckboost.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buckboost_cfg_setup ( buckboost_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->vs2   = HAL_PIN_NC;
    cfg->run = HAL_PIN_NC;
    cfg->vs3   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->vs1 = HAL_PIN_NC;
}

BUCKBOOST_RETVAL buckboost_init ( buckboost_t *ctx, buckboost_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->vs2, cfg->vs2 );
    digital_out_init( &ctx->run, cfg->run );
    digital_out_init( &ctx->vs3, cfg->vs3 );
    digital_out_init( &ctx->pwm, cfg->pwm );
    digital_out_init( &ctx->vs1, cfg->vs1 );

    return BUCKBOOST_OK;
}

void buckboost_default_cfg ( buckboost_t *ctx )
{
    buckboost_enable( ctx );
    Delay_1ms();
    buckboost_set_mode_fixed_freq( ctx );
}

void buckboost_enable ( buckboost_t *ctx )
{
    digital_out_high( &ctx->run );
}

void buckboost_disable ( buckboost_t *ctx )
{
    digital_out_low( &ctx->run );
}

void buckboost_set_mode_fixed_freq ( buckboost_t *ctx )
{
    digital_out_high( &ctx->pwm );
}

void buckboost_enables_auto_burst_mode ( buckboost_t *ctx )
{
    digital_out_low( &ctx->pwm );
}

void buckboost_set_2500mv ( buckboost_t *ctx )
{
    digital_out_low( &ctx->vs3 );
    Delay_1ms();
    digital_out_low( &ctx->vs2 );
    Delay_1ms();
    digital_out_low( &ctx->vs1 );
}

void buckboost_set_3300mv ( buckboost_t *ctx )
{
    digital_out_low( &ctx->vs3 );
    Delay_1ms();
    digital_out_low( &ctx->vs2 );
    Delay_1ms();
    digital_out_high( &ctx->vs1 );
}

void buckboost_set_4100mv ( buckboost_t *ctx )
{
    digital_out_low( &ctx->vs3 );
    Delay_1ms();
    digital_out_high( &ctx->vs2 );
    Delay_1ms();
    digital_out_low( &ctx->vs1 );
}

void buckboost_set_5000mv ( buckboost_t *ctx )
{
    digital_out_low( &ctx->vs3 );
    Delay_1ms();
    digital_out_high( &ctx->vs2 );
    Delay_1ms();
    digital_out_high( &ctx->vs1 );
}

void buckboost_set_6900mv ( buckboost_t *ctx )
{
    digital_out_high( &ctx->vs3 );
    Delay_1ms();
    digital_out_low( &ctx->vs2 );
    Delay_1ms();
    digital_out_low( &ctx->vs1 );
}

void buckboost_set_8200mv ( buckboost_t *ctx )
{
    digital_out_high( &ctx->vs3 );
    Delay_1ms();
    digital_out_low( &ctx->vs2 );
    Delay_1ms();
    digital_out_high( &ctx->vs1 );
}

void buckboost_set_12000mv ( buckboost_t *ctx )
{
    digital_out_high( &ctx->vs3 );
    Delay_1ms();
    digital_out_high( &ctx->vs2 );
    Delay_1ms();
    digital_out_low( &ctx->vs1 );
}

void buckboost_set_15000mv ( buckboost_t *ctx )
{
    digital_out_high( &ctx->vs3 );
    Delay_1ms();
    digital_out_high( &ctx->vs2 );
    Delay_1ms();
    digital_out_high( &ctx->vs1 );
}

// ------------------------------------------------------------------------- END

