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
 * @file ookrx.c
 * @brief OOK RX Click Driver.
 */

#include "ookrx.h"

void ookrx_cfg_setup ( ookrx_cfg_t *cfg ) 
{
    cfg->rssi = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->sqc = HAL_PIN_NC;
    cfg->dout = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = OOKRX_RSSI_VREF_3V3;
}

err_t ookrx_init ( ookrx_t *ctx, ookrx_cfg_t *cfg ) 
{
    err_t error_flag = OOKRX_OK;

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->rssi;

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

    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->sqc, cfg->sqc );

    error_flag |= digital_in_init( &ctx->dout, cfg->dout );

    return error_flag;
}

void ookrx_enable_squelch ( ookrx_t *ctx )
{
    digital_out_low( &ctx->sqc );
}

void ookrx_disable_squelch ( ookrx_t *ctx )
{
    digital_out_high( &ctx->sqc );
}

void ookrx_enable_device ( ookrx_t *ctx )
{
    digital_out_high( &ctx->en );
}

void ookrx_disable_device ( ookrx_t *ctx )
{
    digital_out_low( &ctx->en );
}

uint8_t ookrx_get_data_pin ( ookrx_t *ctx )
{
    return digital_in_read( &ctx->dout );
}

err_t ookrx_read_rssi_voltage ( ookrx_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ------------------------------------------------------------------------- END
