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
 * @file tempiso.c
 * @brief Temp ISO Click Driver.
 */

#include "tempiso.h"

void tempiso_cfg_setup ( tempiso_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = TEMPISO_VREF_3V3;
}

err_t tempiso_init ( tempiso_t *ctx, tempiso_cfg_t *cfg ) 
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

    return ADC_SUCCESS;
}

err_t tempiso_read_raw_adc ( tempiso_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t tempiso_read_voltage ( tempiso_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t tempiso_read_voltage_avg ( tempiso_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < TEMPISO_NUM_CONVERSIONS )
    {
        if ( TEMPISO_OK == tempiso_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > TEMPISO_TIMEOUT_MS )
        {
            return TEMPISO_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / TEMPISO_NUM_CONVERSIONS );
    return TEMPISO_OK;
}

err_t tempiso_set_vref ( tempiso_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t tempiso_read_temperature ( tempiso_t *ctx, float *data_out ) 
{
    float voltage = 0;
    err_t error_flag = tempiso_read_voltage_avg ( ctx, TEMPISO_NUM_CONVERSIONS, &voltage );
    if ( TEMPISO_OK == error_flag )
    {
        *data_out = ( voltage - TEMPISO_TEMP_ZERO_OFFSET_V ) / TEMPISO_TEMP_SENS_V_PER_C;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
