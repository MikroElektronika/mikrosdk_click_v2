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
 * @file bihall247bn.c
 * @brief BI Hall 2 47BN Click Driver.
 */

#include "bihall247bn.h"

void bihall247bn_cfg_setup ( bihall247bn_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = BIHALL247BN_VREF;
}

err_t bihall247bn_init ( bihall247bn_t *ctx, bihall247bn_cfg_t *cfg ) 
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

err_t bihall247bn_read_raw_adc ( bihall247bn_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t bihall247bn_read_voltage ( bihall247bn_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t bihall247bn_read_voltage_avg ( bihall247bn_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    if ( ( 0 == num_conv ) || ( NULL == voltage_avg ) )
    {
        return BIHALL247BN_ERROR;
    }
    while ( cnt < num_conv )
    {
        if ( BIHALL247BN_OK == bihall247bn_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > BIHALL247BN_TIMEOUT_MS )
        {
            return BIHALL247BN_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return BIHALL247BN_OK;
}

err_t bihall247bn_set_vref ( bihall247bn_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void bihall247bn_enable_device ( bihall247bn_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void bihall247bn_disable_device ( bihall247bn_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t bihall247bn_get_output ( bihall247bn_t *ctx, float *output )
{
    float voltage = 0;
    if ( BIHALL247BN_ERROR == bihall247bn_read_voltage_avg ( ctx, BIHALL247BN_NUM_CONVERSIONS, &voltage ) )
    {
        return BIHALL247BN_ERROR;
    }
    if ( NULL != output )
    {
        *output = ( ( voltage - BIHALL247BN_VREF / 2 ) / BIHALL247BN_VOLTAGE_PER_GAUSS );
    }
    return BIHALL247BN_OK;
}

// ------------------------------------------------------------------------- END
