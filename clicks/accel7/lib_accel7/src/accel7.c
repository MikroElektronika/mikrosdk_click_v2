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

#include "accel7.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel7_cfg_setup ( accel7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ACCEL7_DEVICE_ADDRESS;
    cfg->dev_data_resolution = 0;
}

ACCEL7_RETVAL accel7_init ( accel7_t *ctx, accel7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->data_resolution = cfg->dev_data_resolution;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ACCEL7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ACCEL7_OK;
}

void accel7_default_cfg ( accel7_t *ctx, uint8_t resolution, uint8_t range )
{
    // Data resolution 8bit, 12bit and 14bit
    // Axis range +-2g, +-4g, +-8g and +-16g

    ctx->data_resolution = resolution;

    accel7_res_range_cfg( ctx, &resolution, &range );

    accel7_write_byte ( ctx, ACCEL7_REG_CTRL_REG1,
                     ACCEL7_CTRL_REG1_MODE_OPERATING |
                     ACCEL7_CTRL_REG1_DRDYE_DISABLE | 
                     resolution |
                     range );
}

void accel7_generic_write ( accel7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void accel7_generic_read ( accel7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void accel7_write_byte ( accel7_t *ctx, uint8_t reg, uint8_t input_data )
{
    uint8_t write_buf[ 1 ];
    
    write_buf[ 0 ] = input_data;
    
    accel7_generic_write( ctx, reg, write_buf, 1 );
}

uint8_t accel7_read_byte( accel7_t *ctx, uint8_t reg )
{
    uint8_t read_buf[ 1 ] = {0};
        
    accel7_generic_read( ctx, reg, read_buf, 1 );
    
    return read_buf[ 0 ];
}

int16_t accel7_get_axis ( accel7_t *ctx, uint8_t axis )
{
    int16_t axis_data;

    axis_data = accel7_read_byte( ctx, axis + 1 );
    axis_data <<= 8;
    axis_data |= accel7_read_byte( ctx, axis );
        
    if( ctx->data_resolution == ACCEL7_DATA_RESP_12bit )
    {
        axis_data >>= 4;
    }
    else if ( ctx->data_resolution == ACCEL7_DATA_RESP_14bit )
    {
        axis_data >>= 2;
    }
    else
    {
        axis_data >>= 8;
    }

    return axis_data;
}

void accel7_res_range_cfg ( accel7_t *ctx, uint8_t *resolution, uint8_t *range ) 
{
    uint8_t set_resolution;
    uint8_t set_range;

    if ( *resolution == ACCEL7_DATA_RESP_12bit )
    {
        if ( *range == ACCEL7_RANGE_8g )
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_8g;
        }
        else if ( *range == ACCEL7_RANGE_16g )
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_16g;
        }
        else
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_4g;
        }
        set_resolution = ACCEL7_CTRL_REG1_RES_HIGH_RESOLUTION;
    }
    else if ( *resolution == ACCEL7_DATA_RESP_14bit )
    {
        if ( *range == ACCEL7_RANGE_16g )
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_16g;
        }
        else
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_8g;
        }
        set_resolution = ACCEL7_CTRL_REG1_RES_HIGH_RESOLUTION;
    }
    else
    {
        if ( *range == ACCEL7_RANGE_16g )
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_16g;
        }
        else if ( *range == ACCEL7_RANGE_8g )
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_8g;
        }
        else if ( *range == ACCEL7_RANGE_4g )
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_4g;
        }
        else
        {
            set_range = ACCEL7_CTRL_REG1_RANGE_2g;
        }
        set_resolution = ACCEL7_CTRL_REG1_RES_HIGH_RESOLUTION;
    }

    *resolution = set_resolution;
    *range = set_range;
}

uint8_t accel7_get_interrupt_state ( accel7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

