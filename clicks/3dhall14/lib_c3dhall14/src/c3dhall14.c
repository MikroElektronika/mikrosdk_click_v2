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
 * @file c3dhall14.c
 * @brief 3D Hall 14 Click Driver.
 */

#include "c3dhall14.h"

void c3dhall14_cfg_setup ( c3dhall14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C3DHALL14_DEVICE_ADDRESS;
}

err_t c3dhall14_init ( c3dhall14_t *ctx, c3dhall14_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t c3dhall14_default_cfg ( c3dhall14_t *ctx ) 
{
    err_t error_flag = C3DHALL14_OK;
    if ( C3DHALL14_ERROR == c3dhall14_check_communication ( ctx ) )
    {
        return C3DHALL14_ERROR;
    }
    error_flag |= c3dhall14_reset ( ctx );
    error_flag |= c3dhall14_set_operating_mode ( ctx, C3DHALL14_MODE_CONT_MEAS_5HZ );
    error_flag |= c3dhall14_set_range ( ctx, C3DHALL14_RANGE_HIGH_LOW_CURRENT );
    error_flag |= c3dhall14_enable_drdy_int ( ctx, C3DHALL14_DRDY_INT_ENABLE );
    error_flag |= c3dhall14_enable_temp_sensor ( ctx, C3DHALL14_TEMPERATURE_ENABLE );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    return error_flag;
}

err_t c3dhall14_mem_write_single ( c3dhall14_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t c3dhall14_mem_write_multi ( c3dhall14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t c3dhall14_mem_direct_read ( c3dhall14_t *ctx, uint8_t *data_out, uint8_t len )
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

err_t c3dhall14_mem_read ( c3dhall14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t c3dhall14_check_communication ( c3dhall14_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( C3DHALL14_OK == c3dhall14_mem_read ( ctx, C3DHALL14_REG_CID, data_buf, 2 ) )
    {
        if ( ( C3DHALL14_COMPANY_ID == data_buf[ 0 ] ) && 
             ( C3DHALL14_DEVICE_ID == data_buf[ 1 ] ) )
        {
            return C3DHALL14_OK;
        }
    }
    return C3DHALL14_ERROR;
}

uint8_t c3dhall14_get_int_pin ( c3dhall14_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t c3dhall14_check_data_ready ( c3dhall14_t *ctx )
{
    uint8_t status = 0;
    if ( C3DHALL14_DRDY_INT_ENABLE == ctx->drdy_int_out )
    {
        return !c3dhall14_get_int_pin ( ctx );
    }

    if ( C3DHALL14_OK == c3dhall14_mem_read ( ctx, C3DHALL14_REG_STAT1, &status, 1 ) )
    {
        return status & C3DHALL14_STAT1_DRDY;
    }
    return C3DHALL14_ERROR;
}

err_t c3dhall14_get_magnetic_flux ( c3dhall14_t *ctx, float *x_axis, float *y_axis, float *z_axis )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    
    while ( C3DHALL14_STAT1_DRDY != c3dhall14_check_data_ready ( ctx ) );
    
    if ( C3DHALL14_OK == c3dhall14_mem_read ( ctx, C3DHALL14_REG_X_LSB, data_buf, 6 ) )
    {
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 1 ] );
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        *x_axis = ( float ) raw_data * ctx->mag_flux_res;
        
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 3 ] );
        raw_data <<= 8;
        raw_data |= data_buf[ 2 ];
        *y_axis = ( float ) raw_data * ctx->mag_flux_res;
        
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 5 ] );
        raw_data <<= 8;
        raw_data |= data_buf[ 4 ];
        *z_axis = ( float ) raw_data * ctx->mag_flux_res;
        return C3DHALL14_OK;
    }
    return C3DHALL14_ERROR;
}

err_t c3dhall14_get_temperature ( c3dhall14_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( C3DHALL14_OK == c3dhall14_mem_read ( ctx, C3DHALL14_REG_T_LSB, data_buf, 2 ) )
    {
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 1 ] );
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        *temperature = ( float ) raw_data / C3DHALL14_TEMPERATURE_RES;
        return C3DHALL14_OK;
    }
    return C3DHALL14_ERROR;
}

err_t c3dhall14_reset ( c3dhall14_t *ctx )
{
    err_t error_flag = c3dhall14_mem_write_single ( ctx, C3DHALL14_REG_RST, C3DHALL14_RESET );
    uint8_t status = 0;
    do
    {
        Delay_1ms( );
        error_flag |= c3dhall14_mem_read ( ctx, C3DHALL14_REG_STAT1, &status, 1 );
    } 
    while ( C3DHALL14_STAT1_RT != ( status & C3DHALL14_STAT1_RT ) );
    
    return error_flag;
}

