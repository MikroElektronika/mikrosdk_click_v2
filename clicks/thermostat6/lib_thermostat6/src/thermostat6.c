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
 * @file thermostat6.c
 * @brief Thermostat 6 Click Driver.
 */

#include "thermostat6.h"

/**
 * @brief Thermostat 6 Click temperature probe R/T characteristics object.
 * @details Temperature probe R/T characteristics object definition of Thermostat 6 Click driver.
 */
typedef struct
{
    float temp;                 /**< Temperature in degrees Celsius. */
    float rt_r25;               /**< RT/R25, resistance ratio. */

} thermostat6_probe_t;

// NTC Thermistor 10k Cylindrical Probe (B57500M0103A005) R/T characteristics
static thermostat6_probe_t probe[ 43 ] = 
{
    { .temp = -55.0, .rt_r25 = 96.3 },
    { .temp = -50.0, .rt_r25 = 67.01 },
    { .temp = -45.0, .rt_r25 = 47.17 },
    { .temp = -40.0, .rt_r25 = 33.65 },
    { .temp = -35.0, .rt_r25 = 24.26 },
    { .temp = -30.0, .rt_r25 = 17.7 },
    { .temp = -25.0, .rt_r25 = 13.04 },
    { .temp = -20.0, .rt_r25 = 9.707 },
    { .temp = -15.0, .rt_r25 = 7.293 },
    { .temp = -10.0, .rt_r25 = 5.533 },
    { .temp = -5.0, .rt_r25 = 4.232 },
    { .temp = 0.0, .rt_r25 = 3.265 },
    { .temp = 5.0, .rt_r25 = 2.539 },
    { .temp = 10.0, .rt_r25 = 1.99 },
    { .temp = 15.0, .rt_r25 = 1.571 },
    { .temp = 20.0, .rt_r25 = 1.249 },
    { .temp = 25.0, .rt_r25 = 1.0 },
    { .temp = 30.0, .rt_r25 = 0.8057 },
    { .temp = 35.0, .rt_r25 = 0.6531 },
    { .temp = 40.0, .rt_r25 = 0.5327 },
    { .temp = 45.0, .rt_r25 = 0.4369 },
    { .temp = 50.0, .rt_r25 = 0.3603 },
    { .temp = 55.0, .rt_r25 = 0.2986 },
    { .temp = 60.0, .rt_r25 = 0.2488 },
    { .temp = 65.0, .rt_r25 = 0.2083 },
    { .temp = 70.0, .rt_r25 = 0.1752 },
    { .temp = 75.0, .rt_r25 = 0.1481 },
    { .temp = 80.0, .rt_r25 = 0.1258 },
    { .temp = 85.0, .rt_r25 = 0.1072 },
    { .temp = 90.0, .rt_r25 = 0.09177 },
    { .temp = 95.0, .rt_r25 = 0.07885 },
    { .temp = 100.0, .rt_r25 = 0.068 },
    { .temp = 105.0, .rt_r25 = 0.05886 },
    { .temp = 110.0, .rt_r25 = 0.05112 },
    { .temp = 115.0, .rt_r25 = 0.04454 },
    { .temp = 120.0, .rt_r25 = 0.03893 },
    { .temp = 125.0, .rt_r25 = 0.03417 },
    { .temp = 130.0, .rt_r25 = 0.03009 },
    { .temp = 135.0, .rt_r25 = 0.02654 },
    { .temp = 140.0, .rt_r25 = 0.02348 },
    { .temp = 145.0, .rt_r25 = 0.02083 },
    { .temp = 150.0, .rt_r25 = 0.01853 },
    { .temp = 155.0, .rt_r25 = 0.01653 },
};

void thermostat6_cfg_setup ( thermostat6_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->relay = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMOSTAT6_SET_DEV_ADDR;
    cfg->vref        = THERMOSTAT6_VREF_3V3;
}

