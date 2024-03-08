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
 * @file stspin820.c
 * @brief STSPIN820 Click Driver.
 */

#include "stspin820.h"

/**
 * @brief Set delay for controlling motor speed.
 * @details This function sets a delay between toggling step pin.
 * @param[in] speed_macro : Speed macro for selecting how long the delay will be.
 * @return Nothing.
 */
static void stspin820_speed_delay ( uint8_t speed_macro );

void stspin820_cfg_setup ( stspin820_cfg_t *cfg ) 
{
    cfg->dir = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->step = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;
}

err_t stspin820_init ( stspin820_t *ctx, stspin820_cfg_t *cfg ) 
{
    err_t error_flag = STSPIN820_OK;

    error_flag |= digital_out_init( &ctx->dir, cfg->dir );
    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->step, cfg->step );

    error_flag |= digital_in_init( &ctx->fault, cfg->fault );

    return error_flag;
}

void stspin820_default_cfg ( stspin820_t *ctx ) 
{
    stspin820_disable_device ( ctx );
    stspin820_set_direction ( ctx, STSPIN820_DIR_CW );
    stspin820_reset_device ( ctx );
}

void stspin820_drive_motor ( stspin820_t *ctx, uint32_t steps, uint8_t speed )
{
    stspin820_enable_device ( ctx );
    for ( uint32_t cnt = 0; cnt < steps; cnt++ )
    {
        stspin820_set_step_pin ( ctx, STSPIN820_PIN_HIGH_LEVEL );
        stspin820_speed_delay ( speed );
        stspin820_set_step_pin ( ctx, STSPIN820_PIN_LOW_LEVEL );
        stspin820_speed_delay ( speed );
    }
    stspin820_disable_device ( ctx );
}

void stspin820_enable_device ( stspin820_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void stspin820_disable_device ( stspin820_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void stspin820_set_direction ( stspin820_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void stspin820_switch_direction ( stspin820_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void stspin820_reset_device ( stspin820_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void stspin820_set_rst_pin ( stspin820_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t stspin820_get_fault_pin ( stspin820_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

void stspin820_set_step_pin ( stspin820_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->step, state );
}

static void stspin820_speed_delay ( uint8_t speed_macro )
{
    switch ( speed_macro )
    {
        case STSPIN820_SPEED_VERY_SLOW:
        {
            Delay_10ms( );
            break;
        }
        case STSPIN820_SPEED_SLOW:
        {
            Delay_5ms( );
            break;
        }
        case STSPIN820_SPEED_MEDIUM:
        {
            Delay_1ms( );
            Delay_1ms( );
            Delay_500us( );
            break;
        }
        case STSPIN820_SPEED_FAST:
        {
            Delay_1ms( );
            break;
        }
        case STSPIN820_SPEED_VERY_FAST:
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
