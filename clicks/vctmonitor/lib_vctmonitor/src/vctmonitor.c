/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file vctmonitor.c
 * @brief VCT Monitor Click Driver.
 */

#include "vctmonitor.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief VCT Monitor read register.
 * @details This function reads a 16-bit value of 
 * selected register by using I2C serial interface.
 */
static uint16_t drv_read_register_u16( vctmonitor_t *ctx, uint8_t reg );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void vctmonitor_cfg_setup ( vctmonitor_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VCTMONITOR_SLAVE_ADDR_GND_GND;
}

err_t vctmonitor_init ( vctmonitor_t *ctx, vctmonitor_cfg_t *cfg ) {
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

err_t vctmonitor_generic_write ( vctmonitor_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t vctmonitor_generic_read ( vctmonitor_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint8_t vctmonitor_get_status ( vctmonitor_t *ctx ) {
    uint8_t reg;
    uint8_t status;

    reg = VCTMONITOR_REG_STATUS;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, &status, 1 );

    return status;
}

void vctmonitor_configuration ( vctmonitor_t *ctx, uint8_t cfg ) {
    uint8_t tx_data[ 2 ];

    tx_data[ 0 ] = VCTMONITOR_REG_CONTROL;
    tx_data[ 1 ] = cfg;
    tx_data[ 2 ] = 0x02;

    i2c_master_write( &ctx->i2c, tx_data, 3 );
}

float vctmonitor_read_temperature ( vctmonitor_t *ctx ) {
    uint16_t temp_raw;
    float temperature;

    vctmonitor_configuration( ctx, VCTMONITOR_CTRL_SINGLE_MEAS | 
                                   VCTMONITOR_CTRL_MODE1_ALL |
                                   VCTMONITOR_CTRL_MODE2_V1_2_TR2 );

    temp_raw = drv_read_register_u16( ctx, VCTMONITOR_REG_V3_MSB );
    temp_raw &= 0x1FFF;
    temperature = temp_raw * 0.0625;

    return temperature;
}

float vctmonitor_read_voltage_differential ( vctmonitor_t *ctx ) {
    uint16_t volt_raw;
    float voltage;

    vctmonitor_configuration( ctx, VCTMONITOR_CTRL_SINGLE_MEAS |
                                   VCTMONITOR_CTRL_MODE1_ALL |
                                   VCTMONITOR_CTRL_MODE2_V1_2_TR2 );

    volt_raw = drv_read_register_u16( ctx, VCTMONITOR_REG_V2_MSB );

    if ( volt_raw & 0x4000 ) {
        volt_raw &= 0x3FFF;
        voltage = ( volt_raw + 1 ) * ( -19.42 );
    } else {
        volt_raw &= 0x3FFF;
        voltage = ( volt_raw ) * ( 19.42 );
    }
    voltage /= 1000.0; // convert to mV

    return voltage;
}

float vctmonitor_read_voltage_single ( vctmonitor_t *ctx, uint8_t channel ) {
    uint16_t volt_raw;
    float voltage;

    vctmonitor_configuration( ctx, VCTMONITOR_CTRL_SINGLE_MEAS |
                                   VCTMONITOR_CTRL_MODE1_ALL |
                                   VCTMONITOR_CTRL_MODE2_V12_TR2 );
                              
    volt_raw = drv_read_register_u16( ctx, channel );

    if ( volt_raw & 0x4000 ) {
        volt_raw &= 0x3FFF;
        voltage = ( volt_raw + 1 ) * ( -305.18 );
    } else {
        volt_raw &= 0x3FFF;
        voltage = ( volt_raw ) * ( 305.18 );
    }
    voltage /= 1000.0; // convert to mV

    return voltage;
}

float vctmonitor_read_current ( vctmonitor_t *ctx ) {
    uint16_t curr_raw;
    float current;

    vctmonitor_configuration( ctx, VCTMONITOR_CTRL_SINGLE_MEAS |
                                   VCTMONITOR_CTRL_MODE1_ALL |
                                   VCTMONITOR_CTRL_MODE2_V1_2_TR2 );
                              
    curr_raw = drv_read_register_u16( ctx, VCTMONITOR_REG_V2_MSB );

    if ( curr_raw & 0x4000 ) {
        curr_raw &= 0x1FFF;
        current = ( curr_raw + 1 ) * ( -19.42 );
        current /= 0.01; // SHUNT value
    } else {
        curr_raw &= 0x1FFF;
        current = ( curr_raw ) * ( 19.42 );
        current /= 0.01; // SHUNT value
    }
    current /= 1000.0; // convert to mA

    return current;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static uint16_t drv_read_register_u16( vctmonitor_t *ctx, uint8_t reg ) {
    uint8_t rx_data[ 2 ];
    uint16_t data_raw;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_data, 2 );

    data_raw = rx_data[ 0 ];
    data_raw <<= 8;
    data_raw |= rx_data[ 1 ];

    return data_raw;
}

// ------------------------------------------------------------------------- END
