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

#include "buck2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck2_cfg_setup ( buck2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->voset0 = HAL_PIN_NC;
    cfg->voset1 = HAL_PIN_NC;
    cfg->en     = HAL_PIN_NC;
    cfg->fq     = HAL_PIN_NC;
    cfg->pg     = HAL_PIN_NC;
}

BUCK2_RETVAL buck2_init ( buck2_t *ctx, buck2_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->voset0, cfg->voset0 );
    digital_out_init( &ctx->voset1, cfg->voset1 );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->fq, cfg->fq );

    // Input pins

    digital_in_init( &ctx->pg, cfg->pg );

    return BUCK2_OK;
}

void buck2_default_cfg ( buck2_t *ctx )
{
    // Click default configuration

    buck2_set_power_mode( ctx, BUCK2_MODE_ACTIVE );
    buck2_set_output_voltage( ctx, BUCK2_SET_VOLTAGE_3300mV );
}

void buck2_set_voset ( buck2_t *ctx, uint8_t channel, uint8_t state )
{
    if ( channel == BUCK2_VOSET_CH_0 )
    {
        digital_out_write( &ctx->voset0, state );
    }
    else
    {
        digital_out_write( &ctx->voset1, state );
    }
}

void busk2_set_frequency ( buck2_t *ctx, uint8_t freq )
{
    digital_out_write( &ctx->fq, freq );
}

void buck2_set_power_mode ( buck2_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->en, mode );
}

void back2_device_reset ( buck2_t *ctx )
{
    buck2_set_power_mode( ctx, BUCK2_VOSET_LOW );
    Delay_100ms( );
    buck2_set_power_mode( ctx, BUCK2_VOSET_HIGH );
    Delay_100ms( );
}

uint8_t buck2_get_power_good ( buck2_t *ctx  )
{
    return digital_in_read( &ctx->pg );
}

void buck2_set_output_voltage ( buck2_t *ctx , uint8_t voltage )
{
    back2_device_reset( ctx );
    
    switch ( voltage )
    {
        case BUCK2_SET_VOLTAGE_3300mV:
        {
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_0, 0 );
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_1, 0 );
            busk2_set_frequency( ctx, BUCK2_FREQ_790KHz );
            break;
        }
        case BUCK2_SET_VOLTAGE_2500mV:
        {
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_0, 1 );
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_1, 0 );
            busk2_set_frequency( ctx, BUCK2_FREQ_790KHz );
            break;
        }
        case BUCK2_SET_VOLTAGE_1800mV:
        {
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_0, 0 );
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_1, 1 );
            busk2_set_frequency( ctx, BUCK2_FREQ_565KHz );
            break;
        }
        case BUCK2_SET_VOLTAGE_1500mV:
        {
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_0, 1 );
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_1, 1 );
            busk2_set_frequency( ctx, BUCK2_FREQ_565KHz );
            break;
        }
        default:
        {
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_0, 0 );
            buck2_set_voset ( ctx, BUCK2_VOSET_CH_1, 0 );
            busk2_set_frequency( ctx, BUCK2_FREQ_790KHz );
            break;   
        }
    }
}

// ------------------------------------------------------------------------- END

