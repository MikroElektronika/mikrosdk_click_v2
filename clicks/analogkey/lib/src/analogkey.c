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

#include "analogkey.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void analogkey_cfg_setup ( analogkey_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin = HAL_PIN_NC;
    
    cfg->resolution   = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref         = 3.3;
    cfg->dev_key_flag = 1;
    cfg->dev_max_adc = 1024;
    cfg->dev_prec = 51;

}

ANALOGKEY_RETVAL analogkey_init ( analogkey_t *ctx, analogkey_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;

    if (  analog_in_open( &ctx->adc, &adc_cfg ) != ACQUIRE_FAIL )
    {
        return ANALOGKEY_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    ctx->key_flag = cfg->dev_key_flag;
    ctx->max_adc = cfg->dev_max_adc;
    ctx->prec = cfg->dev_prec;

    return ANALOGKEY_OK;
}

analogkey_data_t analogkey_generic_read ( analogkey_t *ctx )
{
    analogkey_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

uint8_t analogkey_get_key ( analogkey_t* ctx, uint16_t adc_value )
{
    if ( adc_value >= ( ctx->max_adc / 6 - ctx->prec ) && adc_value <= ( ctx->max_adc / 6 + ctx->prec ) )
    {
        return ANALOGKEY_TOUCH_KEY_6;
    }
    else if ( adc_value >= ( ctx->max_adc / 6 * 2 - ctx->prec ) && adc_value <= ( ctx->max_adc / 6 * 2 + ctx->prec ) )
    {
        return ANALOGKEY_TOUCH_KEY_5;
    }
    else if ( adc_value >= ( ctx->max_adc / 6 * 3 - ctx->prec ) && adc_value <= ( ctx->max_adc / 6 * 3 + ctx->prec ) )
    {
        return ANALOGKEY_TOUCH_KEY_4;
    }
    else if ( adc_value >= ( ctx->max_adc / 6 * 4 - ctx->prec ) && adc_value <= ( ctx->max_adc / 6 * 4 + ctx->prec ) )
    {
        return ANALOGKEY_TOUCH_KEY_3;
    }
    else if ( adc_value >= ( ctx->max_adc / 6 * 5 - ctx->prec ) && adc_value <= ( ctx->max_adc / 6 * 5 + ctx->prec ) )
    {
        return ANALOGKEY_TOUCH_KEY_2;
    }
    else if ( adc_value >= ( ctx->max_adc - ctx->prec ) && adc_value <= ( ctx->max_adc + ctx->prec ) )
    {
        return ANALOGKEY_TOUCH_KEY_1;
    }

    return ANALOGKEY_NO_TOUCH;
}

void analogkey_set_resolution ( analogkey_t* ctx, uint8_t resolution )
{
    if ( resolution == ANALOGKEY_ADC_RESOLUTION_10bit )
    {
        ctx->max_adc = 1023;
        ctx->prec = 51;
    }
    else
    {
        ctx->max_adc = 4095;
        ctx->prec = 205;
    }
}

// ------------------------------------------------------------------------- END

