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

#include "relay2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void relay2_cfg_setup ( relay2_cfg_t *cfg )
{
    // Additional gpio pins

   cfg->an   = HAL_PIN_NC;
   cfg->pwm = HAL_PIN_NC;
}

RELAY2_RETVAL relay2_init ( relay2_t *ctx, relay2_cfg_t *cfg )
{
    // Output pins 

   digital_out_init( &ctx->an, cfg->an );
   digital_out_init( &ctx->pwm, cfg->pwm );

   return RELAY2_OK;
}


void relay2_relay2_control( relay2_t *ctx, uint8_t pin_state )
{
    if ( pin_state == 0 )
    {
        digital_out_low( &ctx->an );
    }
    else
    {
        digital_out_high( &ctx->an );
    }
}

void relay2_relay1_control( relay2_t *ctx, uint8_t pin_state)
{
    if ( pin_state == 0 )
    {
        digital_out_low( &ctx->pwm );
    }
    else
    {
        digital_out_high( &ctx->pwm );
    }
}

// ------------------------------------------------------------------------- END
