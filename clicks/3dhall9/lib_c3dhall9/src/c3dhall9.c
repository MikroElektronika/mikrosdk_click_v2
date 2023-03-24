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
 * @file c3dhall9.c
 * @brief 3D Hall 9 Click Driver.
 */

#include "c3dhall9.h"
#include "math.h"

void c3dhall9_cfg_setup ( c3dhall9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C3DHALL9_SET_DEV_ADDR;
}

err_t c3dhall9_init ( c3dhall9_t *ctx, c3dhall9_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t c3dhall9_default_cfg ( c3dhall9_t *ctx ) 
{
    err_t error_flag = C3DHALL9_OK;
    
    c3dhall9_enable_chip ( ctx );
    Delay_1sec ( );
    
    error_flag |= c3dhall9_write_register ( ctx, C3DHALL9_REG_EEPROM_02, C3DHALL9_EEPROM_02_ENABLE_X | 
                                                                         C3DHALL9_EEPROM_02_ENABLE_Y | 
                                                                         C3DHALL9_EEPROM_02_ENABLE_Z );
    
    error_flag |= c3dhall9_write_register ( ctx, C3DHALL9_REG_VOLATILE_27, C3DHALL9_VOLATILE_27_ACTIVE_MODE | 
                                                                           C3DHALL9_VOLATILE_27_I2C_SINGLE );
    
    return error_flag;
}

err_t c3dhall9_write_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t tx_buf[ 5 ] = { 0 };

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    tx_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    tx_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );

    return i2c_master_write( &ctx->i2c, tx_buf, 5 );
}

err_t c3dhall9_read_register ( c3dhall9_t *ctx, uint8_t reg, uint32_t *data_out )
{
    uint8_t rx_buf[ 4 ] = { 0 };
    if ( I2C_MASTER_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 4 ) )
    {
        return I2C_MASTER_ERROR;
    }
    
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 2 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 3 ];
    
    return C3DHALL9_OK;
}

void c3dhall9_enable_chip ( c3dhall9_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void c3dhall9_disable_chip ( c3dhall9_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t c3dhall9_get_int_pin ( c3dhall9_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t c3dhall9_read_data ( c3dhall9_t *ctx, c3dhall9_data_t *data_out )
{
    uint32_t reg_data = 0;
    int16_t raw_x = 0, raw_y = 0, raw_z = 0, raw_temp = 0;
    
    if ( ( C3DHALL9_OK == c3dhall9_read_register ( ctx, C3DHALL9_REG_VOLATILE_28, &reg_data ) ) && 
         ( reg_data & C3DHALL9_DATA_READY_BIT ) )
    {
        raw_x = ( reg_data >> 20 ) & 0x0FF0;
        raw_y = ( reg_data >> 12 ) & 0x0FF0;
        raw_z = ( reg_data >> 4 ) & 0x0FF0;
        raw_temp = ( reg_data & 0x3F ) << 6;
        if ( C3DHALL9_OK == c3dhall9_read_register ( ctx, C3DHALL9_REG_VOLATILE_29, &reg_data ) )
        {
            raw_x |= ( ( reg_data >> 16 ) & 0x0F );
            raw_y |= ( ( reg_data >> 12 ) & 0x0F );
            raw_z |= ( ( reg_data >> 8 ) & 0x0F );
            raw_x = ( raw_x ^ C3DHALL9_SIGN_BIT ) - C3DHALL9_SIGN_BIT;
            raw_y = ( raw_y ^ C3DHALL9_SIGN_BIT ) - C3DHALL9_SIGN_BIT;
            raw_z = ( raw_z ^ C3DHALL9_SIGN_BIT ) - C3DHALL9_SIGN_BIT;
            
            data_out->x_axis = ( float ) raw_x / C3DHALL9_GAUSS_RESOLUTION;
            data_out->y_axis = ( float ) raw_y / C3DHALL9_GAUSS_RESOLUTION;
            data_out->z_axis = ( float ) raw_z / C3DHALL9_GAUSS_RESOLUTION;
            
            // Convert the X, Y and Z values into radians
            float x_rad = ( float ) raw_x / C3DHALL9_12BIT_RESOLUTION * TWO_PI;
            float y_rad = ( float ) raw_y / C3DHALL9_12BIT_RESOLUTION * TWO_PI;
            float z_rad = ( float ) raw_z / C3DHALL9_12BIT_RESOLUTION * TWO_PI;
            
            data_out->angle_xy = ( ( y_rad != 0 ) ? atan2( x_rad, y_rad ) : 0 ) * C3DHALL9_HALF_CICRLE_DEGREES / PI;
            data_out->angle_xz = ( ( z_rad != 0 ) ? atan2( x_rad, z_rad ) : 0 )  * C3DHALL9_HALF_CICRLE_DEGREES / PI;
            data_out->angle_yz = ( ( z_rad != 0 ) ? atan2( y_rad, z_rad ) : 0 ) * C3DHALL9_HALF_CICRLE_DEGREES / PI;
            
            raw_temp |= ( reg_data & 0x3F );
            data_out->temperature = ( float ) C3DHALL9_TEMPERATURE_MULTIPLIER * 
                                    ( raw_temp - C3DHALL9_TEMPERATURE_SUBTRACTOR ) / C3DHALL9_12BIT_RESOLUTION;
            return C3DHALL9_OK;
        }
    }
    return C3DHALL9_ERROR;
}

// ------------------------------------------------------------------------- END
