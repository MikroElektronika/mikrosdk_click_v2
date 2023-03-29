/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "compass.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void compass_cfg_setup ( compass_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rdy = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_accel_address = 0x19;
    cfg->i2c_magnet_address = 0x1E;
}

COMPASS_RETVAL compass_init ( compass_t *ctx, compass_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl      = cfg->scl;
    i2c_cfg.sda      = cfg->sda;

    ctx->accel_slave_address = cfg->i2c_accel_address;
    ctx->magnet_slave_address = cfg->i2c_magnet_address;
      
    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COMPASS_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return COMPASS_OK;
}

void compass_accel_generic_write ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->accel_slave_address );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void compass_magnet_generic_write ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->magnet_slave_address );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}


void compass_accel_generic_read ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->accel_slave_address );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void compass_magnet_generic_read ( compass_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->magnet_slave_address );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void compass_default_config ( compass_t *ctx )
{
    uint8_t temp_buff[ 1 ];

    *temp_buff = 0x27;
    compass_accel_generic_write( ctx, COMPASS_CTRL_REG1, temp_buff, 1 );
    *temp_buff = 0x40;
    compass_accel_generic_write( ctx, COMPASS_CTRL_REG4, temp_buff, 1 );
    *temp_buff = 0x40;
    compass_accel_generic_write( ctx, COMPASS_CTRL_REG5, temp_buff, 1 );
    *temp_buff = 0x80;
    compass_accel_generic_write( ctx, COMPASS_FIFO_CTRL_REG, temp_buff, 1 );
    
    *temp_buff = 0x9C;
    compass_magnet_generic_write( ctx, COMPASS_CRA_REG, temp_buff, 1 );
    *temp_buff = 0x20;
    compass_magnet_generic_write( ctx, COMPASS_CRB_REG, temp_buff, 1 );
    *temp_buff = 0x00;
    compass_magnet_generic_write( ctx, COMPASS_MR_REG,  temp_buff, 1 );
    *temp_buff = 0x48;
    compass_magnet_generic_write( ctx, COMPASS_IRA_REG, temp_buff, 1 );
    *temp_buff = 0x34;
    compass_magnet_generic_write( ctx, COMPASS_IRB_REG, temp_buff, 1 );
    *temp_buff = 0x33;
    compass_magnet_generic_write( ctx, COMPASS_IRC_REG, temp_buff, 1 );
}

void compass_read_accel_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis )
{
    uint8_t all_axes[ 6 ];
    uint8_t reader_buff[ 1 ];

    compass_accel_generic_read( ctx, COMPASS_OUT_ACCEL_X_HIGH, reader_buff, 1 );
    all_axes[ 0 ] = reader_buff[ 0 ];

    compass_accel_generic_read( ctx, COMPASS_OUT_ACCEL_X_LOW, reader_buff, 1 );
    all_axes[ 1 ] = reader_buff[ 0 ];

    compass_accel_generic_read( ctx, COMPASS_OUT_ACCEL_Y_HIGH, reader_buff, 1 );
    all_axes[ 2 ] = reader_buff[ 0 ];

    compass_accel_generic_read( ctx, COMPASS_OUT_ACCEL_Y_LOW, reader_buff, 1 );
    all_axes[ 3 ] = reader_buff[ 0 ];

    compass_accel_generic_read( ctx, COMPASS_OUT_ACCEL_Z_HIGH, reader_buff, 1 );
    all_axes[ 4 ] = reader_buff[ 0 ];

    compass_accel_generic_read( ctx, COMPASS_OUT_ACCEL_Z_LOW, reader_buff, 1 );
    all_axes[ 5 ] = reader_buff[ 0 ];

    *x_axis = all_axes[ 0 ];
    *x_axis <<= 8;
    *x_axis |= all_axes[ 1 ];
    
    *y_axis = all_axes[ 2 ];
    *y_axis <<= 8;
    *y_axis |= all_axes[ 3 ];
    
    *z_axis = all_axes[ 4 ];
    *z_axis <<= 8;
    *z_axis |= all_axes[ 5 ];
}

void compass_read_magnet_axis ( compass_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis )
{
    uint8_t all_axes[ 6 ];
    uint8_t reader_buff[ 1 ];
    
    compass_magnet_generic_read( ctx, COMPASS_OUT_MAGNET_X_HIGH, reader_buff, 1 );
    all_axes[ 0 ] = reader_buff[ 0 ];

    compass_magnet_generic_read( ctx, COMPASS_OUT_MAGNET_X_LOW, reader_buff, 1 );
    all_axes[ 1 ] = reader_buff[ 0 ];

    compass_magnet_generic_read( ctx, COMPASS_OUT_MAGNET_Y_HIGH, reader_buff, 1 );
    all_axes[ 2 ] = reader_buff[ 0 ];

    compass_magnet_generic_read( ctx, COMPASS_OUT_MAGNET_Y_LOW, reader_buff, 1 );
    all_axes[ 3 ] = reader_buff[ 0 ];

    compass_magnet_generic_read( ctx, COMPASS_OUT_MAGNET_Z_HIGH, reader_buff, 1 );
    all_axes[ 4 ] = reader_buff[ 0 ];

    compass_magnet_generic_read( ctx, COMPASS_OUT_MAGNET_Z_LOW, reader_buff, 1 );
    all_axes[ 5 ] = reader_buff[ 0 ];

    *x_axis = all_axes[ 0 ];
    *x_axis <<= 8;
    *x_axis |= all_axes[ 1 ];
    
    *y_axis = all_axes[ 2 ];
    *y_axis <<= 8;
    *y_axis |= all_axes[ 3 ];
    
    *z_axis = all_axes[ 4 ];
    *z_axis <<= 8;
    *z_axis |= all_axes[ 5 ];
}

// ------------------------------------------------------------------------- END

