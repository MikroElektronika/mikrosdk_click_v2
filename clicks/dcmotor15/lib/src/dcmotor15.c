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
 * @file dcmotor15.c
 * @brief DC Motor 15 Click Driver.
 */

#include "dcmotor15.h"

void dcmotor15_cfg_setup ( dcmotor15_cfg_t *cfg )
{
    cfg->ipr  = HAL_PIN_NC;
    cfg->slp  = HAL_PIN_NC;
    cfg->in2  = HAL_PIN_NC;
    cfg->in1  = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; 
    cfg->vref       = 3.3;
}

err_t dcmotor15_init ( dcmotor15_t *ctx, dcmotor15_cfg_t *cfg ) 
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->ipr;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->slp, cfg->slp );
    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->in1, cfg->in1 );

    digital_in_init( &ctx->flt, cfg->flt );

    return ADC_SUCCESS;
}

void dcmotor15_default_cfg ( dcmotor15_t *ctx ) 
{
    dcmotor15_stop ( ctx );
}

err_t dcmotor15_read_an_pin_value ( dcmotor15_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t dcmotor15_read_an_pin_voltage ( dcmotor15_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void dcmotor15_set_slp_pin_state ( dcmotor15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->slp, state );
}

void dcmotor15_set_in1_pin_state ( dcmotor15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in1, state );
}

void dcmotor15_set_in2_pin_state ( dcmotor15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->in2, state );
}

uint8_t dcmotor15_fault_check ( dcmotor15_t *ctx )
{
    return digital_in_read ( &ctx->flt );
}

void dcmotor15_forward ( dcmotor15_t *ctx )
{
    dcmotor15_set_slp_pin_state( ctx, DCMOTOR15_HIGH );
    dcmotor15_set_in1_pin_state( ctx, DCMOTOR15_HIGH );
    dcmotor15_set_in2_pin_state( ctx, DCMOTOR15_HIGH );
}

void dcmotor15_reverse ( dcmotor15_t *ctx )
{
    dcmotor15_set_slp_pin_state( ctx, DCMOTOR15_HIGH );
    dcmotor15_set_in1_pin_state( ctx, DCMOTOR15_HIGH );
    dcmotor15_set_in2_pin_state( ctx, DCMOTOR15_LOW );
}

void dcmotor15_brake ( dcmotor15_t *ctx )
{
    dcmotor15_set_slp_pin_state( ctx, DCMOTOR15_HIGH );
    dcmotor15_set_in1_pin_state( ctx, DCMOTOR15_LOW );
    dcmotor15_set_in2_pin_state( ctx, DCMOTOR15_LOW );
}

void dcmotor15_stop ( dcmotor15_t *ctx )
{
    dcmotor15_set_slp_pin_state( ctx, DCMOTOR15_LOW );
}

float dcmotor15_get_current ( dcmotor15_t *ctx, uint16_t num_of_conv )
{
    float voltage = 0;
    float current = 0;
    uint16_t tmp_num = num_of_conv;
    for ( uint16_t cnt = 0; cnt < tmp_num; cnt++ ) 
    {
        dcmotor15_read_an_pin_voltage ( ctx, &voltage );
        current += voltage;
    }
    current /= ( float ) tmp_num;
    current /= ( float ) ( DCMOTOR15_RIPROP_OHM * DCMOTOR15_AIPROP_AMP );
    
    return current;
}

// ------------------------------------------------------------------------- END