err_t thermostat6_init ( thermostat6_t *ctx, thermostat6_cfg_t *cfg ) 
{
    ctx->vref = cfg->vref;

    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, THERMOSTAT6_VREF_3V3 ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_in_init( &ctx->relay, cfg->relay );

    return THERMOSTAT6_OK;
}

err_t thermostat6_get_adc_v ( thermostat6_t *ctx, float *voltage )
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_adc = 0;
    err_t error_flag = i2c_master_read( &ctx->i2c, data_buf, 2 );
    raw_adc = ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) & THERMOSTAT6_ADC_RESOLUTION;
    if ( ( THERMOSTAT6_OK == error_flag ) && ( NULL != voltage ) )
    {
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) THERMOSTAT6_ADC_RESOLUTION );
    }
    return error_flag;
}

err_t thermostat6_get_an_pin_v ( thermostat6_t *ctx, float *voltage )
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t thermostat6_get_adc_v_avg ( thermostat6_t *ctx, float *voltage, uint16_t num_samples )
{
    float voltage_sum = 0;
    float voltage_sample = 0;
    uint32_t cnt = 0;
    for ( cnt = 0; cnt < num_samples; cnt++ )
    {
        if ( THERMOSTAT6_OK != thermostat6_get_adc_v ( ctx, &voltage_sample ) )
        {
            return THERMOSTAT6_ERROR;
        }
        voltage_sum += voltage_sample;
    }
    if ( ( num_samples > 0 ) && ( NULL != voltage ) )
    {
        *voltage = voltage_sum / num_samples;
    }
    return THERMOSTAT6_OK;
}

err_t thermostat6_get_an_pin_v_avg ( thermostat6_t *ctx, float *voltage, uint16_t num_samples )
{
    float voltage_sum = 0;
    float voltage_sample = 0;
    uint32_t cnt = 0;
    for ( cnt = 0; cnt < num_samples; cnt++ )
    {
        if ( THERMOSTAT6_OK != thermostat6_get_an_pin_v ( ctx, &voltage_sample ) )
        {
            return THERMOSTAT6_ERROR;
        }
        voltage_sum += voltage_sample;
    }
    if ( ( num_samples > 0 ) && ( NULL != voltage ) )
    {
        *voltage = voltage_sum / num_samples;
    }
    return THERMOSTAT6_OK;
}

err_t thermostat6_set_vref ( thermostat6_t *ctx, float vref )
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, THERMOSTAT6_VREF_3V3 );
}

uint8_t thermostat6_get_relay_pin ( thermostat6_t *ctx )
{
    return digital_in_read ( &ctx->relay );
}

float thermostat6_get_temperature ( float voltage )
{
    uint8_t cnt = 0;
    float temperature = probe[ 0 ].temp;
    // Calculating resistance ratio (RT/R25) for 10K NTC probe based on voltage input.
    // The form is derived for the following resistor settings:
    // R6 = 49.9K, R7 = 5.1K, R12 = 6.8K, other resistors on input are NOT populated.
    float resistance_ratio = ( 55.1 - 18.52 * voltage ) / ( 1.67 * voltage - 1 ) / 10;
    for ( cnt = 1; cnt < ( sizeof ( probe ) / sizeof ( thermostat6_probe_t ) ); cnt++ )
    {
        // Locate the RT/R25 point in the probe characteristics map
        if ( resistance_ratio > probe[ cnt ].rt_r25 )
        {
            // Interpolating temperature between two temperature points from the probe characteristics map
            temperature = probe[ cnt - 1 ].temp + ( ( resistance_ratio - probe[ cnt - 1 ].rt_r25 ) / 
                                                    ( probe[ cnt ].rt_r25 - probe[ cnt - 1 ].rt_r25 ) ) * 
                                                  ( probe[ cnt ].temp - probe[ cnt - 1 ].temp );
            break;
        }
    }
    return temperature;
}

// ------------------------------------------------------------------------- END
