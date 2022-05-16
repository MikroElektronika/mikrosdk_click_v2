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
 * @file analogmux5.c
 * @brief Analog MUX 5 Click Driver.
 */

#include "analogmux5.h"

void analogmux5_cfg_setup ( analogmux5_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;

    cfg->en   = HAL_PIN_NC;
    cfg->a0 = HAL_PIN_NC;
    cfg->a1 = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t analogmux5_init ( analogmux5_t *ctx, analogmux5_cfg_t *cfg ) 
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
    digital_out_init( &ctx->a0, cfg->a0 );
    digital_out_init( &ctx->a1, cfg->a1 );
    
    digital_out_low( &ctx->en );
    digital_out_low( &ctx->a0 );
    digital_out_low( &ctx->a1 );

    return ADC_SUCCESS;
}

err_t analogmux5_default_cfg ( analogmux5_t *ctx ) 
{
    err_t error_flag = ANALOGMUX5_OK;
    
    analogmux5_enable( ctx );
    
    analogmux5_select_ch( ctx, ANALOGMUX5_SEL_CH_1 );

    return error_flag;
}

void analogmux5_enable ( analogmux5_t *ctx )
{
     digital_out_high( &ctx->en );
}

void analogmux5_disable ( analogmux5_t *ctx )
{
     digital_out_low( &ctx->en );
}

err_t analogmux5_select_ch ( analogmux5_t *ctx, uint8_t ch_select ) 
{
    err_t error_flag = ANALOGMUX5_OK;
    
    switch ( ch_select ) 
    {
        case ANALOGMUX5_SEL_CH_1: 
        {
            digital_out_low( &ctx->a0 );
            digital_out_low( &ctx->a1 );
            break;
        }
        case ANALOGMUX5_SEL_CH_2: 
        {
            digital_out_high( &ctx->a0 );
            digital_out_low( &ctx->a1 );
            break;
        }
        case ANALOGMUX5_SEL_CH_3: 
        {
            digital_out_low( &ctx->a0 );
            digital_out_high( &ctx->a1 );
            break;
        }
        case ANALOGMUX5_SEL_CH_4: 
        {
            digital_out_high( &ctx->a0 );
            digital_out_high( &ctx->a1 );
            break;
        }

        default: 
        {
            digital_out_low( &ctx->a0 );
            digital_out_low( &ctx->a1 );
            error_flag = ANALOGMUX5_ERROR;
            break;
        }
    }
    
    return error_flag;
}

err_t analogmux5_read_an_pin_value ( analogmux5_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t analogmux5_read_an_pin_voltage ( analogmux5_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ------------------------------------------------------------------------- END
