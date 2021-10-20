/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file pressure13.c
 * @brief Pressure 13 Click Driver.
 */

#include "pressure13.h"

void pressure13_cfg_setup ( pressure13_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t pressure13_init ( pressure13_t *ctx, pressure13_cfg_t *cfg ) {
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) {
        return ADC_ERROR;
    }

    return ADC_SUCCESS;
}

err_t pressure13_read_an_pin_value ( pressure13_t *ctx, uint16_t *data_out ) {
    return analog_in_read( &ctx->adc, data_out );
}

err_t pressure13_read_an_pin_voltage ( pressure13_t *ctx, float *data_out ) {
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t pressure13_get_pressure ( pressure13_t *ctx, float *data_out ){
    float pressure = 0; 
    float voltage_value = 0;
    
    if ( pressure13_read_an_pin_voltage( ctx, &voltage_value ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    pressure = voltage_value;
    pressure /= PRESSURE13_V_DD_5_0_mV;
    pressure -= PRESSURE13_GAIN_AND_OFFSET_SYMBOL_B;
    pressure /= PRESSURE13_GAIN_AND_OFFSET_SYMBOL_A;

    pressure *= PRESSURE13_CONVERT_KPAS_TO_MBAR;

    *data_out = pressure;
    return ADC_SUCCESS;
}

// ------------------------------------------------------------------------- END
