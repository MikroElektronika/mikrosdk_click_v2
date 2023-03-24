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

#include "pedometer.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pedometer_cfg_setup ( pedometer_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;
    cfg->dev_step_counter = 0;
}

PEDOMETER_RETVAL pedometer_init ( pedometer_t *ctx, pedometer_cfg_t *cfg )
{
    // Input pins

    if ( digital_in_init( &ctx->int_pin, cfg->int_pin ) == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return PEDOMETER_INIT_ERROR;
    }

    ctx->step_counter = cfg->dev_step_counter;
    return PEDOMETER_OK;
}

void pedometer_reset_step_counter ( pedometer_t *ctx, uint32_t new_cnt )
{
    ctx->step_counter = new_cnt;
}

uint8_t pedometer_get_interrupt_state ( pedometer_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint32_t pedometer_get_step_counter ( pedometer_t *ctx )
{
    return ctx->step_counter;
}

uint8_t pedometer_process ( pedometer_t *ctx )
{
    uint8_t state;
    
    state = pedometer_get_interrupt_state( ctx );
    
    if ( state == 1 )
    {
        ctx->step_counter++;
        return PEDOMETER_NEW_STEP_DETECTED;
    }
    return PEDOMETER_NO_STEP_DETECTED;
}

// ------------------------------------------------------------------------- END

