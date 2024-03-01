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
 * @file stepper4.c
 * @brief Stepper 4 Click Driver.
 */

#include "stepper4.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper4_speed_delay ( uint8_t speed_macro );

void stepper4_cfg_setup ( stepper4_cfg_t *cfg ) 
{
    cfg->dir = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t stepper4_init ( stepper4_t *ctx, stepper4_cfg_t *cfg ) 
{
    err_t error_flag = STEPPER4_OK;

    error_flag |= digital_out_init( &ctx->dir, cfg->dir );
    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->step, cfg->step );

    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    return error_flag;
}

void stepper4_default_cfg ( stepper4_t *ctx ) 
{
    stepper4_enable_device ( ctx );
    stepper4_set_direction ( ctx, STEPPER4_DIR_CW );
    stepper4_reset_device ( ctx );
}

void stepper4_drive_motor ( stepper4_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper4_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper4_set_step_pin ( ctx, STEPPER4_PIN_HIGH_LEVEL );
        stepper4_speed_delay ( speed );
        stepper4_set_step_pin ( ctx, STEPPER4_PIN_LOW_LEVEL );
        stepper4_speed_delay ( speed );
    }
    stepper4_disable_device ( ctx );
}

void stepper4_enable_device ( stepper4_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper4_disable_device ( stepper4_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper4_set_direction ( stepper4_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper4_switch_direction ( stepper4_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper4_reset_device ( stepper4_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t stepper4_get_int_pin ( stepper4_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void stepper4_set_step_pin ( stepper4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

static void stepper4_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER4_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER4_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER4_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER4_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STEPPER4_SPEED_VERY_FAST:
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
