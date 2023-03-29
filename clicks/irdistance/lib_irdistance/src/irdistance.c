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

#include "irdistance.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void irdistance_cfg_setup ( irdistance_cfg_t *cfg )
{
    cfg->out = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref       = 3.3;
}

err_t irdistance_init ( irdistance_t *ctx, irdistance_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->out;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    digital_out_init( &ctx->en, cfg->en );
    digital_out_high( &ctx->en );

    return ADC_SUCCESS;
}

void irdistance_enable_device ( irdistance_t *ctx )
{
    digital_out_high( &ctx->en );
}

void irdistance_disable_device ( irdistance_t *ctx )
{
    digital_out_low( &ctx->en );
}

err_t irdistance_read_adc ( irdistance_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t irdistance_get_pin_voltage ( irdistance_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ------------------------------------------------------------------------- END
