/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file rfmeter3.c
 * @brief RF Meter 3 Click Driver.
 */

#include "rfmeter3.h"

void rfmeter3_cfg_setup ( rfmeter3_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t rfmeter3_init ( rfmeter3_t *ctx, rfmeter3_cfg_t *cfg ) 
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->en, cfg->en );

    return ADC_SUCCESS;
}

err_t rfmeter3_read_an_pin_value ( rfmeter3_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t rfmeter3_read_an_pin_voltage ( rfmeter3_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void rfmeter3_enable_device ( rfmeter3_t *ctx ) 
{
    digital_out_high ( &ctx->en );
}

void rfmeter3_disable_device ( rfmeter3_t *ctx ) 
{
    digital_out_low ( &ctx->en );
}

err_t rfmeter3_get_rf_input_power ( rfmeter3_t *ctx, float *data_out ) 
{
    float voltage = 0;
    
    err_t error_flag = analog_in_read_voltage( &ctx->adc, &voltage );
    
    if ( voltage < RFMETER3_NO_SIGNAL_VOLTAGE )
    {
        return RFMETER3_ERROR;
    }
    
    *data_out = ( voltage - RFMETER3_NO_SIGNAL_VOLTAGE ) / RFMETER3_OUTPUT_SLOPE - RFMETER3_DBM_OFFSET;
    return error_flag;
}

// ------------------------------------------------------------------------- END
