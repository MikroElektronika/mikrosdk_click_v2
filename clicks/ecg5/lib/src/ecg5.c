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
 * @file ecg5.c
 * @brief ECG 5 Click Driver.
 */

#include "ecg5.h"

void ecg5_cfg_setup ( ecg5_cfg_t *cfg ) {
    cfg->an = HAL_PIN_NC;
    cfg->sdn   = HAL_PIN_NC;
    cfg->lon = HAL_PIN_NC;
    cfg->lop = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t ecg5_init ( ecg5_t *ctx, ecg5_cfg_t *cfg ) {
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->sdn, cfg->sdn );

    digital_in_init( &ctx->lon, cfg->lon );
    digital_in_init( &ctx->lop, cfg->lop );

    digital_out_low( &ctx->sdn );

    return ADC_SUCCESS;
}

err_t ecg5_read_an_pin_value ( ecg5_t *ctx, uint16_t *data_out ) {
    return analog_in_read( &ctx->adc, data_out );
}

err_t ecg5_read_an_pin_voltage ( ecg5_t *ctx, float *data_out ) {
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void ecg5_set_mode ( ecg5_t *ctx, uint8_t state ) {
    if ( state == ECG5_NORMAL_MODE ) {
        digital_out_low( &ctx->sdn );
    } else {
        digital_out_high( &ctx->sdn );
    }
}

err_t ecg5_check_lod_negative ( ecg5_t *ctx ) {
    if ( digital_in_read( &ctx->lon ) ) {
        return ECG5_ERROR;
    } else {
        return ECG5_OK;
    }
}

err_t ecg5_check_lod_positive ( ecg5_t *ctx ) {
    if ( digital_in_read( &ctx->lop ) ) {
        return ECG5_ERROR;
    } else {
        return ECG5_OK;
    }
}

// ------------------------------------------------------------------------- END
