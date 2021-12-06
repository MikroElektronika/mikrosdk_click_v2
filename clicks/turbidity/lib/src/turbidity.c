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
 * @file turbidity.c
 * @brief Turbidity Click Driver.
 */

#include "turbidity.h"


/**
 * @brief Turbidity ADC voltage claculation values.
 * @details Definition of ADC voltage claculation data.
 */
#define TURBIDITY_DATA_12_BIT               0x0FFF
#define TURBIDITY_VREF_5000_mV              5000.0
#define TURBIDITY_ADC_RESOLUTION            4096.0
#define TURBIDITY_ADC_VOLTAGE_MAX           4600.0
#define TURBIDITY_ADC_VOLTAGE_MIN           1600.0

/**
 * @brief Nephelometric Turbidity Units claculation values.
 * @details Definition of Nephelometric Turbidity Units claculation data.
 */
#define TURBIDITY_NTU_CALC_FACT_0           0.8871
#define TURBIDITY_NTU_CALC_FACT_1           1.0571
#define TURBIDITY_NTU_CALC_FACT_2           1.1200
#define TURBIDITY_NTU_CALC_FACT_3           1.3333
#define TURBIDITY_NTU_CALC_FACT_4           1.6000
#define TURBIDITY_NTU_MIN                   0.0000
#define TURBIDITY_NTU_MAX                   4000.0
#define TURBIDITY_VOLTAGE_LEVEL_1           2650.0
#define TURBIDITY_VOLTAGE_LEVEL_2           2930.0
#define TURBIDITY_VOLTAGE_LEVEL_3           3350.0
#define TURBIDITY_VOLTAGE_LEVEL_4           3800.0

void turbidity_cfg_setup ( turbidity_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TURBIDITY_SET_DEV_ADDR;
}

err_t turbidity_init ( turbidity_t *ctx, turbidity_cfg_t *cfg ) 
{
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

    return I2C_MASTER_SUCCESS;
}

err_t turbidity_default_cfg ( turbidity_t *ctx ) 
{
    uint16_t adc_val;

    return turbidity_read_adc( ctx, &adc_val );
}

err_t turbidity_generic_read ( turbidity_t *ctx, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_read( &ctx->i2c, rx_buf, rx_len );
}

err_t turbidity_read_adc ( turbidity_t *ctx, uint16_t *adc_val )
{
    uint8_t rx_buf[ 2 ];

    err_t error_flag = turbidity_generic_read( ctx, rx_buf, 2 );

    *adc_val = rx_buf[ 0 ];
    *adc_val <<= 8;
    *adc_val |= rx_buf[ 1 ];
    
    *adc_val &= TURBIDITY_DATA_12_BIT;

    return error_flag;
}

err_t turbidity_get_adc_voltage ( turbidity_t *ctx, float *voltage )
{
    uint16_t adc_data;
    
    err_t error_flag = turbidity_read_adc ( ctx, &adc_data );

    *voltage = ( float ) adc_data;
    *voltage *= TURBIDITY_VREF_5000_mV;
    *voltage /= TURBIDITY_ADC_RESOLUTION;

    return error_flag;
}

err_t turbidity_get_ntu ( turbidity_t *ctx, float *ntu )
{
    float voltage;
    float coeff_c;
    
    err_t error_flag = turbidity_get_adc_voltage ( ctx, &voltage );
    
    coeff_c = TURBIDITY_NTU_CALC_FACT_0;
    
    if ( voltage > TURBIDITY_VOLTAGE_LEVEL_1 )
    {
        coeff_c = TURBIDITY_NTU_CALC_FACT_1;
    }
    
    if ( voltage > TURBIDITY_VOLTAGE_LEVEL_2 )
    {
        coeff_c = TURBIDITY_NTU_CALC_FACT_2;
    }
    
    if ( voltage > TURBIDITY_VOLTAGE_LEVEL_3 )
    {
        coeff_c = TURBIDITY_NTU_CALC_FACT_3;
    }

    if ( voltage > TURBIDITY_VOLTAGE_LEVEL_4 )
    {
        coeff_c = TURBIDITY_NTU_CALC_FACT_4;
    }

    *ntu = TURBIDITY_ADC_VOLTAGE_MAX;
    *ntu -= voltage;
    *ntu /= coeff_c;
    
    if ( voltage > TURBIDITY_ADC_VOLTAGE_MAX )
    {
        *ntu = TURBIDITY_NTU_MIN;
    }

    if ( voltage < TURBIDITY_ADC_VOLTAGE_MIN )
    {
        *ntu = TURBIDITY_NTU_MAX;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
