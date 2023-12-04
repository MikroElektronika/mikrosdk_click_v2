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
 * @file charger19.c
 * @brief Charger 19 Click Driver.
 */

#include "charger19.h"

void charger19_cfg_setup ( charger19_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->sac = HAL_PIN_NC;
    cfg->vs1 = HAL_PIN_NC;
    cfg->vs2 = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t charger19_init ( charger19_t *ctx, charger19_cfg_t *cfg ) 
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

    digital_out_init( &ctx->sac, cfg->sac );
    digital_out_init( &ctx->vs1, cfg->vs1 );
    digital_out_init( &ctx->vs2, cfg->vs2 );

    return ADC_SUCCESS;
}

err_t charger19_default_cfg ( charger19_t *ctx ) 
{
    err_t error_flag = CHARGER19_OK;
    
    error_flag |= charger19_set_vout( ctx, CHARGER19_VOUT_3V0 );
    charger19_set_ship_mode( ctx, CHARGER19_SHIP_MODE_OFF );
    
    return error_flag;
}

err_t charger19_read_an_pin_value ( charger19_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t charger19_read_an_pin_voltage ( charger19_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void charger19_set_ship_mode ( charger19_t *ctx, uint8_t ship_sel )
{
    if ( CHARGER19_SHIP_MODE_ON == ship_sel )
    {
        digital_out_high( &ctx->sac );
    }
    else
    {
        digital_out_low( &ctx->sac );
    }
}

err_t charger19_set_vout ( charger19_t *ctx, uint8_t vout_sel )
{
    err_t error_flag = CHARGER19_OK;
    switch ( vout_sel )
    {
        case ( CHARGER19_VOUT_1V8 ): 
        {
            digital_out_low( &ctx->vs1 );
            digital_out_low( &ctx->vs2 );
            break;
        }
        
        case ( CHARGER19_VOUT_2V1 ): 
        {
            digital_out_high( &ctx->vs1 );
            digital_out_low( &ctx->vs2 );
            break;
        }
        
        case ( CHARGER19_VOUT_2V7 ): 
        {
            digital_out_low( &ctx->vs1 );
            digital_out_high( &ctx->vs2 );
            break;
        }
        
         case ( CHARGER19_VOUT_3V0 ): 
        {
            digital_out_high( &ctx->vs1 );
            digital_out_high( &ctx->vs2 );
            break;
        }
        
        default :
        {
            error_flag = CHARGER19_ERROR;
            break;
        }
        
    }
    
    return error_flag;
}

err_t charger19_get_vbat ( charger19_t *ctx, float *vbat )
{
    err_t error_flag = CHARGER19_OK;
    float battery_voltage = 0;
    
    error_flag = charger19_read_an_pin_voltage ( ctx, &battery_voltage );
    
    *vbat = battery_voltage * 2;
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
