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

#include "vibrasense.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 


/**
 * @brief Reset delay function.
 * @note Delay 100 ms.
**/
void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void vibrasense_cfg_setup ( vibrasense_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

VIBRASENSE_RETVAL vibrasense_init ( vibrasense_t *ctx, vibrasense_cfg_t *cfg )
{
    // Output pins 
    
    digital_out_init( &ctx->en, cfg->en );
    
    // Input pins
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return VIBRASENSE_OK;
}

// Enable vibra sense
void vibrasense_set_mode ( vibrasense_t *ctx, uint8_t en_mode )
{
    if ( en_mode == VIBRASENSE_ENABLE )
    {
        digital_out_high( &ctx->en );
    }
    
    if ( en_mode == VIBRASENSE_DISABLE )
    {
        digital_out_low( &ctx->en );
    }
}

// Reset vibra sense
void vibrasense_reset ( vibrasense_t *ctx )
{
    digital_out_low( &ctx->en );
    dev_reset_delay ( );
    digital_out_high( &ctx->en );
    dev_reset_delay ( );
}

// Check interrupt
uint8_t vibrasense_check_interrupt ( vibrasense_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void dev_reset_delay ( void )
{
    Delay_100ms( );
}


// ------------------------------------------------------------------------- END

