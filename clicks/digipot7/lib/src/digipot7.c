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
 * @file digipot7.c
 * @brief DIGI POT 7 Click Driver.
 */

#include "digipot7.h"

void digipot7_cfg_setup ( digipot7_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIGIPOT7_I2C_SLAVE_ADDRESS_GND;
}

err_t digipot7_init ( digipot7_t *ctx, digipot7_cfg_t *cfg ) {
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

    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

void digipot7_generic_write ( digipot7_t *ctx, uint8_t cmd, uint16_t data_byte ) {
    uint8_t data_buf[ 2 ];
    
    data_byte &= DIGIPOT7_10_BIT;
    
    data_buf[ 0 ] = cmd;
    data_buf[ 0 ] |= ( uint8_t ) ( data_byte >> 8 );
    data_buf[ 1 ] = ( uint8_t ) data_byte;

    i2c_master_write( &ctx->i2c, data_buf, 2 );
}

uint16_t digipot7_generic_read ( digipot7_t *ctx, uint8_t cmd, uint8_t wiper_pos ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint16_t result;

    if ( cmd == DIGIPOT7_COMMAND_READ_50TP ) {
        if ( wiper_pos > 0x38 ) {
            wiper_pos = 0x38;
        }

        tx_buf[ 1 ] = wiper_pos;
    } else {
        tx_buf[ 1 ] = 0x00;
    }

    tx_buf[ 0 ] = cmd;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 2 );
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    result &= DIGIPOT7_10_BIT;

    return result;
}

void digipot7_hw_reset ( digipot7_t *ctx ) {
    digital_out_low( &ctx->rst );
    Delay_100ms();
    digital_out_high( &ctx->rst );
}

uint16_t digipot7_read_rdac ( digipot7_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint16_t result;

    tx_buf[ 0 ] = DIGIPOT7_COMMAND_READ_RDAC;
    tx_buf[ 1 ] = DIGIPOT7_DUMMY;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    result &= DIGIPOT7_10_BIT;

    return result;
}

void digipot7_enable_write ( digipot7_t *ctx ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = DIGIPOT7_COMMAND_WRITE_MEMORY;
    tx_buf[ 1 ] = DIGIPOT7_UPDATE_WIPER_POS;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

void digipot7_write_rdac ( digipot7_t *ctx, uint16_t rdac_data ) {
    uint8_t tx_buf[ 2 ];

    rdac_data &= DIGIPOT7_10_BIT;

    tx_buf[ 0 ] = DIGIPOT7_COMMAND_WRITE_RDAC;
    tx_buf[ 0 ] |= ( uint8_t ) ( rdac_data >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) rdac_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

err_t digipot7_set_resistance ( digipot7_t *ctx, uint16_t res_ohm ) {
    uint8_t status;
    uint16_t rdac_data;
    float tmp;
    
    status = DIGIPOT7_OK;

    if ( res_ohm > 10000 ) {
        status = DIGIPOT7_ERROR;
    } else {
        tmp = 1024.0;
        tmp *= ( float ) res_ohm;
        tmp /= 10000.0;
        
        rdac_data = ( uint16_t ) tmp;
        
        digipot7_write_rdac( ctx, rdac_data );
    }

    return status;
}

void digipot7_sw_reset ( digipot7_t *ctx ) {
    digipot7_generic_write( ctx, DIGIPOT7_COMMAND_SW_RESET, DIGIPOT7_DUMMY );
}

void digipot7_store_wiper ( digipot7_t *ctx ) {
    digipot7_generic_write( ctx, DIGIPOT7_COMMAND_STORE_WIPER, DIGIPOT7_DUMMY );
}

void digipot7_operating_mode ( digipot7_t *ctx, uint8_t mode ) {
    mode &= DIGIPOT7_SHUTDOWN_BIT_MASK;

    if ( mode == DIGIPOT7_NORMAL_MODE ) {
        digipot7_generic_write( ctx, DIGIPOT7_COMMAND_SW_SHUTDOWN, DIGIPOT7_NORMAL_MODE );
    } else {
        digipot7_generic_write( ctx, DIGIPOT7_COMMAND_SW_SHUTDOWN, DIGIPOT7_SHUTDOWN_MODE );
    }
}

uint16_t digipot7_next_frame_read ( digipot7_t *ctx, uint8_t wiper_location ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint16_t result;

    tx_buf[ 0 ] = DIGIPOT7_COMMAND_READ_RDAC;
    tx_buf[ 1 ] = wiper_location;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    result &= DIGIPOT7_10_BIT;

    return result;
}

uint16_t digipot7_read_memory ( digipot7_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint16_t result;

    tx_buf[ 0 ] = DIGIPOT7_COMMAND_READ_MEMORY;
    tx_buf[ 1 ] = DIGIPOT7_DUMMY;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    result &= DIGIPOT7_10_BIT;

    return result;
}

uint8_t digipot7_read_control ( digipot7_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint8_t result;

    tx_buf[ 0 ] = DIGIPOT7_COMMAND_READ_CONTROL;
    tx_buf[ 1 ] = DIGIPOT7_DUMMY;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 2 );

    result = rx_buf[ 0 ];

    result &= DIGIPOT7_CTRL_REG_BIT_MASK;

    return result;
}

// ------------------------------------------------------------------------- END
