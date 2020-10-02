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

#include "motionekmc.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void motionekmc_cfg_setup ( motionekmc_cfg_t *cfg )
{
    // Additional gpio pins

   //cfg->an   = HAL_PIN_NC;
   //cfg->rst = HAL_PIN_NC;
   //cfg->en   = HAL_PIN_NC;
   //cfg->pwm = HAL_PIN_NC;
   //cfg->int_pin = HAL_PIN_NC;
}

MOTIONEKMC_RETVAL motionekmc_init ( motionekmc_t *ctx, motionekmc_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    // Example: Sets pin [high, low] 

    // digital_out_high( &ctx->rst );
    // digital_out_low( &ctx->rst );
	
	// Example: Get pin state 

	// digital_in_read( &ctx->int_pin );

    return MOTIONEKMC_OK;
}

void motionekmc_default_cfg ( motionekmc_t *ctx )
{
    motionekmc_active( ctx, MOTIONEKMC_MODULE_ENABLE );
    Delay_1sec();
}

void motionekmc_active ( motionekmc_t *ctx, uint8_t state )
{
    if ( 0 == state )
    {
        digital_out_write( &ctx->en, 0 );
    }
    else
    {
        digital_out_write( &ctx->en, 1 );
    }
}

uint8_t motionekmc_detect_state ( motionekmc_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

