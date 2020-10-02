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

#include "mic23099.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mic23099_cfg_setup ( mic23099_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

MIC23099_RETVAL mic23099_init ( mic23099_t *ctx, mic23099_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    

    return MIC23099_OK;
}

void mic23099_default_cfg ( mic23099_t *ctx )
{
    // Reset MIC23099
    
    mic23099_reset( ctx );
    dev_comm_delay( );
    
    // Enable MIC23099
    
    mic23099_set_enable( ctx, MIC23099_ENABLE );
    dev_comm_delay( );
}

void mic23099_set_enable ( mic23099_t *ctx, uint8_t en_mode )
{
    if ( en_mode == MIC23099_DISABLE )
    {
        digital_out_low( &ctx->en );    
    }
    
    if ( en_mode == MIC23099_ENABLE )
    {
        digital_out_high( &ctx->en );    
    }
}

void mic23099_reset ( mic23099_t *ctx )
{
    digital_out_low( &ctx->en );
    dev_comm_delay( );
    digital_out_high( &ctx->en );
    dev_comm_delay( );
}

uint8_t mic23099_check_power_good ( mic23099_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

