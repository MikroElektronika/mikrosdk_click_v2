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
 * @file nvsram.c
 * @brief nvSRAM Click Driver.
 */

#include "nvsram.h"

static uint8_t dev_slave_addr;
static uint8_t dev_slave_addr_mem;

void nvsram_cfg_setup ( nvsram_cfg_t *cfg ) {
    
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NVSRAM_I2C_SLAVE_ADDR_0;
    
    dev_slave_addr = NVSRAM_I2C_SLAVE_ADDR_0;
    dev_slave_addr_mem = NVSRAM_I2C_MEM_SEL | ( NVSRAM_I2C_SLAVE_ADDR_0 & 0x06 );
}

err_t nvsram_init ( nvsram_t *ctx, nvsram_cfg_t *cfg ) {
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

    digital_out_init( &ctx->wp, cfg->wp );
  
    return I2C_MASTER_SUCCESS;
}

err_t nvsram_generic_write ( nvsram_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t nvsram_generic_read ( nvsram_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, reg, 1, rx_buf, rx_len );
}

void nvsram_reg_write ( nvsram_t *ctx, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2);
}

uint8_t nvsram_reg_read ( nvsram_t *ctx, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1);

    return rx_buf[ 0 ];
}

void nvsram_burst_reg_write ( nvsram_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes ) {
    uint8_t n_cnt;
    uint8_t tx_buf[ 255 ];

    tx_buf[ 0 ] = reg;

    for ( n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) {
        tx_buf[ n_cnt + 1 ] = p_tx_data[ n_cnt ];
    }

    i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 1 );
}

void nvsram_burst_reg_read ( nvsram_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, p_rx_data, n_bytes);
}

void nvsram_send_cmd ( nvsram_t *ctx, uint8_t cmd ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = NVSRAM_CMD_REG;
    tx_buf[ 1 ] = cmd;
    
    i2c_master_write( &ctx->i2c, tx_buf, 2);
}

uint32_t nvsram_read_dev_id ( nvsram_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 4 ];
    uint32_t dev_id;

    tx_buf[ 0 ] = NVSRAM_DEV_ID_REG_1;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 4 );

    dev_id = rx_buf[ 0 ];
    dev_id <<= 8;
    dev_id |= rx_buf[ 1 ];
    dev_id <<= 8;
    dev_id |= rx_buf[ 2 ];
    dev_id <<= 8;
    dev_id |= rx_buf[ 3 ];

    return dev_id;
}

void nvsram_memory_write ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_tx_data, uint16_t n_bytes ) {
    uint8_t tx_buf[ 255 ];
    uint16_t cnt;

    mem_adr &= 0x0001FFFF;
    dev_slave_addr_mem |= ( uint8_t ) ( mem_adr >> 16 );

    i2c_master_set_slave_address( &ctx->i2c, dev_slave_addr_mem );

    tx_buf[ 0 ] = ( uint8_t )( mem_adr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) mem_adr;

    for ( cnt = 0; cnt < n_bytes; cnt++ ) {
        tx_buf[ cnt + 2 ] = p_tx_data[ cnt ];
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 2 );

    i2c_master_set_slave_address( &ctx->i2c, dev_slave_addr );
}

void nvsram_memory_read ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_rx_data, uint16_t n_bytes ) {
    uint8_t tx_buf[ 2 ];

    mem_adr &= 0x0001FFFF;
    dev_slave_addr_mem |= ( uint8_t ) ( mem_adr >> 16 );

    i2c_master_set_slave_address( &ctx->i2c, dev_slave_addr_mem );

    tx_buf[ 0 ] = ( uint8_t )( mem_adr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) mem_adr;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, p_rx_data, n_bytes );
    
    i2c_master_set_slave_address( &ctx->i2c, dev_slave_addr ); 
}

void nvsram_enable_memory_write ( nvsram_t *ctx, uint8_t en_wr_mem ) {
    if ( en_wr_mem == NVSRAM_WRITE_MEMORY_ENABLE ) {
        digital_out_low(&ctx->wp);
    } else {
        digital_out_high(&ctx->wp);
    }
}

// ------------------------------------------------------------------------- END
