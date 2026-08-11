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
 * @file bihall2.c
 * @brief BI Hall 2 Click Driver.
 */

#include "bihall2.h"

void bihall2_cfg_setup ( bihall2_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = BIHALL2_VREF;
}

err_t bihall2_init ( bihall2_t *ctx, bihall2_cfg_t *cfg ) 
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
    Delay_1ms ( );
    digital_out_high( &ctx->en );
    Delay_10ms ( );

    return ADC_SUCCESS;
}

err_t bihall2_read_raw_adc ( bihall2_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t bihall2_read_voltage ( bihall2_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t bihall2_read_voltage_avg ( bihall2_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    if ( ( 0 == num_conv ) || ( NULL == voltage_avg ) )
    {
        return BIHALL2_ERROR;
    }
    while ( cnt < num_conv )
    {
        if ( BIHALL2_OK == bihall2_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > BIHALL2_TIMEOUT_MS )
        {
            return BIHALL2_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return BIHALL2_OK;
}

err_t bihall2_set_vref ( bihall2_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void bihall2_enable_device ( bihall2_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void bihall2_disable_device ( bihall2_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t bihall2_get_output ( bihall2_t *ctx, float *output )
{
    float voltage = 0;
    if ( BIHALL2_ERROR == bihall2_read_voltage_avg ( ctx, BIHALL2_NUM_CONVERSIONS, &voltage ) )
    {
        return BIHALL2_ERROR;
    }
    if ( NULL != output )
    {
        *output = ( ( voltage - BIHALL2_VREF / 2 ) / BIHALL2_VOLTAGE_PER_GAUSS );
    }
    return BIHALL2_OK;
}

// ------------------------------------------------------------------------- END
