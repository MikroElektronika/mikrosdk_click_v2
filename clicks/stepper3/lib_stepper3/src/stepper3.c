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
 * @file stepper3.c
 * @brief Stepper 3 Click Driver.
 */

#include "stepper3.h"

/**
 * @brief Stepper 3 I/O signal table for full step resolution.
 * @details Specified I/O signal table for full step resolution, set in the following order:
 * INA, INA, INC, and IND.
 */
static uint8_t stepper3_full_step[ 4 ][ 4 ] = 
{
    { 1, 1, 0, 0 },
    { 1, 0, 0, 1 },
    { 0, 0, 1, 1 },
    { 0, 1, 1, 0 },
};

/**
 * @brief Stepper 3 I/O signal table for half step resolution.
 * @details Specified I/O signal table for half step resolution, set in the following order:
 * INA, INA, INC, and IND.
 */
static uint8_t stepper3_half_step[ 8 ][ 4 ] = 
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
static void stepper3_speed_delay ( uint8_t speed_macro );

/**
 * @brief Set pins for one micro step.
 * @details This function sets INA, INB, INC, and IND pins for a desired step.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] pins_array : Array of 4 bytes that contains INA, INB, INC, and IND pins
 * logic state value.
 * @return Nothing.
 */
static void stepper3_set_pins ( stepper3_t *ctx, uint8_t pins_array[ 4 ] );

void stepper3_cfg_setup ( stepper3_cfg_t *cfg ) 
{
    cfg->ina = HAL_PIN_NC;
    cfg->inb = HAL_PIN_NC;
    cfg->inc = HAL_PIN_NC;
    cfg->ind = HAL_PIN_NC;
}

err_t stepper3_init ( stepper3_t *ctx, stepper3_cfg_t *cfg ) 
{
    err_t error_flag = STEPPER3_OK;

    error_flag |= digital_out_init( &ctx->ina, cfg->ina );
    error_flag |= digital_out_init( &ctx->inb, cfg->inb );
    error_flag |= digital_out_init( &ctx->inc, cfg->inc );
    error_flag |= digital_out_init( &ctx->ind, cfg->ind );

    return error_flag;
}

void stepper3_set_ina_pin ( stepper3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ina, state );
}

void stepper3_set_inb_pin ( stepper3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->inb, state );
}

void stepper3_set_inc_pin ( stepper3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->inc, state );
}

void stepper3_set_ind_pin ( stepper3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ind, state );
}

void stepper3_set_step_mode ( stepper3_t *ctx, uint8_t mode )
{
    if ( STEPPER3_MODE_HALF_STEP == mode )
    {
        ctx->step_mode = STEPPER3_MODE_HALF_STEP;
    }
    else
    {
        ctx->step_mode = STEPPER3_MODE_FULL_STEP;
    }
}

void stepper3_set_direction ( stepper3_t *ctx, uint8_t dir )
{
    if ( STEPPER3_DIR_CCW == dir )
    {
        ctx->direction = STEPPER3_DIR_CCW;
    }
    else
    {
        ctx->direction = STEPPER3_DIR_CW;
    }
}

void stepper3_switch_direction ( stepper3_t *ctx )
{
    if ( STEPPER3_DIR_CCW == ctx->direction )
    {
        ctx->direction = STEPPER3_DIR_CW;
    }
    else
    {
        ctx->direction = STEPPER3_DIR_CCW;
    }
}

void stepper3_enable_device ( stepper3_t *ctx )
{
    digital_out_low ( &ctx->ina );
    digital_out_low ( &ctx->inb );
    digital_out_low ( &ctx->inc );
    digital_out_low ( &ctx->ind );
}

void stepper3_disable_device ( stepper3_t *ctx )
{
    digital_out_high ( &ctx->ina );
    digital_out_high ( &ctx->inb );
    digital_out_high ( &ctx->inc );
    digital_out_high ( &ctx->ind );
}

void stepper3_drive_motor ( stepper3_t *ctx, uint32_t steps, uint8_t speed )
{
    stepper3_enable_device ( ctx );
    stepper3_speed_delay ( speed );
    for ( uint32_t num_steps = 0; num_steps < ( steps * STEPPER3_MICROSTEP_NUM_PER_STEP ); num_steps++ )
    {
        if ( STEPPER3_MODE_HALF_STEP == ctx->step_mode )
        {
            if ( STEPPER3_DIR_CCW == ctx->direction )
            {
                stepper3_set_pins ( ctx, stepper3_half_step[ num_steps % 8 ] );
            }
            else
            {
                stepper3_set_pins ( ctx, stepper3_half_step[ 7 - ( num_steps % 8 ) ] );
            }
        }
        else
        {
            if ( STEPPER3_DIR_CCW == ctx->direction )
            {
                stepper3_set_pins ( ctx, stepper3_full_step[ num_steps % 4 ] );
            }
            else
            {
                stepper3_set_pins ( ctx, stepper3_full_step[ 3 - ( num_steps % 4 ) ] );
            }
        }
        stepper3_speed_delay ( speed );
    }
    stepper3_disable_device ( ctx );
}

static void stepper3_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STEPPER3_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            Delay_10ms( );
            break;
        }
        case STEPPER3_SPEED_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STEPPER3_SPEED_MEDIUM:
        {
            Delay_5ms( );
            break;
        }
        case STEPPER3_SPEED_FAST:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STEPPER3_SPEED_VERY_FAST:
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

static void stepper3_set_pins ( stepper3_t *ctx, uint8_t pins_array[ 4 ] )
{
    stepper3_set_ina_pin ( ctx, pins_array[ 0 ] );
    stepper3_set_inb_pin ( ctx, pins_array[ 1 ] );
    stepper3_set_inc_pin ( ctx, pins_array[ 2 ] );
    stepper3_set_ind_pin ( ctx, pins_array[ 3 ] );
}

// ------------------------------------------------------------------------- END
