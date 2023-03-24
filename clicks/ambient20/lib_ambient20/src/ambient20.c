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
 * @file ambient20.c
 * @brief Ambient 20 Click Driver.
 */

#include "ambient20.h"

void ambient20_cfg_setup ( ambient20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT20_DEVICE_ADDRESS;
}

err_t ambient20_init ( ambient20_t *ctx, ambient20_cfg_t *cfg ) 
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

err_t ambient20_default_cfg ( ambient20_t *ctx ) 
{
    err_t error_flag = AMBIENT20_OK;
    
    error_flag = ambient20_disable_wait_mode( ctx );
    error_flag |= ambient20_set_meas_mode( ctx, AMBIENT20_100mS_MODE );
    error_flag |= ambient20_set_gain( ctx, AMBIENT20_GAIN_X1, AMBIENT20_GAIN_X1 );
    error_flag |= ambient20_enable_meas( ctx );
    
    return error_flag;
}

err_t ambient20_generic_write ( ambient20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ambient20_generic_read ( ambient20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ambient20_sw_reset ( ambient20_t *ctx )
{
    uint8_t data_in = AMBIENT20_ENABLE << 7;
    
    return ambient20_generic_write( ctx, AMBIENT20_SYSTEM_CONTROL_REG, &data_in, 1 );
}

err_t ambient20_get_manufacturer_id ( ambient20_t *ctx, uint8_t *manufacturer_id )
{
    return ambient20_generic_read( ctx, AMBIENT20_MANUFACTURER_ID_REG, manufacturer_id, 1 );
}

err_t ambient20_get_part_id ( ambient20_t *ctx, uint8_t *part_id )
{
    err_t error_flag = AMBIENT20_OK;
    uint8_t read_data;
     
    error_flag = ambient20_generic_read( ctx, AMBIENT20_SYSTEM_CONTROL_REG, &read_data, 1 );
    read_data &= AMBIENT20_PART_ID_MASK;
    *part_id = read_data;
    
    return error_flag;
}

err_t ambient20_enable_wait_mode ( ambient20_t *ctx )
{
    uint8_t data_in = AMBIENT20_ENABLE << 2;
    
    return ambient20_generic_write( ctx, AMBIENT20_MODE_CONTROL1_REG, &data_in, 1 );
}

err_t ambient20_disable_wait_mode ( ambient20_t *ctx )
{
    err_t error_flag = AMBIENT20_OK;
    uint8_t data_in;
    
    error_flag = ambient20_generic_read( ctx, AMBIENT20_MODE_CONTROL1_REG, &data_in, 1 );
    
    data_in &= ~(AMBIENT20_ENABLE << 2);
    
    error_flag |= ambient20_generic_write( ctx, AMBIENT20_MODE_CONTROL1_REG, &data_in, 1 );
    
    return error_flag;
}

err_t ambient20_set_meas_mode ( ambient20_t *ctx, uint8_t meas_mode )
{
    err_t error_flag = AMBIENT20_OK;
    uint8_t data_in;
    
    error_flag = ambient20_generic_read( ctx, AMBIENT20_MODE_CONTROL1_REG, &data_in, 1 );
    
    data_in &= ~AMBIENT20_ENABLE;
    data_in |= meas_mode;
    
    error_flag |= ambient20_generic_write( ctx, AMBIENT20_MODE_CONTROL1_REG, &data_in, 1 );
    
    return error_flag;
}

err_t ambient20_set_gain ( ambient20_t *ctx, uint8_t data0_gain, uint8_t data1_gain )
{
    uint8_t data_in;
    
    data_in = data0_gain;
    data_in <<= 4;
    data_in |= data1_gain;
    
    ctx->data0_gain = data0_gain;
    ctx->data1_gain = data1_gain;
    
    return ambient20_generic_write( ctx, AMBIENT20_MODE_CONTROL2_REG, &data_in, 1 );
}

err_t ambient20_enable_meas ( ambient20_t *ctx )
{
    err_t error_flag = AMBIENT20_OK;
    uint8_t data_in;
    
    error_flag = ambient20_generic_read( ctx, AMBIENT20_MODE_CONTROL3_REG, &data_in, 1 );
    
    data_in |= AMBIENT20_ENABLE; 
    
    error_flag |= ambient20_generic_write( ctx, AMBIENT20_MODE_CONTROL3_REG, &data_in, 1 );
    
    return error_flag;
}

err_t ambient20_disable_meas ( ambient20_t *ctx )
{
    err_t error_flag = AMBIENT20_OK;
    uint8_t data_in;
    
    error_flag = ambient20_generic_read( ctx, AMBIENT20_MODE_CONTROL3_REG, &data_in, 1 );
    
    data_in &= ~AMBIENT20_ENABLE;
    
    error_flag |= ambient20_generic_write( ctx, AMBIENT20_MODE_CONTROL3_REG, &data_in, 1 );
    
    return error_flag;
}

err_t ambient20_check_valid ( ambient20_t *ctx )
{
    err_t error_flag = AMBIENT20_ERROR;
    uint8_t valid_data;
    
    ambient20_generic_read( ctx, AMBIENT20_MODE_CONTROL3_REG, &valid_data, 1 );
    if ( valid_data & AMBIENT20_VALID_MASK )
    {
        error_flag = AMBIENT20_OK;
    }
    
    return error_flag;
}

err_t ambient20_read_data0 ( ambient20_t *ctx, uint16_t *data0_out )
{
    err_t error_flag = AMBIENT20_OK;
    uint8_t read_data;
    uint16_t data_out;
    
    error_flag = ambient20_generic_read( ctx, AMBIENT20_DATA0_MSB_REG, &read_data, 1 );

    data_out = read_data;
    data_out <<= 8;
    
    error_flag |= ambient20_generic_read( ctx, AMBIENT20_DATA0_LSB_REG, &read_data, 1 );
    
    data_out |= read_data;
    *data0_out = data_out;
    
    return error_flag; 
}

err_t ambient20_read_data1 ( ambient20_t *ctx, uint16_t *data1_out )
{
    err_t error_flag = AMBIENT20_OK;
    uint8_t read_data;
    uint16_t data_out;
    
    error_flag = ambient20_generic_read( ctx, AMBIENT20_DATA1_MSB_REG, &read_data, 1 );

    data_out = read_data;
    data_out <<= 8;
    
    error_flag |= ambient20_generic_read( ctx, AMBIENT20_DATA1_LSB_REG, &read_data, 1 );
    
    data_out |= read_data;
    *data1_out = data_out;
    
    return error_flag; 
}

err_t ambient20_get_data_lux ( ambient20_t *ctx, float *data0_out ,float *data1_out )
{
    err_t error_flag = AMBIENT20_OK;
    uint16_t data0, data1;
    float data0_lx, data1_lx;
    
    error_flag = ambient20_read_data0( ctx, &data0 );
    switch ( ctx->data0_gain )
    {
        case AMBIENT20_GAIN_X1:
        {
            data0_lx = ( float )data0 * AMBIENT20_DATA0_CONVERSION_COEF;
            break;
        }
        case AMBIENT20_GAIN_X32:
        {
            data0_lx = ( ( ( float ) data0 / 32 ) * AMBIENT20_DATA0_CONVERSION_COEF);
            break;
        }
        case AMBIENT20_GAIN_X256:
        {
            data0_lx = ( ( ( float ) data0 / 256 ) * AMBIENT20_DATA0_CONVERSION_COEF);
            break;
        }
        default:
        {
            data0_lx = ( float )data0 * AMBIENT20_DATA0_CONVERSION_COEF;
            break;
        }
    }
    
    error_flag |= ambient20_read_data1( ctx, &data1 );
    switch ( ctx->data1_gain )
    {
        case AMBIENT20_GAIN_X1:
        {
            data1_lx = ( float )data1 * AMBIENT20_DATA1_CONVERSION_COEF;
            break;
        }
        case AMBIENT20_GAIN_X32:
        {
            data1_lx = ( ( ( float ) data1 / 32 ) * AMBIENT20_DATA1_CONVERSION_COEF);
            break;
        }
        case AMBIENT20_GAIN_X256:
        {
            data1_lx = ( ( ( float ) data1 / 256 ) * AMBIENT20_DATA1_CONVERSION_COEF);
            break;
        }
        default:
        {
            data1_lx = ( float )data1 * AMBIENT20_DATA1_CONVERSION_COEF;
            break;
        }
    }
    
    *data0_out = data0_lx;
    *data1_out = data1_lx;
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
