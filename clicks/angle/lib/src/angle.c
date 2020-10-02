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

#include "angle.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void angle_cfg_setup ( angle_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x0C;
}

ANGLE_RETVAL angle_init ( angle_t *ctx, angle_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ANGLE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return ANGLE_OK;
}

void angle_default_cfg ( angle_t *ctx )
{
    angle_set_config( ctx, ANGLE_CDS_NO_CHANGLE | 
                           ANGLE_HDR_RESET_1 | 
                           ANGLE_SFR_RESET_1 | 
                           ANGLE_CSR_STA_1 | 
                           ANGLE_CXE_1 | 
                           ANGLE_CER_1 );
}

void angle_generic_write ( angle_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void angle_generic_read ( angle_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t angle_get_angle ( angle_t *ctx )
{
    uint8_t read_reg[ 2 ];
    uint16_t angle;
    uint16_t angle_val;

    angle_generic_read( ctx, 0x20, read_reg, 2 );

    angle = read_reg[ 0 ];
    angle <<= 8;
    angle |= read_reg[ 1 ];
    angle &= 0x0FFF;
    angle_val = ( uint16_t )( angle * (360 / 4096.0));

    return angle_val;
}

uint16_t angle_get_temperature ( angle_t *ctx )
{
    uint8_t read_reg[ 2 ];
    uint16_t temp;
    uint16_t temp_val;

    angle_generic_read( ctx, 0x28, read_reg, 2 );

    temp = read_reg[ 0 ];
    temp <<= 8;
    temp |= read_reg[ 1 ];
    temp &= 0x0FFF;
    temp_val = ( uint16_t )temp / 8 - 273;

    return temp_val;
}

uint16_t angle_get_magnetics ( angle_t *ctx )
{
    uint8_t read_reg[ 2 ];
    uint16_t magnet;
    uint16_t magnet_val;

    angle_generic_read( ctx, 0x2A, read_reg, 2 );

    magnet = read_reg[ 0 ];
    magnet <<= 8;
    magnet |= read_reg[ 1 ];
    magnet &= 0x0FFF;
    magnet_val = ( uint16_t )magnet;
    
    return magnet_val;
}

uint16_t angle_get_status( angle_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 2 ];
    uint16_t status;

    angle_generic_read( ctx, reg, read_reg, 2 );

    status = read_reg[ 0 ];
    status <<= 8;
    status |= read_reg[ 1 ];
    status &= 0x0FFF;

    return status;
}

void angle_set_config ( angle_t *ctx, uint16_t set_value )
{
    uint8_t write_reg[ 2 ];
  
    write_reg[ 0 ] = set_value >> 8;
    write_reg[ 1 ] = set_value & 0x00FF;
    
    angle_generic_write( ctx, 0x1E, write_reg, 2 );
}

// ------------------------------------------------------------------------- END

