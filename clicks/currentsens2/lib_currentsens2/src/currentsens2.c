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
 * @file currentsens2.c
 * @brief Current Sens 2 Click Driver.
 */

#include "currentsens2.h"

void currentsens2_cfg_setup ( currentsens2_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t currentsens2_init ( currentsens2_t *ctx, currentsens2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ADC_SUCCESS;
}

err_t currentsens2_read_an_pin_value ( currentsens2_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t currentsens2_read_an_pin_vol ( currentsens2_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

uint8_t currentsens2_get_int_pin ( currentsens2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void currentsens2_set_prim_turn_no ( currentsens2_t *ctx, uint8_t turns )
{
    ctx->no_of_turns = turns;
}

err_t currentsens2_tare ( currentsens2_t *ctx )
{
    err_t error_flag = CURRENTSENS2_OK;
    float voltage = 0;
    float voltage_sum = 0;

    for ( uint8_t n_cnt = 0; n_cnt < CURRENTSENS2_NUM_CONVERSIONS; n_cnt++ )
    {
        error_flag = currentsens2_read_an_pin_vol ( ctx, &voltage ); 
        voltage_sum += voltage;
    }

    ctx->zero_val = ( voltage_sum / CURRENTSENS2_NUM_CONVERSIONS );

    return error_flag;
}

err_t currentsens2_get_current ( currentsens2_t *ctx, float *current )
{
    err_t error_flag = CURRENTSENS2_OK;
    float voltage = 0;
    float voltage_sum = 0;

    for ( uint8_t n_cnt = 0; n_cnt < CURRENTSENS2_NUM_CONVERSIONS; n_cnt++ )
    {
        error_flag = currentsens2_read_an_pin_vol ( ctx, &voltage ); 
        voltage_sum += voltage;
    }

    voltage = ( voltage_sum / CURRENTSENS2_NUM_CONVERSIONS );

    *current = ( ( voltage - ctx->zero_val ) * CURRENTSENS2_CONV_FACTOR ) / ctx->no_of_turns;

    return error_flag;
}

// ------------------------------------------------------------------------- END
