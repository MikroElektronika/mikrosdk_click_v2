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

#include "shtan.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void shtan_cfg_setup ( shtan_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 3.3;
    cfg->vdd        = 3.3;
}

err_t shtan_init ( shtan_t *ctx, shtan_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );

    if ( cfg->vdd == 0 )
    {
        ctx->vdd = 3.3;

        return ADC_ERROR;
    }

    ctx->vdd = cfg->vdd;

    return ADC_SUCCESS;
}

err_t shtan_read_adc ( shtan_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t shtan_read_an_voltage ( shtan_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t shtan_meas_temperature ( shtan_t *ctx, float *data_out, shtan_temp_mode_t sel )
{
    float an_vol = 0;

    if ( shtan_read_an_voltage( ctx, &an_vol ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    an_vol /= ctx->vdd;

    if ( sel == SHTAN_SET_TEMP_MODE_DEG_C )
    {
        an_vol *= 218.75;
        an_vol -= 66.875;
    }
    else
    {
        an_vol *= 393.75;
        an_vol -= 88.375;
    }

    *data_out = an_vol;

    return ADC_SUCCESS;
}

err_t shtan_meas_humidity ( shtan_t *ctx, float *data_out )
{
    float an_vol = 0;

    if ( shtan_read_an_voltage( ctx, &an_vol ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    an_vol /= ctx->vdd;
    an_vol *= 125;
    an_vol -= 12.5;

    *data_out = an_vol;

    return ADC_SUCCESS;
}

void shtan_set_mode ( shtan_t *ctx, shtan_adc_mode_t sel )
{
    if ( sel == SHTAN_SET_ADC_MODE_TEMP )
    {
        digital_out_low( &ctx->cs );
    }
    else
    {
        digital_out_high( &ctx->cs );
    }
}

void shtan_reset ( shtan_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

// ------------------------------------------------------------------------ END
