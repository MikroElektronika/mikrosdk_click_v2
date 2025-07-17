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
 * @file powerstep.c
 * @brief Power Step Click Driver.
 */

#include "powerstep.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void powerstep_speed_delay ( uint8_t speed_macro );

void powerstep_cfg_setup ( powerstep_cfg_t *cfg ) 
{
    cfg->dir  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
}

err_t powerstep_init ( powerstep_t *ctx, powerstep_cfg_t *cfg ) 
{
    err_t error_flag = POWERSTEP_OK;

    error_flag |= digital_out_init( &ctx->dir, cfg->dir );
    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->step, cfg->step );

    return error_flag;
}

void powerstep_enable_device ( powerstep_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void powerstep_disable_device ( powerstep_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void powerstep_set_direction ( powerstep_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void powerstep_switch_direction ( powerstep_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void powerstep_set_rst_pin ( powerstep_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void powerstep_reset_device ( powerstep_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void powerstep_set_step_pin ( powerstep_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

void powerstep_drive_motor ( powerstep_t *ctx, uint32_t steps, uint8_t speed )
{
    powerstep_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        powerstep_set_step_pin ( ctx, POWERSTEP_PIN_HIGH_LEVEL );
        powerstep_speed_delay ( speed );
        powerstep_set_step_pin ( ctx, POWERSTEP_PIN_LOW_LEVEL );
        powerstep_speed_delay ( speed );
    }
    powerstep_disable_device ( ctx );
}

static void powerstep_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case POWERSTEP_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case POWERSTEP_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case POWERSTEP_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case POWERSTEP_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case POWERSTEP_SPEED_VERY_FAST:
        {
            Delay_500us( );
            break;
        }
        default:
        {
            Delay_1ms( );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
