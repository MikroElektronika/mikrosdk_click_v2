/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "pollution.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define HYDROGEN_MAX_R_LOAD          9950.0
#define POLLUTION_VCC                4.95
#define POLLUTION_C1                 0.8639656653028277
#define POLLUTION_C2                 1.1496082990709344
#define POLLUTION_C3                 1.5489389323538676
#define POLLUTION_M1                 -0.30361905759780833
#define POLLUTION_M2                 -0.4694852833012203
#define POLLUTION_M3                 -0.5989696888059545
#define POLLUTION_ATMOCO2            397.13
#define POLLUTION_VREF               1.8
#define POLLUTION_ADC_VAL            4096.0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_comm_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pollution_cfg_setup ( pollution_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin        = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ena           = HAL_PIN_NC;
    
    // ADC characteristics

    cfg->resolution   = ANALOG_IN_RESOLUTION_14_BIT;
    cfg->vref         = 3.3;
}

POLLUTION_RETVAL pollution_init ( pollution_t *ctx, pollution_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;
    
    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin  = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return POLLUTION_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // Output pins 

    digital_out_init( &ctx->ena, cfg->ena );

    return POLLUTION_OK;
}

void pollution_default_cfg ( pollution_t *ctx )
{
    // Enable the WSP2110 sensor
    
    pollution_enable( ctx );
    
    // Reset the WSP2110 sensor
    
    pollution_reset( ctx );
}

pollution_data_t pollution_generic_read ( pollution_t *ctx )
{
    pollution_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

void pollution_enable ( pollution_t *ctx )
{
    digital_out_high( &ctx->ena );
}

void pollution_disable ( pollution_t *ctx )
{
    digital_out_low( &ctx->ena );
}

void pollution_reset ( pollution_t *ctx )
{
    digital_out_high( &ctx->ena );
    dev_comm_delay( );
    
    digital_out_low( &ctx->ena );
    dev_comm_delay( );
}

float pollution_measure_load_voltage ( pollution_t *ctx )
{
    float voltage;

    analog_in_read_voltage( &ctx->adc, &voltage );
    
    return voltage;
}

float pollution_get_resistance ( pollution_t *ctx )
{
    float result;
    float v_load;

    v_load  = pollution_measure_load_voltage( ctx );

    result  = POLLUTION_VCC;
    result /= v_load - 1;
    result *= HYDROGEN_MAX_R_LOAD;

    return result;
}

float pollution_get_corrected_resistance ( pollution_t *ctx )
{
    float result;
    float v_load;
    float s_res;

    v_load  = pollution_measure_load_voltage( ctx );
    s_res   = pollution_get_resistance( ctx );

    result  = v_load;
    result /= POLLUTION_VCC - v_load;
    result *= s_res;

    return result;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_comm_delay ( void )
{
    Delay_100ms();
}

// ------------------------------------------------------------------------- END

