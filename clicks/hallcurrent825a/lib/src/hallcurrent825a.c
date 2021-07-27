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
 * @file hallcurrent825a.c
 * @brief Hall Current 8 25A Click Driver.
 */

#include "hallcurrent825a.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define HALLCURRENT825A_QUIESCENT_VOLTAGE                1.65
#define HALLCURRENT825A_CONVERT_V_TO_mV                  1000
#define HALLCURRENT825A_FACTOR_SENSITIVITY_OF_10mV_A     10
#define HALLCURRENT825A_FACTOR_PRECISION_SENSITIVITY     1.1

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Measurement delay.
 * @details Measurement delay for 1 milliseconds.
 */
static void dev_measure_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hallcurrent825a_cfg_setup ( hallcurrent825a_cfg_t *cfg )
{
    cfg->an = HAL_PIN_NC;
    cfg->oc1 = HAL_PIN_NC;
    cfg->oc2 = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref       = 3.3;
}

err_t hallcurrent825a_init ( hallcurrent825a_t *ctx, hallcurrent825a_cfg_t *cfg ) {
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    // It should contain the error status checking for every pin init.

    digital_in_init( &ctx->oc1, cfg->oc1 );
    digital_in_init( &ctx->oc2, cfg->oc2 );

    return ADC_SUCCESS;
}

err_t hallcurrent825a_read_an_pin_value ( hallcurrent825a_t *ctx, uint16_t *data_out ) {
    return analog_in_read( &ctx->adc, data_out );
}

err_t hallcurrent825a_read_an_pin_voltage ( hallcurrent825a_t *ctx, float *data_out ) {
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t hallcurrent825a_calibration ( hallcurrent825a_t *ctx, hallcurrent825a_offset_t *offset_val ) {
    err_t status;
    float voltage;
    float temp;
    
    status = HALLCURRENT825A_OK;
    temp = 0;
    
    for ( uint16_t n_cnt = 0; n_cnt < 500; n_cnt++ ) {
        status |= analog_in_read_voltage( &ctx->adc, &voltage ); 
        temp += voltage;
        dev_measure_delay( );
    }
    
    temp /= 500;
    temp = HALLCURRENT825A_QUIESCENT_VOLTAGE - temp; 
    
    offset_val->offset = temp; 
    
    return status;
}

err_t hallcurrent825a_get_voltage ( hallcurrent825a_t *ctx, float *avr_voltage ) {
    err_t status;
    float voltage;
    float temp;
    
    status = HALLCURRENT825A_OK;
    temp = 0;
    
    for ( uint16_t n_cnt = 0; n_cnt < 500; n_cnt++ ) {
        status |= analog_in_read_voltage( &ctx->adc, &voltage ); 
        temp += voltage;
        dev_measure_delay( );
    }
    
    *avr_voltage = temp / 500; 
    
    return status;
}

err_t hallcurrent825a_get_current( hallcurrent825a_t *ctx, hallcurrent825a_offset_t *offset_val, float *current ) {
    err_t status;
    float curr_val;
    float voltage;
    float sum;
    float sensor_offset;
    
    sensor_offset = offset_val->offset;
    
    status = HALLCURRENT825A_OK;
    sum = 0;
    
    for ( uint16_t n_cnt = 0; n_cnt < 500; n_cnt++ ) {
        status |= analog_in_read_voltage( &ctx->adc, &voltage ); 
        sum += voltage;
        dev_measure_delay( );
    }
    
    curr_val = sum / 500;
    curr_val -= HALLCURRENT825A_QUIESCENT_VOLTAGE;
    curr_val += sensor_offset;
    curr_val *= HALLCURRENT825A_CONVERT_V_TO_mV;
    curr_val /= HALLCURRENT825A_FACTOR_SENSITIVITY_OF_10mV_A;
    curr_val /= HALLCURRENT825A_FACTOR_PRECISION_SENSITIVITY;
     
    *current = curr_val;
    
    return status;
}

uint8_t hallcurrent825a_get_odc1 ( hallcurrent825a_t *ctx ) {
    return digital_in_read( &ctx->oc1 );
}

uint8_t hallcurrent825a_get_odc2 ( hallcurrent825a_t *ctx ) {
    return digital_in_read( &ctx->oc2 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_measure_delay ( void ) {
    Delay_1ms( );
}
    
// ------------------------------------------------------------------------- END
