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
 * @file isoadc3.c
 * @brief ISO ADC 3 Click Driver.
 */

#include "isoadc3.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS
/**
 * @brief Read function delay of 1 millisecond.
 */
void dev_mesure_delay( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS

void isoadc3_cfg_setup ( isoadc3_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ISOADC3_SET_DEV_ADDR;
}

err_t isoadc3_init ( isoadc3_t *ctx, isoadc3_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t isoadc3_generic_write ( isoadc3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t isoadc3_generic_read ( isoadc3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint16_t isoadc3_read_adc ( isoadc3_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint16_t result;

    i2c_master_read( &ctx->i2c, rx_buf, 2 );
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    result &= ISOADC3_12_BIT_DATA;

    return result;
}

uint16_t isoadc3_get_adc_voltage ( isoadc3_t *ctx, uint16_t v_ref ) {
    float lbs_val = 0.0;
    uint16_t raw_data = 0;
    float result = 0.0;
    lbs_val = ( ( float )v_ref ) / ISOADC3_RESOLUTION;
    raw_data = isoadc3_read_adc( ctx );

    result = raw_data * lbs_val;
    result -= ISOADC3_OFFSET;
    result /= 4;

    return ( uint16_t )result;
}

uint16_t isoadc3_read_voltage ( isoadc3_t *ctx, uint16_t v_ref ) {
    float adc_vtg_sum = 0;
    float adc_vtg;
    float result = 0.0;

    for ( uint8_t n_cnt = 0; n_cnt < ISOADC3_ADC_NUM_OF_MEASURE; n_cnt++ ) {
        adc_vtg = isoadc3_get_adc_voltage( ctx, v_ref );
        adc_vtg_sum += adc_vtg;
        dev_mesure_delay( );
    }

    result = adc_vtg_sum;
    result /= ISOADC3_ADC_NUM_OF_MEASURE;
    return ( uint16_t )result;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS

void dev_mesure_delay( void ) {
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
