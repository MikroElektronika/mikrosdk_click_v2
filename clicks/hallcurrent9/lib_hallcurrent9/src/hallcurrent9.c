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
 * @file hallcurrent9.c
 * @brief Hall Current 9 Click Driver.
 */

#include "hallcurrent9.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define HALLCURRENT9_DATA_12_BIT              0x0FFF
#define HALLCURRENT9_ADC_NUM_OF_MEASURE        100.0
#define HALLCURRENT9_VREF_5000_mV             5000.0
#define HALLCURRENT9_ADC_FULL_RESOLUTION      4096.0
#define HALLCURRENT9_ADC_HALF_RESOLUTION      2048.0
#define HALLCURRENT9_INS_MAX                     7.7
#define HALLCURRENT9_INS_RESOLUTION             15.4
#define HALLCURRENT9_CONV_A_TO_mA             1000.0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void dev_measure_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS


void hallcurrent9_cfg_setup ( hallcurrent9_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT9_SET_DEV_ADDR;
}

err_t hallcurrent9_init ( hallcurrent9_t *ctx, hallcurrent9_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->an, cfg->an );

    return I2C_MASTER_SUCCESS;
}

err_t hallcurrent9_read_adc ( hallcurrent9_t *ctx, uint16_t *read_adc ) {
    uint8_t rx_buf[ 2 ];
    uint16_t adc_val;
    err_t status;
    
    status = i2c_master_read( &ctx->i2c, rx_buf, 2 );

    adc_val = rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];
    
    adc_val &= HALLCURRENT9_DATA_12_BIT;
    
    *read_adc = adc_val;

    return status;
}

err_t hallcurrent9_set_calibration ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val ) {
    float avg_val = 0;
    uint16_t adc_data;
    err_t error_flag;
    
    error_flag = HALLCURRENT9_OK;
    
    for ( uint8_t n_cnt = 0; n_cnt < 20; n_cnt++ ) {
        error_flag |= hallcurrent9_read_adc ( ctx, &adc_data );
        avg_val += ( float ) adc_data;
        dev_measure_delay( );
    }
    
    avg_val /= 20;
    
    adc_val->zero_adc_val = ( uint16_t ) avg_val;
    
    return error_flag;
}

float hallcurrent9_get_current ( hallcurrent9_t *ctx, hallcurrent9_calibration_data_t *adc_val ) {
    float current;
    uint16_t adc_tmp;
    uint32_t adc_sum;
    
    adc_sum = 0;
    
    for ( uint8_t n_cnt = 0; n_cnt < 100; n_cnt++ ) {
        hallcurrent9_read_adc( ctx, &adc_tmp );
        current += ( float ) adc_tmp;
        dev_measure_delay( );
    }
    
    current /= 100;
    current -= adc_val->zero_adc_val;
    current *= HALLCURRENT9_INS_RESOLUTION;
    current /= HALLCURRENT9_ADC_FULL_RESOLUTION;
    current *= HALLCURRENT9_CONV_A_TO_mA;

    return current;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_measure_delay ( void ) {
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
