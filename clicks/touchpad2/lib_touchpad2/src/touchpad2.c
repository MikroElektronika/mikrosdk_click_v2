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
 * @file touchpad2.c
 * @brief TouchPad 2 Click Driver.
 */

#include "touchpad2.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_rdy_wait_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void touchpad2_cfg_setup ( touchpad2_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TOUCHPAD2_SET_DEV_ADDR;
}

err_t touchpad2_init ( touchpad2_t *ctx, touchpad2_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t touchpad2_default_cfg ( touchpad2_t *ctx ) {
    err_t status;
    touchpad2_channel_setup_t ch_setup;
    
    status = TOUCHPAD2_OK;
    
    ch_setup.total_rx = 5;
    ch_setup.total_tx = 4;
    ch_setup.track_pad_rx = 5;
    ch_setup.track_pad_tx = 4;
    ch_setup.pm_setup = TOUCHPAD2_CHARGE_MUTUAL_SELF_CHARG;
    ch_setup.pm_setup |= TOUCHPAD2_RX_GROUP_RXA;
    ch_setup.pm_setup |= TOUCHPAD2_SUM_OF_TP_TX;
    ch_setup.tx_config = TOUCHPAD2_TX_CFG_DEFAULT;
    
    status |= touchpad2_channel_setup( ctx, ch_setup );
    
    return status;
}

err_t touchpad2_generic_write ( touchpad2_t *ctx, uint8_t cmd, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = cmd;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t touchpad2_generic_read ( touchpad2_t *ctx, uint8_t cmd, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, rx_buf, rx_len );
}

uint8_t touchpad2_check_interrupt ( touchpad2_t *ctx ) {    
    return digital_in_read( &ctx->int_pin ); 
}

void touchpad2_wait_ready ( touchpad2_t *ctx ) {
    while ( digital_in_read( &ctx->int_pin ) == 0 ){
        dev_rdy_wait_delay( );
    }
}

err_t touchpad2_channel_setup ( touchpad2_t *ctx, touchpad2_channel_setup_t ch_setup ) {
    err_t status;
    uint8_t tx_buf[ 8 ];
    
    status = TOUCHPAD2_OK;
    
    tx_buf[ 0 ] = ch_setup.total_rx;
    tx_buf[ 1 ] = ch_setup.total_tx;
    tx_buf[ 2 ] = ch_setup.track_pad_rx;
    tx_buf[ 3 ] = ch_setup.track_pad_tx;
    tx_buf[ 4 ] = ch_setup.pm_setup;
    tx_buf[ 5 ] = ( uint8_t ) ( ch_setup.tx_config >> 8 );
    tx_buf[ 6 ] = ( uint8_t ) ch_setup.tx_config;
    
    status |= touchpad2_generic_write( ctx, TOUCHPAD2_CMD_CHANNEL_SETUP, tx_buf, 7 );
    
    return status;
}

err_t touchpad2_check_version ( touchpad2_t *ctx, touchpad2_ver_info_t *ver_info ) {
    err_t status;
    uint8_t rx_buf[ 10 ];
    uint16_t tmp;
    float ver;
    
    status = TOUCHPAD2_OK;

    status |= touchpad2_generic_read( ctx, TOUCHPAD2_CMD_VERSION_INFO, rx_buf, 10 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    ver_info->product_num = tmp;
    
    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];
    ver_info->projec_num = tmp;
    
    ver = ( float ) rx_buf[ 4 ];
    
    if ( rx_buf[ 5 ] > 99 ) {
        ver += ( float ) ( ( float ) rx_buf[ 5 ] / 1000 );    
    } else if ( rx_buf[ 5 ] > 9 ) {
        ver += ( float ) ( ( float  )rx_buf[ 5 ] / 100 );       
    } else {
        ver += ( float ) (( float ) rx_buf[ 5 ] / 10 );   
    }
    
    ver_info->version = ver;
    
    tmp = rx_buf[ 6 ];
    tmp <<= 8;
    tmp |= rx_buf[ 7 ];
    ver_info->hw_id = tmp;
    
    tmp = rx_buf[ 8 ];
    tmp <<= 8;
    tmp |= rx_buf[ 9 ];
    ver_info->hw_revision = tmp;
    
    return status;
}

err_t touchpad2_get_touch ( touchpad2_t *ctx, touchpad2_touch_t *touch_data ) {
    err_t status;
    uint8_t rx_buf[ 8 ];
    uint16_t tmp;
    
    status = TOUCHPAD2_OK;

    status |= touchpad2_generic_read( ctx, TOUCHPAD2_CMD_XY_DATA, rx_buf, 8 );

    touch_data->xy_info = rx_buf[ 0 ];
    
    touch_data->no_of_fingers = rx_buf[ 0 ] & TOUCHPAD2_NO_OF_FINGERS; 
    
    touch_data->id_tag = rx_buf[ 1 ];
    
    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];
    touch_data->x_pos = tmp;
    
    tmp = rx_buf[ 4 ];
    tmp <<= 8;
    tmp |= rx_buf[ 5 ];
    touch_data->y_pos = tmp;
    
    tmp = rx_buf[ 6 ];
    tmp <<= 8;
    tmp |= rx_buf[ 7 ];
    touch_data->touch_str = tmp;
    
    return status;
}

err_t touchpad2_get_all_data ( touchpad2_t *ctx, uint8_t *rx_data ) {
    err_t status;
    
    status = TOUCHPAD2_OK;

    status |= touchpad2_generic_read( ctx, TOUCHPAD2_CMD_XY_DATA, rx_data, 36 );
    
    return status;
}

err_t touchpad2_get_status ( touchpad2_t *ctx, uint8_t sel_status, uint16_t *rx_data ) {
    err_t status;
    uint8_t rx_buf[ 8 ];
    uint16_t tmp;
    
    status = TOUCHPAD2_OK;

    if ( sel_status == TOUCHPAD2_PROXIMITY_STATUS ) {
        touchpad2_generic_read( ctx, TOUCHPAD2_CMD_PROXIMITY_STATUS, rx_buf, 8 );
    } else if ( sel_status == TOUCHPAD2_TOUCH_STATUS ) {
        touchpad2_generic_read( ctx, TOUCHPAD2_CMD_TOUCH_STATUS, rx_buf, 8 );   
    } else {
        touchpad2_generic_read( ctx, TOUCHPAD2_CMD_SNAP_STATUS, rx_buf, 8 );       
    }

    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];
    rx_data[ 0 ] = tmp;
    
    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    rx_data[ 1 ] = tmp;
    
    tmp = rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];
    rx_data[ 2 ] = tmp;
    
    tmp = rx_buf[ 7 ];
    tmp <<= 8;
    tmp |= rx_buf[ 6 ];
    rx_data[ 3 ] = tmp;
    
    return status;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_rdy_wait_delay ( void ) {
    Delay_1us( );
}

// ------------------------------------------------------------------------- END
