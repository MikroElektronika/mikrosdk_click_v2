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
    cfg->an_pin = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref       = 3.3;
    cfg->vsel       = 3.3;
}

err_t analogkey_init ( analogkey_t *ctx, analogkey_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    ctx->vref = cfg->vref;
    ctx->vdiv = cfg->vref / cfg->vsel;

    return ADC_SUCCESS;
}

uint16_t analogkey_generic_read ( analogkey_t *ctx )
{
    uint16_t rx_data = 0;

    analog_in_read( &ctx->adc, &rx_data );

    return rx_data;
}

float analogkey_read_voltage ( analogkey_t *ctx )
{
    float rx_data = 0;

    analog_in_read_voltage( &ctx->adc, &rx_data );

    return rx_data;
}

analogkey_key_id_t analogkey_get_key ( analogkey_t* ctx, float an_value )
{
    float tmp = an_value * ctx->vdiv / ctx->vref;

    if ( tmp > 0.9 )
    {
        return ANALOGKEY_TOUCH_KEY_1;
    }
    else if ( tmp > 0.77 )
    {
        return ANALOGKEY_TOUCH_KEY_2;
    }
    else if ( tmp > 0.6 )
    {
        return ANALOGKEY_TOUCH_KEY_3;
    }
    else if ( tmp > 0.42 )
    {
        return ANALOGKEY_TOUCH_KEY_4;
    }
    else if ( tmp > 0.26 )
    {
        return ANALOGKEY_TOUCH_KEY_5;
    }
    else if ( tmp > 0.06 )
    {
        return ANALOGKEY_TOUCH_KEY_6;
    }

    return ANALOGKEY_TOUCH_KEY_NONE;
}

// ------------------------------------------------------------------------ END