err_t c3dhall14_set_operating_mode ( c3dhall14_t *ctx, uint8_t mode )
{
    if ( mode > C3DHALL14_MODE_POWER_DOWN_2 )
    {
        return C3DHALL14_ERROR;
    }
    uint8_t reg_data = 0;
    err_t error_flag = c3dhall14_mem_read ( ctx, C3DHALL14_REG_CTRL1, &reg_data, 1 );
    if ( mode != ( C3DHALL14_MODE_MASK & reg_data ) )
    {
        reg_data &= ~C3DHALL14_MODE_MASK;
        reg_data |= mode;
        error_flag |= c3dhall14_mem_write_single ( ctx, C3DHALL14_REG_CTRL1, reg_data );
    }
    return error_flag;
}

err_t c3dhall14_set_range ( c3dhall14_t *ctx, uint8_t range )
{
    if ( range > C3DHALL14_RANGE_LOW_LOW_NOISE )
    {
        return C3DHALL14_ERROR;
    }
    uint8_t reg_data = 0;
    err_t error_flag = c3dhall14_mem_read ( ctx, C3DHALL14_REG_CTRL2, &reg_data, 1 );
    if ( range != ( ( C3DHALL14_RANGE_MASK & reg_data ) >> C3DHALL14_RANGE_SHIFT ) )
    {
        reg_data &= ~C3DHALL14_RANGE_MASK;
        reg_data |= ( range << C3DHALL14_RANGE_SHIFT );
        error_flag |= c3dhall14_mem_write_single ( ctx, C3DHALL14_REG_CTRL2, reg_data );
    }
    if ( C3DHALL14_RANGE_LOW_LOW_NOISE == range )
    {
        ctx->mag_flux_res = C3DHALL14_MAG_FLUX_RES_L;
    }
    else
    {
        ctx->mag_flux_res = C3DHALL14_MAG_FLUX_RES_H;
    }
    return error_flag;
}

err_t c3dhall14_enable_temp_sensor ( c3dhall14_t *ctx, uint8_t enable )
{
    uint8_t reg_data = 0;
    err_t error_flag = c3dhall14_mem_read ( ctx, C3DHALL14_REG_CTRL4, &reg_data, 1 );
    if ( C3DHALL14_TEMPERATURE_ENABLE == enable )
    {
        if ( C3DHALL14_TEMPERATURE_EN_MASK != ( C3DHALL14_TEMPERATURE_EN_MASK & reg_data ) )
        {
            reg_data |= C3DHALL14_TEMPERATURE_EN_MASK;
            error_flag |= c3dhall14_mem_write_single ( ctx, C3DHALL14_REG_CTRL4, reg_data );
        }
    }
    else
    {
        if ( C3DHALL14_TEMPERATURE_EN_MASK == ( C3DHALL14_TEMPERATURE_EN_MASK & reg_data ) )
        {
            reg_data &= ~C3DHALL14_TEMPERATURE_EN_MASK;
            error_flag |= c3dhall14_mem_write_single ( ctx, C3DHALL14_REG_CTRL4, reg_data );
        }
    }
    return error_flag;
}

err_t c3dhall14_enable_drdy_int ( c3dhall14_t *ctx, uint8_t enable )
{
    uint8_t reg_data = 0;
    err_t error_flag = c3dhall14_mem_read ( ctx, C3DHALL14_REG_CTRL4, &reg_data, 1 );
    if ( C3DHALL14_DRDY_INT_ENABLE == enable )
    {
        if ( C3DHALL14_DRDY_INT_EN_MASK != ( C3DHALL14_DRDY_INT_EN_MASK & reg_data ) )
        {
            reg_data |= C3DHALL14_DRDY_INT_EN_MASK;
            error_flag |= c3dhall14_mem_write_single ( ctx, C3DHALL14_REG_CTRL4, reg_data );
        }
    }
    else
    {
        if ( C3DHALL14_DRDY_INT_EN_MASK == ( C3DHALL14_DRDY_INT_EN_MASK & reg_data ) )
        {
            reg_data &= ~C3DHALL14_DRDY_INT_EN_MASK;
            error_flag |= c3dhall14_mem_write_single ( ctx, C3DHALL14_REG_CTRL4, reg_data );
        }
    }
    ctx->drdy_int_out = enable;
    return error_flag;
}

// ------------------------------------------------------------------------- END
