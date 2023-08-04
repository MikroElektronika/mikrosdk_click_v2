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

#include "stretch.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stretch_cfg_setup ( stretch_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pwm = HAL_PIN_NC;
   
    cfg->resolution   = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref         = 3.3;
}

STRETCH_RETVAL stretch_init ( stretch_t *ctx, stretch_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;
    
    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return STRETCH_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // Output pins 

    digital_out_init( &ctx->pwm, cfg->pwm );

    return STRETCH_OK;

}

stretch_data_t stretch_generic_read ( stretch_t *ctx )
{
    stretch_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

// Turn on the LED function 
void stretch_turn_on_led( stretch_t *ctx )
{
    digital_out_high( &ctx->pwm );
}

// Turn off the LED function 
void stretch_turn_off_led( stretch_t *ctx )
{
    digital_out_low( &ctx->pwm );
}

// ------------------------------------------------------------------------- END

