/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file stepper32.c
 * @brief Stepper 32 Click Driver.
 */

#include "stepper32.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting the delay length.
 * @return Nothing.
 */
static void stepper32_speed_delay ( uint8_t speed_macro );

void stepper32_cfg_setup ( stepper32_cfg_t *cfg ) 
{
    cfg->en = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->home = HAL_PIN_NC;
}

err_t stepper32_init ( stepper32_t *ctx, stepper32_cfg_t *cfg ) 
{
    err_t error_flag = STEPPER32_OK;

    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->dir, cfg->dir );
    error_flag |= digital_out_init( &ctx->step, cfg->step );

    error_flag |= digital_in_init( &ctx->home, cfg->home );
    
    Delay_1ms ( );
    stepper32_disable_device ( ctx );
    stepper32_reset_device ( ctx );
    stepper32_set_direction ( ctx, STEPPER32_DIR_CW );
    stepper32_set_step_pin ( ctx, STEPPER32_PIN_STATE_LOW );
    Delay_1ms ( );

    return error_flag;
}

void stepper32_enable_device ( stepper32_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper32_disable_device ( stepper32_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper32_reset_device ( stepper32_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void stepper32_set_rst_pin ( stepper32_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stepper32_set_direction ( stepper32_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper32_switch_direction ( stepper32_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

uint8_t stepper32_get_home_pin ( stepper32_t *ctx )
{
    return digital_in_read ( &ctx->home );
}

void stepper32_set_step_pin ( stepper32_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

void stepper32_drive_motor ( stepper32_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper32_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stepper32_set_step_pin ( ctx, STEPPER32_PIN_STATE_HIGH );
        stepper32_speed_delay ( speed );
        stepper32_set_step_pin ( ctx, STEPPER32_PIN_STATE_LOW );
        stepper32_speed_delay ( speed );
    }
    stepper32_disable_device ( ctx );
}

static void stepper32_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER32_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER32_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER32_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER32_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER32_SPEED_VERY_FAST:
        {
            Delay_1ms( );
            break;
        }
        default:
        {
            Delay_5ms( );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
