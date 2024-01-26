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
 * @file i2cextend.c
 * @brief I2C Extend Click Driver.
 */

#include "i2cextend.h"

void i2cextend_cfg_setup ( i2cextend_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cs  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->on  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2CEXTEND_I2C_SLAVE_ADDR_0;
}

err_t i2cextend_init ( i2cextend_t *ctx, i2cextend_cfg_t *cfg ) {
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->on, cfg->on );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    i2cextend_set_rst ( ctx, I2CEXTEND_PIN_STATE_HIGH );
    i2cextend_set_cs ( ctx, I2CEXTEND_PIN_STATE_HIGH );
    i2cextend_set_on ( ctx, I2CEXTEND_PIN_STATE_LOW );
    Delay_100ms ( );
    i2cextend_set_on ( ctx, I2CEXTEND_PIN_STATE_HIGH );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

void i2cextend_generic_write ( i2cextend_t *ctx, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t i2cextend_generic_read ( i2cextend_t *ctx, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void i2cextend_rmt_write ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;

    i2c_master_set_slave_address( &ctx->i2c, rmt_slave_addr );
    Delay_1ms( );
    
    i2c_master_write( &ctx->i2c, tx_buf, 2 );
    
    i2c_master_set_slave_address( &ctx->i2c, I2CEXTEND_I2C_SLAVE_ADDR_0 );
    Delay_1ms( );
}

uint8_t i2cextend_rmt_read ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_set_slave_address( &ctx->i2c, rmt_slave_addr );
    Delay_1ms( );
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1 );
    
    i2c_master_set_slave_address( &ctx->i2c, I2CEXTEND_I2C_SLAVE_ADDR_0 );
    Delay_1ms( );

    return rx_buf[ 0 ];
}

void i2cextend_rmt_multi_write ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes ) {
    uint8_t n_cnt;
    uint8_t tx_buf[ 255 ];

    tx_buf[ 0 ] = reg;

    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) {
        tx_buf[ n_cnt + 1 ] = p_tx_data[ n_cnt ];
    }

    i2c_master_set_slave_address( &ctx->i2c, rmt_slave_addr );
    Delay_1ms( );
    
    i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 1 );
    
    i2c_master_set_slave_address( &ctx->i2c, I2CEXTEND_I2C_SLAVE_ADDR_0 );
    Delay_1ms( );
}

void i2cextend_rmt_multi_read ( i2cextend_t *ctx, uint8_t rmt_slave_addr, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_set_slave_address( &ctx->i2c, rmt_slave_addr );
    Delay_1ms( );
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, p_rx_data, n_bytes );
    
    i2c_master_set_slave_address( &ctx->i2c, I2CEXTEND_I2C_SLAVE_ADDR_0 );
    Delay_1ms( );
}

void i2cextend_set_config ( i2cextend_t *ctx, uint8_t intr_mode, uint8_t ctrl_sel ) {
    uint8_t tmp;
    
    intr_mode &= I2CEXTEND_CONFIG_INTR_MODE_BIT_MASK;
    ctrl_sel &= I2CEXTEND_CONFIG_CTRL_SEL_BIT_MASK;

    tmp = i2cextend_generic_read( ctx, I2CEXTEND_REG_CONFIG );
    tmp |= intr_mode;
    tmp |= ctrl_sel;
    
    i2cextend_generic_write( ctx, I2CEXTEND_REG_CONFIG, tmp );
}

void i2cextend_status ( i2cextend_t *ctx, i2cextend_status_data_t *status_data ) {
    uint8_t status;

    status = i2cextend_generic_read( ctx, I2CEXTEND_REG_STATUS );

    status_data->nlink = status & 0x01;
    status_data->nalert = ( status & 0x02 ) >> 1;
    status_data->ext_nalert = ( status & 0x04 ) >> 2;
    status_data->speed_idx = ( status & 0xF0 ) >> 4;
}

void i2cextend_enable_alerts ( i2cextend_t *ctx, uint8_t link_good, uint8_t link_lost, uint8_t fault ) {
    uint8_t tmp;

    link_good &= I2CEXTEND_ALERT_EN_LINK_GOOD;
    link_lost &= I2CEXTEND_ALERT_EN_LINK_LOST;
    fault &= I2CEXTEND_ALERT_EN_FAULT;

    tmp = i2cextend_generic_read( ctx, I2CEXTEND_REG_ALERT_EN );
    tmp |= link_good;
    tmp |= link_lost;
    tmp |= fault;

    i2cextend_generic_write( ctx, I2CEXTEND_REG_ALERT_EN, tmp );
}

void i2cextend_fault ( i2cextend_t *ctx, i2cextend_fault_data_t *fault_data ) {
    uint8_t fault_val;

    fault_val = i2cextend_generic_read( ctx, I2CEXTEND_REG_FAULT );

    fault_data->i2c_write_fault = fault_val & 0x01;
    fault_data->link_fault = ( fault_val & 0x02 ) >> 1;
    fault_data->ext_i2c_fault = ( fault_val & 0x04 ) >> 2;
    fault_data->tx_buf_overflow = ( fault_val & 0x08 ) >> 3;
}

uint8_t i2cextend_get_scratch ( i2cextend_t *ctx ) {
    uint8_t rx_buf;

    rx_buf = i2cextend_generic_read( ctx, I2CEXTEND_REG_SCRATCH );

    return rx_buf;
}

void i2cextend_set_out_slave_address ( i2cextend_t *ctx, uint8_t out_slave_address ) {
    uint8_t addr_trans;
    
    addr_trans = I2CEXTEND_I2C_SLAVE_ADDR_0;
    addr_trans ^= out_slave_address;

    i2cextend_generic_write( ctx, I2CEXTEND_REG_ADDR_TRANS, addr_trans );
}

void i2cextend_set_out_ctrl ( i2cextend_t *ctx, uint8_t out_ctrl ) {
    if ( out_ctrl == I2CEXTEND_PIN_STATE_LOW ) {
        i2cextend_generic_write( ctx, I2CEXTEND_REG_CTRL, I2CEXTEND_CTRL_SEL_L );
    } else {
        i2cextend_generic_write( ctx, I2CEXTEND_REG_CTRL, I2CEXTEND_CTRL_SEL_H );
    }
}

void i2cextend_set_rst ( i2cextend_t *ctx, uint8_t en_rst ) {
    if ( en_rst == I2CEXTEND_PIN_STATE_LOW ) {
        digital_out_low( &ctx->rst );
    } else {
        digital_out_high( &ctx->rst );
    }
}

void i2cextend_set_cs ( i2cextend_t *ctx, uint8_t en_cs ) {
    if ( en_cs == I2CEXTEND_PIN_STATE_LOW ) {
        digital_out_low( &ctx->cs );
    } else { 
        digital_out_high( &ctx->cs );
    }
}

void i2cextend_set_on ( i2cextend_t *ctx, uint8_t on_state ) {
    if ( on_state == I2CEXTEND_PIN_STATE_LOW ) {
        digital_out_low( &ctx->on );
    } else { 
        digital_out_high( &ctx->on );
    }
}

uint8_t i2cextend_check_int ( i2cextend_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
