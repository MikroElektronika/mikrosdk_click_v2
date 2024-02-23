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
 * @file stepper2.c
 * @brief Stepper 2 Click Driver.
 */

#include "stepper2.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper2_speed_delay ( uint8_t speed_macro );

void stepper2_cfg_setup ( stepper2_cfg_t *cfg ) 
{
    cfg->en = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->slp = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
}

err_t stepper2_init ( stepper2_t *ctx, stepper2_cfg_t *cfg ) 
{
    err_t error_flag = STEPPER2_OK;

    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->slp, cfg->slp );
    error_flag |= digital_out_init( &ctx->step, cfg->step );
    error_flag |= digital_out_init( &ctx->dir, cfg->dir );

    return error_flag;
}

void stepper2_default_cfg ( stepper2_t *ctx ) 
{
    stepper2_disable_reset ( ctx );
    stepper2_disable_sleep ( ctx );
    stepper2_disable_device ( ctx );
    stepper2_set_direction ( ctx, STEPPER2_DIR_CCW );
}

void stepper2_drive_motor ( stepper2_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper2_enable_device ( ctx );
    Delay_10ms ( );
    for ( uint32_t step_cnt = 0; step_cnt < steps; step_cnt++ )
    {
        for ( uint32_t micro_step_cnt = 0; micro_step_cnt < STEPPER2_MICROSTEP_NUM_PER_STEP; micro_step_cnt++ )
        {
            stepper2_set_step_pin ( ctx, STEPPER2_PIN_STATE_HIGH );
            stepper2_speed_delay ( speed );
            stepper2_set_step_pin ( ctx, STEPPER2_PIN_STATE_LOW );
            stepper2_speed_delay ( speed );
        }
    }
    stepper2_disable_device ( ctx );
}

void stepper2_enable_reset ( stepper2_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void stepper2_disable_reset ( stepper2_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void stepper2_enable_sleep ( stepper2_t *ctx )
{
    digital_out_low ( &ctx->slp );
}

void stepper2_disable_sleep ( stepper2_t *ctx )
{
    digital_out_high ( &ctx->slp );
}

void stepper2_enable_device ( stepper2_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper2_disable_device ( stepper2_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper2_set_direction ( stepper2_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper2_switch_direction ( stepper2_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper2_set_step_pin ( stepper2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

static void stepper2_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER2_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER2_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER2_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER2_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER2_SPEED_VERY_FAST:
        {
            Delay_1ms( );
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
