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
 * @file profet10a.c
 * @brief PROFET 10A Click Driver.
 */

#include "profet10a.h"

void profet10a_cfg_setup ( profet10a_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->den   = HAL_PIN_NC;
    cfg->in = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 3.3;
}

err_t profet10a_init ( profet10a_t *ctx, profet10a_cfg_t *cfg ) 
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

    digital_out_init( &ctx->den, cfg->den );
    digital_out_init( &ctx->in, cfg->in );
    
    ctx->rsens = 1200;
    ctx->kilis = 5450;

    return ADC_SUCCESS;
}

err_t profet10a_read_an_pin_value ( profet10a_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t profet10a_read_an_pin_voltage ( profet10a_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t profet10a_set_mode ( profet10a_t *ctx, uint8_t mode )
{
    err_t ret_val = PROFET10A_ERROR;
    switch ( mode )
    {
        case PROFET10A_MODE_OFF:
        case PROFET10A_DIAGNOSTIC_OFF:
        {
            digital_out_low( &ctx->den );
            digital_out_low( &ctx->in );
            ret_val = PROFET10A_OK;
            break;
        }
        case PROFET10A_MODE_ON:
        {
            digital_out_low( &ctx->den );
            digital_out_high( &ctx->in );
            ret_val = PROFET10A_OK;
            break;
        }
        case PROFET10A_DIAGNOSTIC_ON:
        {
            digital_out_high( &ctx->den );
            digital_out_high( &ctx->in );
            ret_val = PROFET10A_OK;
            break;
        }
        default:
            break;
    }
    
    if ( PROFET10A_OK == ret_val )
    {
        ctx->mode = mode;
    }
    
    return ret_val;
}

// ------------------------------------------------------------------------- END
