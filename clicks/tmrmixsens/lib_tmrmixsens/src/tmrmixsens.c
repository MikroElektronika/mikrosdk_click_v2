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

#include "tmrmixsens.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void tmrmixsens_cfg_setup ( tmrmixsens_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->omn = HAL_PIN_NC;
    cfg->bi  = HAL_PIN_NC;

    cfg->resolution   = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref         = 3.3;
}

TMRMIXSENS_RETVAL tmrmixsens_init ( tmrmixsens_t *ctx, tmrmixsens_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return TMRMIXSENS_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // Input pins

    digital_in_init( &ctx->omn, cfg->omn );
    digital_in_init( &ctx->bi, cfg->bi );

    return TMRMIXSENS_OK;
}

tmrmixsens_data_t tmrmixsens_generic_read ( tmrmixsens_t *ctx )
{
    tmrmixsens_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

uint8_t tmrmixsens_get_omnipolar ( tmrmixsens_t *ctx )
{
    return digital_in_read( &ctx->omn );
}

uint8_t tmrmixsens_get_bipolar ( tmrmixsens_t *ctx )
{
    return digital_in_read( &ctx->bi );
}

// ------------------------------------------------------------------------- END

