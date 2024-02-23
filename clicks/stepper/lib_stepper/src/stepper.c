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
 * @file stepper.c
 * @brief Stepper Click Driver.
 */

#include "stepper.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stepper_speed_delay ( uint8_t speed_macro );

void stepper_cfg_setup ( stepper_cfg_t *cfg ) 
{
    cfg->ms1 = HAL_PIN_NC;
    cfg->ms2 = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
}

err_t stepper_init ( stepper_t *ctx, stepper_cfg_t *cfg ) 
{
    err_t error_flag = STEPPER_OK;

    error_flag |= digital_out_init( &ctx->ms1, cfg->ms1 );
    error_flag |= digital_out_init( &ctx->ms2, cfg->ms2 );
    error_flag |= digital_out_init( &ctx->dir, cfg->dir );
    error_flag |= digital_out_init( &ctx->step, cfg->step );
    error_flag |= digital_out_init( &ctx->en, cfg->en );

    return error_flag;
}

void stepper_default_cfg ( stepper_t *ctx ) 
{
    stepper_disable_device ( ctx );
    stepper_set_direction ( ctx, STEPPER_DIR_CW );
    stepper_set_step_mode ( ctx, STEPPER_MODE_FULL_STEP );
}

void stepper_set_step_mode ( stepper_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case STEPPER_MODE_FULL_STEP:
        {
            digital_out_low ( &ctx->ms1 );
            digital_out_low ( &ctx->ms2 );
            break;
        }
        case STEPPER_MODE_HALF_STEP:
        {
            digital_out_high ( &ctx->ms1 );
            digital_out_low ( &ctx->ms2 );
            break;
        }
        case STEPPER_MODE_QUARTER_STEP:
        {
            digital_out_low ( &ctx->ms1 );
            digital_out_high ( &ctx->ms2 );
            break;
        }
        case STEPPER_MODE_1_OVER_8_STEP:
        {
            digital_out_high ( &ctx->ms1 );
            digital_out_high ( &ctx->ms2 );
            break;
        }
        default:
        {
            digital_out_low ( &ctx->ms1 );
            digital_out_low ( &ctx->ms2 );
            break;
        }
    }
}

void stepper_drive_motor ( stepper_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper_enable_device ( ctx );
    for ( uint32_t step_cnt = 0; step_cnt < steps; step_cnt++ )
    {
        for ( uint32_t micro_step_cnt = 0; micro_step_cnt < STEPPER_MICROSTEP_NUM_PER_STEP; micro_step_cnt++ )
        {
            stepper_set_step_pin ( ctx, STEPPER_PIN_STATE_HIGH );
            stepper_speed_delay ( speed );
            stepper_set_step_pin ( ctx, STEPPER_PIN_STATE_LOW );
            stepper_speed_delay ( speed );
        }
    }
    stepper_disable_device ( ctx );
}

void stepper_enable_device ( stepper_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stepper_disable_device ( stepper_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stepper_set_direction ( stepper_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stepper_switch_direction ( stepper_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stepper_set_step_pin ( stepper_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

static void stepper_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER_SPEED_VERY_FAST:
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
