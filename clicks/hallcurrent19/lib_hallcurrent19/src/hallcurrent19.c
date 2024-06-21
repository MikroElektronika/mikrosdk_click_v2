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
 * @file hallcurrent19.c
 * @brief Hall Current 19 Click Driver.
 */

#include "hallcurrent19.h"

void hallcurrent19_cfg_setup ( hallcurrent19_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->oc2 = HAL_PIN_NC;
    cfg->oc1 = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t hallcurrent19_init ( hallcurrent19_t *ctx, hallcurrent19_cfg_t *cfg ) 
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

    digital_in_init( &ctx->oc2, cfg->oc2 );
    digital_in_init( &ctx->oc1, cfg->oc1 );

    return ADC_SUCCESS;
}

err_t hallcurrent19_read_an_pin_value ( hallcurrent19_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t hallcurrent19_read_voltage ( hallcurrent19_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

uint8_t hallcurrent19_get_oc1 ( hallcurrent19_t *ctx )
{
    return digital_in_read( &ctx->oc1 );
}

uint8_t hallcurrent19_get_oc2 ( hallcurrent19_t *ctx )
{
    return digital_in_read( &ctx->oc2 );
}

err_t hallcurrent19_set_zero_ref ( hallcurrent19_t *ctx )
{
    err_t error_flag = HALLCURRENT19_OK;
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;

    while ( cnt < HALLCURRENT19_NUM_CONVERSIONS )
    {
        if ( HALLCURRENT19_OK == hallcurrent19_read_voltage( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        else
        {
            timeout_cnt++;
            if ( timeout_cnt >= HALLCURRENT19_NUM_CONVERSIONS )
            {
                return HALLCURRENT19_ERROR;
            }
        }
    }
    ctx->zero_vref = ( float ) ( voltage_sum / HALLCURRENT19_NUM_CONVERSIONS );

    return error_flag;
}

err_t hallcurrent19_get_current ( hallcurrent19_t *ctx, float *current ) 
{
    err_t error_flag = HALLCURRENT19_OK;

    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < HALLCURRENT19_NUM_CONVERSIONS )
    {
        if ( HALLCURRENT19_OK == hallcurrent19_read_voltage( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        else
        {
            timeout_cnt++;
            if ( timeout_cnt >= HALLCURRENT19_NUM_CONVERSIONS )
            {
                return HALLCURRENT19_ERROR;
            }
        }
    }
    *current = ( ( voltage_sum / HALLCURRENT19_NUM_CONVERSIONS ) - 
                 ctx->zero_vref ) / HALLCURRENT19_SENSITIVITY_V_TO_A;

    return error_flag; 
}

// ------------------------------------------------------------------------- END
