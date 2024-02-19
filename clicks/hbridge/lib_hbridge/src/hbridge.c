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
 * @file hbridge.c
 * @brief H-Bridge Click Driver.
 */

#include "hbridge.h"

/**
 * @brief H-Bridge I/O signal table for full step resolution.
 * @details Specified I/O signal table for full step resolution, set in the following order:
 * IN1A, IN1A, IN1B, and IN2B.
 */
static uint8_t hbridge_full_step[ 4 ][ 4 ] = 
{
    { 1, 1, 0, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 1, 1 },
    { 0, 1, 1, 0 },
};

/**
 * @brief H-Bridge I/O signal table for half step resolution.
 * @details Specified I/O signal table for half step resolution, set in the following order:
 * IN1A, IN1A, IN1B, and IN2B.
 */
static uint8_t hbridge_half_step[ 8 ][ 4 ] = 
{
    { 1, 1, 0, 0 },
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, 1, 1, 0 },
    { 0, 1, 0, 0 },
};

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void hbridge_speed_delay ( uint8_t speed_macro );

/**
 * @brief Set pins for one micro step.
 * @details This function sets IN1A, IN1A, IN1B, and IN2B pins for a desired step.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] pins_array : Array of 4 bytes that contains IN1A, IN1A, IN1B, and IN2B pins
 * logic state value.
 * @return Nothing.
 */
static void hbridge_set_pins ( hbridge_t *ctx, uint8_t pins_array[ 4 ] );

void hbridge_cfg_setup ( hbridge_cfg_t *cfg ) 
{
    cfg->in2a = HAL_PIN_NC;
    cfg->in2b = HAL_PIN_NC;
    cfg->in1b = HAL_PIN_NC;
    cfg->in1a = HAL_PIN_NC;
}

err_t hbridge_init ( hbridge_t *ctx, hbridge_cfg_t *cfg ) 
{
    err_t error_flag = HBRIDGE_OK;

    error_flag |= digital_out_init( &ctx->in2a, cfg->in2a );
    error_flag |= digital_out_init( &ctx->in2b, cfg->in2b );
    error_flag |= digital_out_init( &ctx->in1b, cfg->in1b );
    error_flag |= digital_out_init( &ctx->in1a, cfg->in1a );

    return error_flag;
}

void hbridge_set_in1a_pin ( hbridge_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in1a, state );
}

void hbridge_set_in2a_pin ( hbridge_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in2a, state );
}

void hbridge_set_in1b_pin ( hbridge_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in1b, state );
}

void hbridge_set_in2b_pin ( hbridge_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in2b, state );
}

void hbridge_set_step_mode ( hbridge_t *ctx, uint8_t mode )
{
    if ( HBRIDGE_MODE_HALF_STEP == mode )
    {
        ctx->step_mode = HBRIDGE_MODE_HALF_STEP;
    }
    else
    {
        ctx->step_mode = HBRIDGE_MODE_FULL_STEP;
    }
}

void hbridge_set_direction ( hbridge_t *ctx, uint8_t dir )
{
    if ( HBRIDGE_DIR_CCW == dir )
    {
        ctx->direction = HBRIDGE_DIR_CCW;
    }
    else
    {
        ctx->direction = HBRIDGE_DIR_CW;
    }
}

void hbridge_switch_direction ( hbridge_t *ctx )
{
    if ( HBRIDGE_DIR_CCW == ctx->direction )
    {
        ctx->direction = HBRIDGE_DIR_CW;
    }
    else
    {
        ctx->direction = HBRIDGE_DIR_CCW;
    }
}

void hbridge_enable_device ( hbridge_t *ctx )
{
    digital_out_low ( &ctx->in1a );
    digital_out_low ( &ctx->in2a );
    digital_out_low ( &ctx->in1b );
    digital_out_low ( &ctx->in2b );
}

void hbridge_disable_device ( hbridge_t *ctx )
{
    digital_out_high ( &ctx->in1a );
    digital_out_high ( &ctx->in2a );
    digital_out_high ( &ctx->in1b );
    digital_out_high ( &ctx->in2b );
}

void hbridge_drive_motor ( hbridge_t *ctx, uint32_t steps, uint8_t speed )
{
    hbridge_enable_device ( ctx );
    hbridge_speed_delay ( speed );
    for ( uint32_t num_steps = 0; num_steps < steps; num_steps++ )
    {
        if ( HBRIDGE_MODE_HALF_STEP == ctx->step_mode )
        {
            if ( HBRIDGE_DIR_CW == ctx->direction )
            {
                hbridge_set_pins ( ctx, hbridge_half_step[ num_steps % 8 ] );
            }
            else
            {
                hbridge_set_pins ( ctx, hbridge_half_step[ 7 - ( num_steps % 8 ) ] );
            }
        }
        else
        {
            if ( HBRIDGE_DIR_CW == ctx->direction )
            {
                hbridge_set_pins ( ctx, hbridge_full_step[ num_steps % 4 ] );
            }
            else
            {
                hbridge_set_pins ( ctx, hbridge_full_step[ 3 - ( num_steps % 4 ) ] );
            }
        }
        hbridge_speed_delay ( speed );
    }
    hbridge_disable_device ( ctx );
}

static void hbridge_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case HBRIDGE_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case HBRIDGE_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case HBRIDGE_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case HBRIDGE_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case HBRIDGE_SPEED_VERY_FAST:
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

static void hbridge_set_pins ( hbridge_t *ctx, uint8_t pins_array[ 4 ] )
{
    hbridge_set_in1a_pin ( ctx, pins_array[ 0 ] );
    hbridge_set_in2a_pin ( ctx, pins_array[ 1 ] );
    hbridge_set_in1b_pin ( ctx, pins_array[ 2 ] );
    hbridge_set_in2b_pin ( ctx, pins_array[ 3 ] );
}

// ------------------------------------------------------------------------- END
