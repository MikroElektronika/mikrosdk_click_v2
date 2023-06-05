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

#define HALLCURRENT825A_QUIESCENT_VOLTAGE              1.65f
#define HALLCURRENT825A_SENSITIVITY_OF_10_V_A          0.048f

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

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 3.3;
}

err_t hallcurrent825a_init ( hallcurrent825a_t *ctx, hallcurrent825a_cfg_t *cfg ) 
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

    digital_in_init( &ctx->oc1, cfg->oc1 );
    digital_in_init( &ctx->oc2, cfg->oc2 );

    return ADC_SUCCESS;
}

err_t hallcurrent825a_read_pin_value ( hallcurrent825a_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t hallcurrent825a_read_pin_volt ( hallcurrent825a_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t hallcurrent825a_calibration ( hallcurrent825a_t *ctx ) 
{
    err_t status = HALLCURRENT825A_OK;
    float voltage = 0;
    
    status |= hallcurrent825a_get_voltage( ctx, &voltage ); 
    
    ctx->offset = HALLCURRENT825A_QUIESCENT_VOLTAGE - voltage; 
    
    return status;
}

err_t hallcurrent825a_get_voltage ( hallcurrent825a_t *ctx, float *avr_voltage ) 
{
    err_t status = HALLCURRENT825A_OK;
    float voltage = 0;
    float sum_voltage = 0;
    uint16_t n_cnt = 0;
    
    for ( n_cnt = 0; n_cnt < 500; n_cnt++ ) 
    {
        status |= hallcurrent825a_read_pin_volt( ctx, &voltage ); 
        sum_voltage += voltage;
        dev_measure_delay( );
    }
    
    *avr_voltage = sum_voltage / 500; 
    
    return status;
}

err_t hallcurrent825a_get_current( hallcurrent825a_t *ctx, float *current ) 
{
    err_t status = HALLCURRENT825A_OK;
    float voltage = 0;
    
    status |= hallcurrent825a_get_voltage( ctx, &voltage );
    
    voltage -= ( HALLCURRENT825A_QUIESCENT_VOLTAGE - ctx->offset );
    
    *current = voltage / HALLCURRENT825A_SENSITIVITY_OF_10_V_A;
    
    return status;
}

uint8_t hallcurrent825a_get_odc1 ( hallcurrent825a_t *ctx ) 
{
    return digital_in_read( &ctx->oc1 );
}

uint8_t hallcurrent825a_get_odc2 ( hallcurrent825a_t *ctx ) 
{
    return digital_in_read( &ctx->oc2 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_measure_delay ( void ) 
{
    Delay_1ms( );
}
    
// ------------------------------------------------------------------------- END
