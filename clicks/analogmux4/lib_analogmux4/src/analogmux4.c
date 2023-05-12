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
 * @file analogmux4.c
 * @brief Analog MUX 4 Click Driver.
 */

#include "analogmux4.h"

void analogmux4_cfg_setup ( analogmux4_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->a0 = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->a2 = HAL_PIN_NC;
    cfg->a1 = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t analogmux4_init ( analogmux4_t *ctx, analogmux4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->a0, cfg->a0 );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->a2, cfg->a2 );
    digital_out_init( &ctx->a1, cfg->a1 );

    return ADC_SUCCESS;
}

err_t analogmux4_read_an_pin_value ( analogmux4_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t analogmux4_read_an_pin_voltage ( analogmux4_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void analogmux4_enable_input ( analogmux4_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void analogmux4_disable_input ( analogmux4_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void analogmux4_set_input_channel ( analogmux4_t *ctx, uint8_t channel )
{
    switch ( channel )
    {
        case ANALOGMUX4_CHANNEL_0:
        {
            digital_out_low ( &ctx->a0 );
            digital_out_low ( &ctx->a1 );
            digital_out_low ( &ctx->a2 );
            break;
        }
        case ANALOGMUX4_CHANNEL_1:
        {
            digital_out_high ( &ctx->a0 );
            digital_out_low ( &ctx->a1 );
            digital_out_low ( &ctx->a2 );
            break;
        }
        case ANALOGMUX4_CHANNEL_2:
        {
            digital_out_low ( &ctx->a0 );
            digital_out_high ( &ctx->a1 );
            digital_out_low ( &ctx->a2 );
            break;
        }
        case ANALOGMUX4_CHANNEL_3:
        {
            digital_out_high ( &ctx->a0 );
            digital_out_high ( &ctx->a1 );
            digital_out_low ( &ctx->a2 );
            break;
        }
        case ANALOGMUX4_CHANNEL_4:
        {
            digital_out_low ( &ctx->a0 );
            digital_out_low ( &ctx->a1 );
            digital_out_high ( &ctx->a2 );
            break;
        }
        case ANALOGMUX4_CHANNEL_5:
        {
            digital_out_high ( &ctx->a0 );
            digital_out_low ( &ctx->a1 );
            digital_out_high ( &ctx->a2 );
            break;
        }
        case ANALOGMUX4_CHANNEL_6:
        {
            digital_out_low ( &ctx->a0 );
            digital_out_high ( &ctx->a1 );
            digital_out_high ( &ctx->a2 );
            break;
        }
        case ANALOGMUX4_CHANNEL_7:
        {
            digital_out_high ( &ctx->a0 );
            digital_out_high ( &ctx->a1 );
            digital_out_high ( &ctx->a2 );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
