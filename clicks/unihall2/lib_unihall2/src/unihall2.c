/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file unihall2.c
 * @brief UNI Hall 2 Click Driver.
 */

#include "unihall2.h"

void unihall2_cfg_setup ( unihall2_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = UNIHALL2_VREF_3V3;
}

err_t unihall2_init ( unihall2_t *ctx, unihall2_cfg_t *cfg ) 
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

    ctx->vref = cfg->vref;

    digital_out_init( &ctx->en, cfg->en );
    
    /* Enable device */
    digital_out_high( &ctx->en );

    /* At least 10us wait time after enabling the device is needed for valid output */
    Delay_1ms( );

    return ADC_SUCCESS;
}

err_t unihall2_read_raw_adc ( unihall2_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t unihall2_read_voltage ( unihall2_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t unihall2_read_voltage_avg ( unihall2_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    if ( 0 == num_conv )
    {
        return UNIHALL2_ERROR;
    }
    while ( cnt < num_conv )
    {
        if ( UNIHALL2_OK == unihall2_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > UNIHALL2_TIMEOUT_MS )
        {
            return UNIHALL2_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return UNIHALL2_OK;
}

err_t unihall2_set_vref ( unihall2_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t unihall2_read_field ( unihall2_t *ctx, float *field )
{
    float voltage = 0;
    err_t error_flag = unihall2_read_voltage_avg ( ctx, UNIHALL2_NUM_CONV, &voltage );
    if ( UNIHALL2_OK == error_flag )
    {
        /*
         * In linear mode of operation (datasheet page 14, fig. 10):
         * 
         * V_OUT = ( B_IN * SENS ) + V_OUT(QVO)
         *  - V_OUT(QVO) = 0.33V -> output voltage when B_IN = 0G (  datasheet page 10 )
         *  - SENS = 4.7mV/G -> sensor sensitivity ( datasheet page 10 )
         * 
         * => B = ( V_OUT − QVO ) / SENS
         */
        *field = ( voltage - UNIHALL2_QVO_3V3 ) / UNIHALL2_SENS_3V3;
    }
    return error_flag;
}

void unihall2_enable_device ( unihall2_t *ctx )
{
    digital_out_high( &ctx->en );
}

void unihall2_disable_device ( unihall2_t *ctx )
{
    digital_out_low( &ctx->en );
}

// ------------------------------------------------------------------------- END
