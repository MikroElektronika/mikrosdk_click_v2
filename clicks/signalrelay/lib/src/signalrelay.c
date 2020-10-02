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

#include "signalrelay.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void signalrelay_cfg_setup ( signalrelay_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->re1 = HAL_PIN_NC;
    cfg->re2 = HAL_PIN_NC;
    cfg->re3 = HAL_PIN_NC;
    cfg->re4 = HAL_PIN_NC;
}

SIGNALRELAY_RETVAL signalrelay_init ( signalrelay_t *ctx, signalrelay_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->re1, cfg->re1 );
    digital_out_init( &ctx->re2, cfg->re2 );
    digital_out_init( &ctx->re3, cfg->re3 );
    digital_out_init( &ctx->re4, cfg->re4 );

    return SIGNALRELAY_OK;
}

void signalrelay_default_cfg ( signalrelay_t *ctx )
{
    // Click default configuration

    signalrelay_relay_state( ctx, SIGNALRELAY_RELAY_1, SIGNALRELAY_STATE_OFF );
    signalrelay_relay_state( ctx, SIGNALRELAY_RELAY_2, SIGNALRELAY_STATE_OFF );
    signalrelay_relay_state( ctx, SIGNALRELAY_RELAY_3, SIGNALRELAY_STATE_OFF );
    signalrelay_relay_state( ctx, SIGNALRELAY_RELAY_4, SIGNALRELAY_STATE_OFF ); 
}

void signalrelay_relay_state( signalrelay_t *ctx, uint8_t relay, uint8_t state )
{
   switch ( relay )
   {
       case SIGNALRELAY_RELAY_1:
       {
           digital_out_write( &ctx->re1, state );
           break;
       }
       case SIGNALRELAY_RELAY_2:
       {
           digital_out_write( &ctx->re2, state );
           break;
       }
       case SIGNALRELAY_RELAY_3:
       {
           digital_out_write( &ctx->re3, state );
           break;
       }
       case SIGNALRELAY_RELAY_4:
       {
           digital_out_write( &ctx->re4, state );
           break;
       }
   }
}

// ------------------------------------------------------------------------- END

