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

#include "audioamp2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audioamp2_cfg_setup ( audioamp2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->gn0   = HAL_PIN_NC;
    cfg->gn1 = HAL_PIN_NC;
    cfg->stb   = HAL_PIN_NC;
    cfg->mute = HAL_PIN_NC;
    cfg->dia = HAL_PIN_NC;
}

AUDIOAMP2_RETVAL audioamp2_init ( audioamp2_t *ctx, audioamp2_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->gn0, cfg->gn0 );
    digital_out_init( &ctx->gn1, cfg->gn1 );
    digital_out_init( &ctx->stb, cfg->stb );
    digital_out_init( &ctx->mute, cfg->mute );

    // Input pins

    digital_in_init( &ctx->dia, cfg->dia );

    return AUDIOAMP2_OK;
}

uint8_t audioamp2_set_mode ( audioamp2_t *ctx, uint8_t sel_mode )
{
    switch ( sel_mode )
    {
        case 0x00 :
        {
            digital_out_low( &ctx->stb );
            break;
        }
        case 0x01 :
        {
            digital_out_high( &ctx->stb );
            digital_out_low( &ctx->mute );
            break;
        }
        case 0x02 :
        {
            digital_out_high( &ctx->stb );
            digital_out_high( &ctx->mute );
            break;
        }
        default :
        {
            return 1;
        }
    }
    return 0;
}

uint8_t audioamp2_set_gain ( audioamp2_t *ctx, uint8_t sel_gain )
{
    switch ( sel_gain )
    {
        case 0x00 :
        {
            digital_out_low( &ctx->gn0 );
            digital_out_low( &ctx->gn1 );
            break;
        }
        case 0x01 :
        {
            digital_out_low( &ctx->gn0 );
            digital_out_high( &ctx->gn1 );
            break;
        }
        case 0x02 :
        {
            digital_out_high( &ctx->gn0 );
            digital_out_low( &ctx->gn1 );
            break;
        }
        case 0x03 :
        {
            digital_out_high( &ctx->gn0 );
            digital_out_high( &ctx->gn1 );
            break;
        }
        default :
        {
            return 1;
        }
    }
    return 0;
}

uint8_t audioamp2_check_diagnostic ( audioamp2_t *ctx )
{
    if ( digital_in_read( &ctx->dia ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ------------------------------------------------------------------------- END

