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
 * @file mux4.c
 * @brief MUX 4 Click Driver.
 */

#include "mux4.h"

void mux4_cfg_setup ( mux4_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->s2 = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->s0 = HAL_PIN_NC;
    cfg->s1 = HAL_PIN_NC;

    /**
     * Should leave this by default for portability purposes. 
     * Different MCU's have different resolutions. 
     * Change only if necessary.
    */
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; 
    cfg->vref       = 3.3;
}

err_t mux4_init ( mux4_t *ctx, mux4_cfg_t *cfg ) 
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

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

    digital_out_init( &ctx->s2, cfg->s2 );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->s0, cfg->s0 );
    digital_out_init( &ctx->s1, cfg->s1 );

    return ADC_SUCCESS;
}

err_t mux4_read_an_pin_value ( mux4_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t mux4_read_an_pin_voltage ( mux4_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void mux4_enable_input ( mux4_t *ctx, uint8_t en_state ) 
{
    digital_out_write( &ctx->en, en_state );
}

void mux4_select_input ( mux4_t *ctx, uint8_t input ) 
{
    switch ( input )
    {
        case MUX4_SELECT_INPUT_1:
        {
            digital_out_low( &ctx->s0 );
            digital_out_low( &ctx->s1 );
            digital_out_low( &ctx->s2 );
            break;
        }
        case MUX4_SELECT_INPUT_2:
        {
            digital_out_high( &ctx->s0 );
            digital_out_low( &ctx->s1 );
            digital_out_low( &ctx->s2 );
            break;
        }
        case MUX4_SELECT_INPUT_3:
        {
            digital_out_low( &ctx->s0 );
            digital_out_high( &ctx->s1 );
            digital_out_low( &ctx->s2 );
            break;
        }
        case MUX4_SELECT_INPUT_4:
        {
            digital_out_high( &ctx->s0 );
            digital_out_high( &ctx->s1 );
            digital_out_low( &ctx->s2 );
            break;
        }
        case MUX4_SELECT_INPUT_5:
        {
            digital_out_low( &ctx->s0 );
            digital_out_low( &ctx->s1 );
            digital_out_high( &ctx->s2 );
            break;
        }
        case MUX4_SELECT_INPUT_6:
        {
            digital_out_high( &ctx->s0 );
            digital_out_low( &ctx->s1 );
            digital_out_high( &ctx->s2 );
            break;
        }
        case MUX4_SELECT_INPUT_7:
        {
            digital_out_low( &ctx->s0 );
            digital_out_high( &ctx->s1 );
            digital_out_high( &ctx->s2 );
            break;
        }
        case MUX4_SELECT_INPUT_8:
        {
            digital_out_high( &ctx->s0 );
            digital_out_high( &ctx->s1 );
            digital_out_high( &ctx->s2 );
            break;
        }
        default:
        {
            digital_out_low( &ctx->s0 );
            digital_out_low( &ctx->s1 );
            digital_out_low( &ctx->s2 );
            break;
        }
    }
}


// ------------------------------------------------------------------------- END
