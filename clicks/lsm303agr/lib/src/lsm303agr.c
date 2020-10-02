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

#include "lsm303agr.h"


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

uint8_t lsm303agr_read_reg ( lsm303agr_t *ctx, uint8_t reg);
void lsm303agr_write_reg ( lsm303agr_t *ctx, uint8_t reg, uint8_t wr_reg_value);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lsm303agr_cfg_setup ( lsm303agr_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x00;
}

LSM303AGR_RETVAL lsm303agr_init ( lsm303agr_t *ctx, lsm303agr_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LSM303AGR_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LSM303AGR_OK;

}

void lsm303agr_default_cfg ( lsm303agr_t *ctx )
{
     lsm303agr_accelerometer_init ( ctx );
     lsm303agr_magnetometer_init ( ctx );    
}


float lsm303agr_get_acc_axis_x ( lsm303agr_t *ctx )
{
    int16_t  value;
    float  ret_value;
    uint8_t buff[ 2 ];
    ctx->slave_address = 0x19;

    buff[0] = lsm303agr_read_reg ( ctx, 0x28 );
    buff[1] = lsm303agr_read_reg ( ctx, 0x29 );

    value = (int16_t)( ( ( buff[ 1 ] & 0xFF ) << 8) | (buff[ 0 ] & 0xFF ) );
    
    ret_value = ( ( float )( value >> 4 ) * 980.0f + 500.0f) / 1000.0f;

    return ret_value;
}

float lsm303agr_get_acc_axis_y ( lsm303agr_t *ctx )
{
    int16_t  value;
    float  ret_value;
    uint8_t buff[ 2 ];
    ctx->slave_address = 0x19;

    buff[0] = lsm303agr_read_reg ( ctx, 0x2A );
    buff[1] = lsm303agr_read_reg ( ctx, 0x2B );

    value = (int16_t)( ( ( buff[ 1 ] & 0xFF ) << 8 ) | ( buff[ 0 ] & 0xFF));
    
    ret_value = ((float)( value >> 4 ) * 980.0f + 500.0f) / 1000.0f;
    
    return ret_value;
}

float lsm303agr_get_acc_axis_z ( lsm303agr_t *ctx )
{
    int16_t  value;
    float  ret_value;
    uint8_t buff[2];
    ctx->slave_address = 0x19;


    buff[0] = lsm303agr_read_reg ( ctx, 0x2C );
    buff[1] = lsm303agr_read_reg ( ctx, 0x2D );

    value = (int16_t)( ( ( buff[ 1 ] & 0xFF ) << 8) | (buff[ 0 ] & 0xFF));
    
    ret_value = ((float)( value >> 4 ) * 980.0f + 500.0f) / 1000.0f;    

    return ret_value;
}

float lsm303agr_get_mag_axis_x ( lsm303agr_t *ctx )
{
    volatile int16_t  value;
    float  ret_value;
    volatile uint8_t buff[2];
    float sensitivity = 1.5;
    ctx->slave_address = 0x1E;

    buff[0] = lsm303agr_read_reg ( ctx, 0x68 );
    buff[1] = lsm303agr_read_reg ( ctx, 0x69 );

    value = (int16_t)(((buff[1] & 0xff) << 8) | (buff[0] & 0xff));
    
    ret_value = (float) ((int32_t)value) * sensitivity;

    return ret_value;
}

float lsm303agr_get_mag_axis_y ( lsm303agr_t *ctx )
{
    int16_t  value;
    volatile float  ret_value;
    uint8_t buff[2];
    float sensitivity = 1.5;
    ctx->slave_address = 0x1E;

    buff[0] = lsm303agr_read_reg ( ctx, 0x6A );
    buff[1] = lsm303agr_read_reg ( ctx, 0x6B );

    value = (int16_t)(((buff[1] & 0xff) << 8) | (buff[0] & 0xff));
    
    ret_value = (float) ((int32_t)value)* sensitivity; 

    return ret_value;
}

float lsm303agr_get_mag_axis_z (  lsm303agr_t *ctx )
{
    volatile int16_t  value;
    float  ret_value;
    uint8_t buff[2];
    float sensitivity = 1.5;
    ctx->slave_address = 0x1E;

    buff[0] = lsm303agr_read_reg ( ctx, 0x6C );
    buff[1] = lsm303agr_read_reg ( ctx, 0x6D );

    value = (int16_t)(((buff[1] & 0xff) << 8) | (buff[0] & 0xff));
    
    
    ret_value = (float) ((int32_t)value) * sensitivity;

    return ret_value;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

uint8_t lsm303agr_read_reg ( lsm303agr_t *ctx, uint8_t reg)
{
    uint8_t rx_buf;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, &rx_buf, 1 ); 

    return rx_buf;
}

void lsm303agr_write_reg ( lsm303agr_t *ctx, uint8_t reg, uint8_t wr_reg_value)
{
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ] = reg; 
    tx_buf[ 1 ] = wr_reg_value;
    
    i2c_master_write( &ctx->i2c, tx_buf, 2 ); 
}

void lsm303agr_magnetometer_init ( lsm303agr_t *ctx )
{
    ctx->slave_address = 0x1E;
    lsm303agr_write_reg( ctx, 0x60, 0x00);;
}

void lsm303agr_accelerometer_init ( lsm303agr_t *ctx )
{
    ctx->slave_address = 0x19;
    lsm303agr_write_reg ( ctx, 0x20, 0x57);
}

// ------------------------------------------------------------------------- END

