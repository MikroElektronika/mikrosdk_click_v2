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
 * @file stepper27.c
 * @brief Stepper 27 Click Driver.
 */

#include "stepper27.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper27_speed_delay ( uint8_t speed_macro );

void stepper27_cfg_setup ( stepper27_cfg_t *cfg ) 
{
    cfg->dir   = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->en    = HAL_PIN_NC;
    cfg->step  = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;
}

err_t stepper27_init ( stepper27_t *ctx, stepper27_cfg_t *cfg ) 
{
    err_t error_flag = STEPPER27_OK;

    error_flag |= digital_out_init( &ctx->dir, cfg->dir );
    error_flag |= digital_out_init( &ctx->sleep, cfg->sleep );
    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->step, cfg->step );

    error_flag |= digital_in_init( &ctx->fault, cfg->fault );

    return error_flag;
}

void stepper27_enable_device ( stepper27_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper27_disable_device ( stepper27_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper27_set_direction ( stepper27_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper27_switch_direction ( stepper27_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper27_set_sleep_pin ( stepper27_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sleep, state );
}

void stepper27_reset_device ( stepper27_t *ctx )
{
    digital_out_low ( &ctx->sleep );
    Delay_100ms ( );
    digital_out_high ( &ctx->sleep );
    Delay_100ms ( );
}

void stepper27_set_step_pin ( stepper27_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

uint8_t stepper27_get_int_pin ( stepper27_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

void stepper27_drive_motor ( stepper27_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper27_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper27_set_step_pin ( ctx, STEPPER27_PIN_HIGH_LEVEL );
        stepper27_speed_delay ( speed );
        stepper27_set_step_pin ( ctx, STEPPER27_PIN_LOW_LEVEL );
        stepper27_speed_delay ( speed );
    }
    stepper27_disable_device ( ctx );
}

static void stepper27_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER27_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER27_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER27_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER27_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER27_SPEED_VERY_FAST:
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
