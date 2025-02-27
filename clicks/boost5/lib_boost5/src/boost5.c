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
 * @file boost5.c
 * @brief Boost 5 Click Driver.
 */

#include "boost5.h"

void boost5_cfg_setup ( boost5_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = BOOST5_VREF_DEFAULT;
}

err_t boost5_init ( boost5_t *ctx, boost5_cfg_t *cfg ) 
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
    digital_out_low ( &ctx->en );
    Delay_1sec ( );

    return ADC_SUCCESS;
}

err_t boost5_read_adc_raw ( boost5_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t boost5_read_adc_volt ( boost5_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t boost5_read_adc_volt_avg ( boost5_t *ctx, uint16_t num_conv, float *volt_avg ) 
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( BOOST5_OK == boost5_read_adc_volt ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            timeout_cnt = 0;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > BOOST5_TIMEOUT_MS )
        {
            return BOOST5_ERROR;
        }
    }
    *volt_avg = ( voltage_sum / num_conv );
    return BOOST5_OK;
}

void boost5_enable_device ( boost5_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_1sec ( );
}

void boost5_disable_device ( boost5_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_1sec ( );
}

void boost5_reset_device ( boost5_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
    digital_out_high ( &ctx->en );
    Delay_1sec ( );
}

err_t boost5_read_vout ( boost5_t *ctx, float *vout ) 
{
    float adc_volt = 0;
    err_t error_flag = boost5_read_adc_volt_avg ( ctx, BOOST5_NUM_CONVERSIONS, &adc_volt );
    if ( ( BOOST5_OK == error_flag ) && ( NULL != vout ) )
    {
        *vout = adc_volt * ( BOOST5_R15_KOHM + BOOST5_R16_KOHM ) / BOOST5_R16_KOHM;
        if ( ( *vout < ( BOOST5_VOUT_MIN - BOOST5_VOUT_OFFSET ) ) || 
             ( *vout > ( BOOST5_VOUT_MAX + BOOST5_VOUT_OFFSET ) ) )
        {
            *vout = 0;
            error_flag = BOOST5_ERROR;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
