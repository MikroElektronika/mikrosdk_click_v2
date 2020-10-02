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

#include "accel8.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel8_cfg_setup ( accel8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->da = HAL_PIN_NC;
    cfg->cl = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ACCEL8_DEVICE_SLAVE_ADDRESS_ADD;
}

ACCEL8_RETVAL accel8_init ( accel8_t *ctx, accel8_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ACCEL8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->da, cfg->da );
    digital_in_init( &ctx->cl, cfg->cl );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ACCEL8_OK;
}

void accel8_default_cfg ( accel8_t *ctx, uint8_t accel_cfg, uint8_t gyro_cfg, range_retval_t *rng )
{
    uint8_t temp_write;
    uint8_t range;

    temp_write = ACCEL8_PM1_CLKSEL_INTERNAL_8MHZ_OSCILLATOR;
    accel8_generic_write( ctx, ACCEL8_REG_PWR_MGMT_1, &temp_write, 1 );
    temp_write = ACCEL8_INTE_DATA_RDY_ENABLE;
    accel8_generic_write( ctx, ACCEL8_REG_INT_ENABLE, &temp_write, 1 );
     
    accel8_generic_write( ctx, ACCEL8_REG_ACCEL_CONFIG, &accel_cfg, 1 );

    range = accel_cfg >> 3;
     
    switch ( range )
    {
        case 0:
        {
            rng->accel_range = 2;
            break;
        }
        case 1:
        {
            rng->accel_range = 4;
            break;
        }
        case 2:
        {
            rng->accel_range = 8;
            break;
        }
        case 3:
        {
            rng->accel_range = 16;
            break;
        }
    }

    accel8_generic_write( ctx, ACCEL8_REG_GYRO_CONFIG, &gyro_cfg, 1 );
    
    range = gyro_cfg >> 3;

    switch ( range )
    {
        case 0:
        {
            rng->gyro_range = 250;
            break;
        }
        case 1:
        {
            rng->gyro_range = 500;
            break;
        }
        case 2:
        {
            rng->gyro_range = 1000;
            break;
        }
        case 3:
        {
            rng->gyro_range = 2000;
            break;
        }
    }

    temp_write = ACCEL8_FIFO_ENABLE_TEMP | ACCEL8_FIFO_ENABLE_X_AXIS_GYRO |
                                          ACCEL8_FIFO_ENABLE_Y_AXIS_GYRO |
                                          ACCEL8_FIFO_ENABLE_Z_AXIS_GYRO |
                                          ACCEL8_FIFO_ENABLE_ACCEL;
    accel8_generic_write( ctx, ACCEL8_REG_FIFO_EN, &temp_write, 1 );
}

void accel8_generic_write ( accel8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );      
}

void accel8_generic_read ( accel8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t accel8_read_data ( accel8_t *ctx, uint8_t reg )
{
    uint8_t data_buff[ 2 ];
    uint16_t read_data;

    accel8_generic_read( ctx, reg, data_buff, 2 );

    read_data = data_buff[ 0 ];
    read_data <<=  8;
    read_data |= data_buff[ 1 ];

    return read_data;
}

float accel8_get_temperature ( accel8_t *ctx )
{
    volatile int16_t temp_out;

    temp_out = accel8_read_data( ctx, ACCEL8_TEMP_DATA );
    return ( ( ( float )temp_out / 340.0f ) + 36.53f );
}

void accel8_get_accel_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis )
{
    *x_axis = accel8_read_data( ctx, ACCEL8_ACCEL_X_AXIS_DATA );
    *y_axis = accel8_read_data( ctx, ACCEL8_ACCEL_Y_AXIS_DATA );
    *z_axis = accel8_read_data( ctx, ACCEL8_ACCEL_Z_AXIS_DATA );
}

void accel8_get_gyro_axis ( accel8_t *ctx, int16_t *x_axis, int16_t *y_axis, int16_t *z_axis )
{
    *x_axis = accel8_read_data( ctx, ACCEL8_GYRO_X_AXIS_DATA );
    *y_axis = accel8_read_data( ctx, ACCEL8_GYRO_Y_AXIS_DATA );
    *z_axis = accel8_read_data( ctx, ACCEL8_GYRO_Z_AXIS_DATA );
}

uint8_t accel8_get_interrupt ( accel8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}
// ------------------------------------------------------------------------- END

