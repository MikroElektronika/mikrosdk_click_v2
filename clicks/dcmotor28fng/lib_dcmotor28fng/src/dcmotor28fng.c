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
 * @file dcmotor28fng.c
 * @brief DC Motor 28 FNG Click Driver.
 */

#include "dcmotor28fng.h"

void dcmotor28fng_cfg_setup ( dcmotor28fng_cfg_t *cfg )
{
    cfg->isense = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->in1   = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = DCMOTOR28FNG_VREF_DEFAULT;
}

err_t dcmotor28fng_init ( dcmotor28fng_t *ctx, dcmotor28fng_cfg_t *cfg ) 
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->isense;

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

    digital_out_init( &ctx->sleep, cfg->sleep );
    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_low ( &ctx->sleep );
    digital_out_low ( &ctx->in1 );
    digital_out_low ( &ctx->in2 );

    digital_in_init( &ctx->fault, cfg->fault );
    Delay_100ms ( );
    digital_out_high ( &ctx->sleep );
    Delay_100ms ( );
    return ADC_SUCCESS;
}

err_t dcmotor28fng_read_adc_raw ( dcmotor28fng_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t dcmotor28fng_read_adc_volt ( dcmotor28fng_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t dcmotor28fng_read_adc_volt_avg ( dcmotor28fng_t *ctx, uint16_t num_conv, float *volt_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( DCMOTOR28FNG_OK == dcmotor28fng_read_adc_volt ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            timeout_cnt = 0;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > DCMOTOR28FNG_TIMEOUT_MS )
        {
            return DCMOTOR28FNG_ERROR;
        }
    }
    *volt_avg = ( voltage_sum / num_conv );
    return DCMOTOR28FNG_OK;
}

err_t dcmotor28fng_set_adc_vref ( dcmotor28fng_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void dcmotor28fng_set_in1_pin ( dcmotor28fng_t *ctx )
{
    digital_out_high( &ctx->in1 );
}

void dcmotor28fng_clear_in1_pin ( dcmotor28fng_t *ctx )
{
    digital_out_low( &ctx->in1 );
}

void dcmotor28fng_set_in2_pin ( dcmotor28fng_t *ctx )
{
    digital_out_high( &ctx->in2 );
}

void dcmotor28fng_clear_in2_pin ( dcmotor28fng_t *ctx )
{
    digital_out_low( &ctx->in2 );
}

void dcmotor28fng_set_sleep_pin ( dcmotor28fng_t *ctx )
{
    digital_out_high( &ctx->sleep );
}

void dcmotor28fng_clear_sleep_pin ( dcmotor28fng_t *ctx )
{
    digital_out_low( &ctx->sleep );
}

uint8_t dcmotor28fng_get_fault_pin ( dcmotor28fng_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

void dcmotor28fng_drive_motor ( dcmotor28fng_t *ctx, uint8_t state )
{
    switch ( state )
    {
        case DCMOTOR28FNG_MOTOR_COAST:
        {
            digital_out_low ( &ctx->in1 );
            digital_out_low ( &ctx->in2 );
            break;
        }
        case DCMOTOR28FNG_MOTOR_FORWARD:
        {
            digital_out_high ( &ctx->in1 );
            digital_out_low ( &ctx->in2 );
            break;
        }
        case DCMOTOR28FNG_MOTOR_REVERSE:
        {
            digital_out_low ( &ctx->in1 );
            digital_out_high ( &ctx->in2 );
            break;
        }
        case DCMOTOR28FNG_MOTOR_BRAKE:
        {
            digital_out_high ( &ctx->in1 );
            digital_out_high ( &ctx->in2 );
            break;
        }
        default:
        {
            break;
        }
    }
}

err_t dcmotor28fng_calib_offset ( dcmotor28fng_t *ctx )
{
    float voltage = 0;
    dcmotor28fng_drive_motor ( ctx, DCMOTOR28FNG_MOTOR_COAST );
    Delay_1sec ( );
    Delay_1sec ( );
    err_t error_flag = dcmotor28fng_read_adc_volt_avg ( ctx, DCMOTOR28FNG_NUM_CONVERSIONS, &voltage );
    ctx->zero_curr_offset = voltage;
    return error_flag;
}

err_t dcmotor28fng_get_out_current ( dcmotor28fng_t *ctx, float *current )
{
    float voltage = 0;
    err_t error_flag = dcmotor28fng_read_adc_volt_avg ( ctx, DCMOTOR28FNG_NUM_CONVERSIONS, &voltage );
    if ( ( DCMOTOR28FNG_OK == error_flag ) && ( NULL != current ) )
    {
        voltage -= ctx->zero_curr_offset;
        if ( voltage < 0 )
        {
            voltage = 0;
        }
        *current = voltage / DCMOTOR28FNG_RISENSE_V_TO_MA;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
