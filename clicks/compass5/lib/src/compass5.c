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
 * @file compass5.c
 * @brief Compass 5 Click Driver.
 */

#include "compass5.h"

void compass5_cfg_setup ( compass5_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COMPASS5_SET_DEV_ADDR;
}

err_t compass5_init ( compass5_t *ctx, compass5_cfg_t *cfg ) {
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

err_t compass5_generic_write ( compass5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ){
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t compass5_generic_read ( compass5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void compass5_write_byte ( compass5_t *ctx, uint8_t reg, uint8_t tx_data ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;
    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t compass5_read_byte ( compass5_t *ctx, uint8_t reg ) {
    uint8_t rx_data;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, &rx_data, 1);
    return rx_data;
}

void compass5_sw_reset ( compass5_t *ctx ) {
    compass5_write_byte( ctx, COMPASS5_CONTROL_3_SETTINGS, COMPASS5_SRST_BIT );
}

void compass5_get_id ( compass5_t *ctx, uint8_t *company_id, uint8_t *device_id ) {
    uint8_t rx_buf[ 2 ];

    compass5_generic_read( ctx, COMPASS5_COMPANI_ID, rx_buf, 2 );
    *company_id = rx_buf[ 0 ];
    *device_id = rx_buf[ 1 ];
}

uint8_t compass5_check_data_ready ( compass5_t *ctx ) {
    uint8_t drdy;

    compass5_generic_read( ctx, COMPASS5_DATA_STATUS_1, &drdy, 1 );
    drdy &= COMPASS5_BIT_MASK_BIT0;
    return drdy;
}

uint8_t compass5_check_data_overrun ( compass5_t *ctx ) {
    uint8_t dor;

    compass5_generic_read( ctx, COMPASS5_DATA_STATUS_1, &dor, 1 );
    dor >>= 1;
    dor &= COMPASS5_BIT_MASK_BIT0;
    return dor;
}

uint8_t compass5_set_operation_mode ( compass5_t *ctx, uint8_t op_mode ) {
    uint8_t status;

    if ( ( op_mode == COMPASS5_MODE_POWER_DOWN )            ||
         ( op_mode == COMPASS5_MODE_SINGLE_MEASUREMENT )    ||
         ( op_mode == COMPASS5_MODE_CON_MEASUREMENT_10HZ )  ||
         ( op_mode == COMPASS5_MODE_CON_MEASUREMENT_20HZ )  ||
         ( op_mode == COMPASS5_MODE_CON_MEASUREMENT_50HZ )  ||
         ( op_mode == COMPASS5_MODE_CON_MEASUREMENT_100HZ ) ||
         ( op_mode == COMPASS5_MODE_SELF_TEST ) ) {
       
        status = COMPASS5_OK;
        compass5_write_byte( ctx, COMPASS5_CONTROL_2_SETTINGS, op_mode );
    }
    else {
        status = COMPASS5_ERROR;
    }
    return status;
}

uint8_t compass5_get_operation_mode ( compass5_t *ctx ) {
    uint8_t op_mode;

    op_mode = compass5_read_byte( ctx, COMPASS5_CONTROL_2_SETTINGS );
    return op_mode;
}

void compass5_measurement_axis ( compass5_t *ctx, int16_t *axis_x, int16_t *axis_y, int16_t *axis_z ) {
    uint8_t all_axis[ 6 ];
    uint8_t reader_buff[ 1 ];
    uint8_t status;

    compass5_generic_read( ctx, COMPASS5_X_AXIS_DATA_H, reader_buff, 1 );
    all_axis[ 0 ] = reader_buff[ 0 ];

    compass5_generic_read( ctx, COMPASS5_X_AXIS_DATA_L, reader_buff, 1 );
    all_axis[ 1 ] = reader_buff[ 0 ];

    compass5_generic_read( ctx, COMPASS5_Y_AXIS_DATA_H, reader_buff, 1 );
    all_axis[ 2 ] = reader_buff[ 0 ];

    compass5_generic_read( ctx, COMPASS5_Y_AXIS_DATA_L, reader_buff, 1 );
    all_axis[ 3 ] = reader_buff[ 0 ];

    compass5_generic_read( ctx, COMPASS5_Z_AXIS_DATA_H, reader_buff, 1 );
    all_axis[ 4 ] = reader_buff[ 0 ];

    compass5_generic_read( ctx, COMPASS5_Z_AXIS_DATA_L, reader_buff, 1 );
    all_axis[ 5 ] = reader_buff[ 0 ];
    
    compass5_generic_read( ctx, COMPASS5_DATA_STATUS_2, &status, 1 );

    *axis_x = all_axis[ 0 ];
    *axis_x <<= 8;
    *axis_x |= all_axis[ 1 ];

    *axis_y = all_axis[ 2 ];
    *axis_y <<= 8;
    *axis_y |= all_axis[ 3 ];

    *axis_z = all_axis[ 4 ];
    *axis_z <<= 8;
    *axis_z |= all_axis[ 5 ];
}

void compass5_get_mag_data ( compass5_t *ctx, int16_t *axis_x, int16_t *axis_y, int16_t *axis_z ) {
    uint8_t rx_buf[ 6 ];

    compass5_generic_read( ctx, COMPASS5_X_AXIS_DATA_L, rx_buf, 6 );

    *axis_x = rx_buf[ 1 ];
    *axis_x <<= 8;
    *axis_x |= rx_buf[ 0 ];

    *axis_y = rx_buf[ 3 ];
    *axis_y <<= 8;
    *axis_y |= rx_buf[ 2 ];

    *axis_z = rx_buf[ 5 ];
    *axis_z <<= 8;
    *axis_z |= rx_buf[ 4 ];
}



// ------------------------------------------------------------------------- END
