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

#include "hbridge2.h"

void hbridge2_cfg_setup ( hbridge2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->gin   = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->end   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
}

HBRIDGE2_RETVAL hbridge2_init ( hbridge2_t *ctx, hbridge2_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->gin, cfg->gin );
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->end, cfg->end );
    digital_out_init( &ctx->pwm , cfg->pwm  );

    // Input pins

    digital_out_high( &ctx->gin );
    digital_out_low( &ctx->end );

    return HBRIDGE2_OK;
}

uint8_t hbridge2_set_output ( hbridge2_t *ctx, uint8_t out_state )
{
    if ( out_state & 0xFC )
        return 1;

    switch ( out_state )
    {
        case 0x00 :
        {
            digital_out_low( &ctx->dir );
            digital_out_high( &ctx->pwm );
            digital_out_high( &ctx->dir );
            digital_out_high( &ctx->pwm );

            break;
        }
        case 0x01 :
        {
            digital_out_high( &ctx->dir );
            digital_out_low( &ctx->pwm );
            digital_out_high( &ctx->dir) ;
            digital_out_high( &ctx->pwm );

            break;
        }
        case 0x02 :
        {
            digital_out_low( &ctx->dir );
            digital_out_low( &ctx->pwm );
            digital_out_high( &ctx->dir );
            digital_out_high( &ctx->pwm );

            break;
        }
        case 0x03 :
        {
            digital_out_low( &ctx->dir );
            digital_out_low( &ctx->pwm );
            digital_out_high( &ctx->dir );
            digital_out_low( &ctx->pwm );

            break;
        }
        default :
        {
            break;
        }
    }
    
    return 0;
}

void hbridge2_enable ( hbridge2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->end, state );
}

void hbridge2_set_gout ( hbridge2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->gin, state );
}

// ------------------------------------------------------------------------- END

