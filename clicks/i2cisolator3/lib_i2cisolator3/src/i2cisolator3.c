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
 * @file i2cisolator3.c
 * @brief I2C Isolator 3 Click Driver.
 */

#include "i2cisolator3.h"
static uint8_t dev_slave_addr;

void i2cisolator3_cfg_setup ( i2cisolator3_cfg_t *cfg ) {

    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2CISOLATOR3_SET_DEV_ADDR;
}

err_t i2cisolator3_init ( i2cisolator3_t *ctx, i2cisolator3_cfg_t *cfg ) {

    i2c_master_config_t i2c_cfg;

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

err_t i2cisolator3_generic_write ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t i2cisolator3_generic_read ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void i2cisolator3_send_cmd ( i2cisolator3_t *ctx, uint8_t command ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = command;
    i2c_master_write( &ctx->i2c, tx_buf, 1 );
}

void i2cisolator3_write_byte ( i2cisolator3_t *ctx, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;
    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t i2cisolator3_read_byte ( i2cisolator3_t *ctx, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg;
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1 );
    return rx_buf[ 0 ];
}

err_t i2cisolator3_burst_write ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes ) {

    uint8_t status;
    uint8_t n_cnt;
    uint8_t tx_buf[ 257 ];

    status = I2CISOLATOR3_OK;
    if ( n_bytes == I2CISOLATOR3_READ_WRITE_LEN_ERROR ) {
        status = I2CISOLATOR3_ERROR;
    }
    else {
        tx_buf[ 0 ] = reg;
        for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) {
            tx_buf[ n_cnt + 1 ] = p_tx_data[ n_cnt ];
        }
        i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 1);
    }

    return status;
}

err_t i2cisolator3_burst_read ( i2cisolator3_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes ) {

    uint8_t status;
    uint8_t tx_buf[ 1 ];

    status = I2CISOLATOR3_OK;
    if ( n_bytes == I2CISOLATOR3_READ_WRITE_LEN_ERROR ) {
        status = I2CISOLATOR3_ERROR;
    }
    else {
        tx_buf[ 0 ] = reg;
        i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, p_rx_data, n_bytes );
    }
    return status;
}

err_t i2cisolator3_adv_write ( i2cisolator3_t *ctx, uint8_t *p_reg, uint8_t n_reg_bytes, uint8_t *p_tx_data, uint8_t n_tx_data_bytes ) {
    uint8_t status;
    uint8_t n_cnt;
    uint8_t total_len;
    uint8_t tx_buf[ 512 ];

    status = I2CISOLATOR3_OK;
    if ( ( n_reg_bytes == I2CISOLATOR3_READ_WRITE_LEN_ERROR ) || ( n_tx_data_bytes == I2CISOLATOR3_READ_WRITE_LEN_ERROR ) ) {
        status = I2CISOLATOR3_ERROR;
    }
    else {
        total_len = n_reg_bytes + n_tx_data_bytes;
        for ( n_cnt = 0; n_cnt < n_reg_bytes; n_cnt++ ) {
            tx_buf[ n_cnt ] = p_reg[ n_cnt ];
        }
        for ( n_cnt = 0; n_cnt < n_tx_data_bytes; n_cnt++ ) {
            
            tx_buf[ n_reg_bytes + n_cnt ] = p_tx_data[ n_cnt ];
        }
        
        i2c_master_write( &ctx->i2c, tx_buf, total_len);
    }
    return status;
}


err_t i2cisolator3_adv_read ( i2cisolator3_t *ctx, uint8_t *p_reg, uint8_t n_reg_bytes, uint8_t *p_rx_data, uint8_t n_rx_data_bytes ) {

    uint8_t status;
    uint8_t n_cnt;
    uint8_t tx_buf[ 256 ];

    status = I2CISOLATOR3_OK;
    if ( ( n_reg_bytes == I2CISOLATOR3_READ_WRITE_LEN_ERROR ) || ( n_rx_data_bytes == I2CISOLATOR3_READ_WRITE_LEN_ERROR ) ) {
        
        status = I2CISOLATOR3_ERROR;
    }
    else {
        for ( n_cnt = 0; n_cnt < n_reg_bytes; n_cnt++ ) {
            
            tx_buf[ n_cnt ] = p_reg[ n_cnt ];
        }

        i2c_master_write_then_read( &ctx->i2c, tx_buf, n_reg_bytes, p_rx_data, n_rx_data_bytes );
    }
    return status;
}

// ------------------------------------------------------------------------- END
