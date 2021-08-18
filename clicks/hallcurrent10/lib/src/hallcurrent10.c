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
 * @file hallcurrent10.c
 * @brief Hall Current 10 Click Driver.
 */

#include "hallcurrent10.h"

#define HALLCURRENT10_DATA_12_BIT              0x0FFF
#define HALLCURRENT10_ADC_FULL_RESOLUTION      4096.0
#define HALLCURRENT10_VREF_5000_mV             5000.0
#define HALLCURRENT10_VREF_OFFSET_2500_mV      2500.0
#define HALLCURRENT10_ADC_NUM_OF_MEASURE        100.0
#define HALLCURRENT10_CONV_A_TO_mA             1000.0
#define HALLCURRENT10_CURRENT_RANGE              50.0

void hallcurrent10_cfg_setup ( hallcurrent10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT10_SET_DEV_ADDR;
}

err_t hallcurrent10_init ( hallcurrent10_t *ctx, hallcurrent10_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t hallcurrent10_default_cfg ( hallcurrent10_t *ctx ) 
{
    uint16_t read_adc;

    return hallcurrent10_read_adc( ctx, &read_adc );
}

err_t hallcurrent10_read_adc ( hallcurrent10_t *ctx, uint16_t *read_adc ) 
{
    uint8_t rx_buf[ 2 ];
    uint16_t adc_val;

    err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );

    adc_val = rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];
    adc_val &= HALLCURRENT10_DATA_12_BIT;

    *read_adc = adc_val;

    return err_flag;
}

err_t hallcurrent10_get_adc_voltage ( hallcurrent10_t *ctx, float *adc_vtg ) 
{
    uint16_t adc_val;

    err_t err_flag = hallcurrent10_read_adc( ctx, &adc_val );

    *adc_vtg = ( float ) ( adc_val );
    *adc_vtg *= HALLCURRENT10_VREF_5000_mV;
    *adc_vtg /= HALLCURRENT10_ADC_FULL_RESOLUTION;
    *adc_vtg -= HALLCURRENT10_VREF_OFFSET_2500_mV;

    return err_flag;
}

err_t hallcurrent10_get_current ( hallcurrent10_t *ctx, float *current ) 
{
    float adc_vtg_sum = 0;
    float adc_vtg;
    err_t err_flag;

    for ( uint8_t n_cnt = 0; n_cnt < HALLCURRENT10_ADC_NUM_OF_MEASURE; n_cnt++ ) 
    {
        err_flag |= hallcurrent10_get_adc_voltage( ctx, &adc_vtg );
        adc_vtg_sum += adc_vtg;
        Delay_1ms( );
    }

    *current = adc_vtg_sum;
    *current /= HALLCURRENT10_ADC_NUM_OF_MEASURE;

    *current /= HALLCURRENT10_CURRENT_RANGE;
    *current *= HALLCURRENT10_CONV_A_TO_mA;

    return err_flag;
}

// ------------------------------------------------------------------------- END
