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
 * @file magneto10.c
 * @brief Magneto 10 Click Driver.
 */

#include "magneto10.h"

void magneto10_cfg_setup ( magneto10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = MAGNETO10_SET_DEV_ADDR;
}

err_t magneto10_init ( magneto10_t *ctx, magneto10_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t magneto10_default_cfg ( magneto10_t *ctx ) 
{
    if ( MAGNETO10_ERROR == magneto10_check_communication ( ctx ) )
    {
        return MAGNETO10_ERROR;
    }
    err_t error_flag = magneto10_reset ( ctx );
    error_flag |= magneto10_set_operating_mode ( ctx, MAGNETO10_MODE_CONT_MEAS_500HZ );
    error_flag |= magneto10_enable_temperature_sensor ( ctx, MAGNETO10_TEMPERATURE_ENABLE );
    return error_flag;
}

err_t magneto10_mem_write_single ( magneto10_t *ctx, uint8_t reg, uint8_t tx_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t magneto10_mem_write_multiple ( magneto10_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ MAGNETO10_REG_T_EN_DIG_FILT_Z + 2 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t magneto10_mem_direct_read ( magneto10_t *ctx, uint8_t *rx_buf, uint8_t rx_len )
{
    return i2c_master_read( &ctx->i2c, rx_buf, rx_len );
}

err_t magneto10_mem_read ( magneto10_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t magneto10_check_communication ( magneto10_t *ctx ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    
    if ( MAGNETO10_OK == magneto10_mem_read ( ctx, MAGNETO10_REG_CID, rx_buf, 2 ) )
    {
        if ( ( MAGNETO10_COMPANY_ID == rx_buf[ 0 ] ) && 
             ( MAGNETO10_DEVICE_ID == rx_buf[ 1 ] ) )
        {
            return MAGNETO10_OK;
        }
    }
    return MAGNETO10_ERROR;
}

err_t magneto10_check_data_ready ( magneto10_t *ctx ) 
{
    uint8_t status = 0;
    if ( MAGNETO10_OK == magneto10_mem_read ( ctx, MAGNETO10_REG_STAT1, &status, 1 ) )
    {
        return status & MAGNETO10_STAT1_DRDY;
    }
    return MAGNETO10_ERROR;
}

err_t magneto10_get_magnetic_flux ( magneto10_t *ctx, float *x_axis, float *y_axis, float *z_axis ) 
{
    uint8_t rx_buf[ 6 ] = { 0 };
    
    while ( MAGNETO10_STAT1_DRDY != magneto10_check_data_ready ( ctx ) );
    
    if ( MAGNETO10_OK == magneto10_mem_read ( ctx, MAGNETO10_REG_X_LSB, rx_buf, 6 ) )
    {
        *x_axis = ( float )( ( ( int16_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 0 ] ) * MAGNETO10_MAG_FLUX_RESOLUTION;
        *y_axis = ( float )( ( ( int16_t ) rx_buf[ 3 ] << 8 ) | rx_buf[ 2 ] ) * MAGNETO10_MAG_FLUX_RESOLUTION;
        *z_axis = ( float )( ( ( int16_t ) rx_buf[ 5 ] << 8 ) | rx_buf[ 4 ] ) * MAGNETO10_MAG_FLUX_RESOLUTION;
        return MAGNETO10_OK;
    }
    return MAGNETO10_ERROR;
}

err_t magneto10_get_temperature ( magneto10_t *ctx, float *temperature ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    
    if ( MAGNETO10_OK == magneto10_mem_read ( ctx, MAGNETO10_REG_T_LSB, rx_buf, 2 ) )
    {
        *temperature = ( float )( ( ( int16_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 0 ] ) / MAGNETO10_TEMPERATURE_RES;
        return MAGNETO10_OK;
    }
    return MAGNETO10_ERROR;
}

err_t magneto10_reset ( magneto10_t *ctx ) 
{
    err_t error_flag = magneto10_mem_write_single ( ctx, MAGNETO10_REG_RST, MAGNETO10_RESET );
    uint8_t status = 0;
    do
    {
        Delay_1ms( );
        error_flag |= magneto10_mem_read ( ctx, MAGNETO10_REG_STAT1, &status, 1 );
    } while ( MAGNETO10_STAT1_RT != ( status & MAGNETO10_STAT1_RT ) );
    
    return error_flag;
}

err_t magneto10_set_operating_mode ( magneto10_t *ctx, uint8_t mode ) 
{
    if ( mode > MAGNETO10_MODE_POWER_DOWN )
    {
        return MAGNETO10_ERROR;
    }
    return magneto10_mem_write_single ( ctx, MAGNETO10_REG_CTRL, mode );
}

err_t magneto10_enable_temperature_sensor ( magneto10_t *ctx, uint8_t enable ) 
{
    uint8_t rx_data;
    
    err_t error_flag = magneto10_mem_read ( ctx, MAGNETO10_REG_T_EN_DIG_FILT_Z, &rx_data, 1 );
    
    if ( MAGNETO10_TEMPERATURE_ENABLE == enable )
    {
        if ( MAGNETO10_TEMPERATURE_EN_MASK != ( MAGNETO10_TEMPERATURE_EN_MASK & rx_data ) )
        {
            rx_data |= MAGNETO10_TEMPERATURE_EN_MASK;
            error_flag != magneto10_mem_write_single ( ctx, MAGNETO10_REG_T_EN_DIG_FILT_Z, rx_data );
        }
    }
    else
    {
        if ( MAGNETO10_TEMPERATURE_EN_MASK == ( MAGNETO10_TEMPERATURE_EN_MASK & rx_data ) )
        {
            rx_data &= ~MAGNETO10_TEMPERATURE_EN_MASK;
            error_flag != magneto10_mem_write_single ( ctx, MAGNETO10_REG_T_EN_DIG_FILT_Z, rx_data );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
