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
 * @file pressure14.c
 * @brief Pressure 14 Click Driver.
 */

#include "pressure14.h"

void pressure14_cfg_setup ( pressure14_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE14_SET_DEV_ADDR;
}

err_t pressure14_init ( pressure14_t *ctx, pressure14_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

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

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    return I2C_MASTER_SUCCESS;
}

err_t pressure14_generic_write ( pressure14_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t pressure14_generic_read ( pressure14_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void pressure14_measure_cmd ( pressure14_t *ctx ) {
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = PRESSURE14_CMD_OUT_MEAS;
    tx_buf[ 1 ] = PRESSURE14_CMD_DUMMY;
    tx_buf[ 2 ] = PRESSURE14_CMD_DUMMY;
    
    i2c_master_write( &ctx->i2c, tx_buf, 3 );
    
}

uint8_t pressure14_check_busy_flag_int ( pressure14_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

void pressure14_read_press_and_temp ( pressure14_t *ctx, uint8_t *status_byte, uint32_t *pressure_data, uint32_t *temp_data ) {
    uint8_t rx_buf[ 7 ];
    uint32_t tmp;

    tmp = 0;

    i2c_master_read( &ctx->i2c, rx_buf, 7 );
    *status_byte = rx_buf[ 0 ];
    
    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];
    *pressure_data = tmp;
    
    tmp = rx_buf[ 4 ];
    tmp <<= 8;
    tmp |= rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= rx_buf[ 6 ];
    *temp_data = tmp;
}

float pressure14_get_pressure ( uint32_t pressure_raw, uint8_t conv_unit ) {
    float conv_constant;
    float result;
    
    switch ( conv_unit ) {
        case PRESSURE14_CONV_UNIT_PSI:
            conv_constant = PRESSURE14_CONST_PSI;
        break;

        case PRESSURE14_CONV_UNIT_PASCAL:
            conv_constant = PRESSURE14_CONST_PASCAL;
        break;

        case PRESSURE14_CONV_UNIT_KILOPASCAL:
            conv_constant = PRESSURE14_CONST_KILOPASCAL;
        break;

        case PRESSURE14_CONV_UNIT_MMHG:
            conv_constant = PRESSURE14_CONST_MMHG;
        break;

        case PRESSURE14_CONV_UNIT_INHG:
            conv_constant = PRESSURE14_CONST_INHG;
        break;

        case PRESSURE14_CONV_UNIT_ATMOSPHERIC:
            conv_constant = PRESSURE14_CONST_ATMOSPHERIC;
        break;

        case PRESSURE14_CONV_UNIT_MILIBAR:
            conv_constant = PRESSURE14_CONST_MILIBAR;
        break;

        case PRESSURE14_CONV_UNIT_BAR:
            conv_constant = PRESSURE14_CONST_BAR;
        break;

        default:
            conv_constant = PRESSURE14_CONST_PSI;
        break;
    }
    
    result = ( float )pressure_raw;
    result -= PRESSURE14_CONST_PRESS_OUT_MIN;
    result *= PRESSURE14_CONST_PRESS_VAL_MAX - PRESSURE14_CONST_PRESS_VAL_MIN;
    result /= PRESSURE14_CONST_PRESS_OUT_MAX - PRESSURE14_CONST_PRESS_OUT_MIN;
    result += PRESSURE14_CONST_PRESS_VAL_MIN;
    result *= conv_constant;
    return result;
}

float pressure14_get_temperature ( uint32_t temperature_raw, uint8_t conv_unit ) {
    float conv_addi_constant;
    float conv_mult_constant;
    float result;

    switch ( conv_unit ) {
        case PRESSURE14_CONV_UNIT_CELSIUS:
            conv_addi_constant = PRESSURE14_CONST_ADDI_CELS;
            conv_mult_constant = PRESSURE14_CONST_MULT_CELS;
        break;

        case PRESSURE14_CONV_UNIT_KELVIN:
            conv_addi_constant = PRESSURE14_CONST_ADDI_KELV;
            conv_mult_constant = PRESSURE14_CONST_MULT_KELV;
        break;

        case PRESSURE14_CONV_UNIT_FAHRENHEIT:
            conv_addi_constant = PRESSURE14_CONST_ADDI_FAHR;
            conv_mult_constant = PRESSURE14_CONST_MULT_FAHR;
        break;
        default:
            conv_addi_constant = PRESSURE14_CONST_ADDI_CELS;
            conv_mult_constant = PRESSURE14_CONST_MULT_CELS;
        break;
    }
    
    result = ( float )( temperature_raw );
    result *= PRESSURE14_CONST_TEMP_MAX - PRESSURE14_CONST_TEMP_MIN;
    result /= PRESSURE14_CONST_TEMP_OUT_MAX;
    result += PRESSURE14_CONST_TEMP_MIN;
    result *= conv_mult_constant;
    result += conv_addi_constant;
    return result;
}

// ------------------------------------------------------------------------- END
