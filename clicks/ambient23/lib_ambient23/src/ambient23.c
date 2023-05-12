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
 * @file ambient23.c
 * @brief Ambient 23 Click Driver.
 */

#include "ambient23.h"

void ambient23_cfg_setup ( ambient23_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT23_DEVICE_ADDRESS;
}

err_t ambient23_init ( ambient23_t *ctx, ambient23_cfg_t *cfg ) 
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

err_t ambient23_default_cfg ( ambient23_t *ctx ) 
{
    err_t error_flag = AMBIENT23_OK;
    uint16_t tmp_data = 0;
    
    error_flag = ambient23_reg_write( ctx, AMBIENT23_REG_CONFIG, AMBIENT23_GAIN_1 | 
                                           AMBIENT23_DATA_GAIN_1 | AMBIENT23_SDO_SHUTDOWN_OFF | 
                                           AMBIENT23_SHUTDOWN_OFF | AMBIENT23_TRIGGER_OFF | 
                                           AMBIENT23_INTEGRATION_50_MS );

    return error_flag;
}

err_t ambient23_generic_write ( ambient23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ambient23_generic_read ( ambient23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ambient23_reg_write ( ambient23_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tmp_data[ 2 ] = { 0 };
    
    tmp_data[ 0 ] = ( uint8_t ) data_in;
    tmp_data[ 1 ] = ( uint8_t ) ( data_in >> 8 );
    
    return ambient23_generic_write( ctx, reg, tmp_data, 2 );
}

err_t ambient23_reg_read ( ambient23_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = AMBIENT23_OK;
    uint8_t tmp_data[ 2 ] = { 0 };

    error_flag = ambient23_generic_read( ctx, reg, tmp_data, 2 );
    
    *data_out = ( ( ( uint16_t )tmp_data[ 1 ] << 8 ) ) | tmp_data[ 0 ];;
    
    return error_flag;
}

err_t ambient23_calculate_res ( ambient23_t *ctx, float *conversion_mul )
{
    err_t error_flag = AMBIENT23_OK;
    uint16_t tmp_data = 0;
    uint8_t gain_lvl = 0;       
    uint8_t it_val = 0;
    uint8_t data_gain = 0;
    
    error_flag |= ambient23_reg_read( ctx, AMBIENT23_REG_CONFIG, &tmp_data );
    
    if ( AMBIENT23_GAIN_1 == ( tmp_data & AMBIENT23_GAIN_MSK ) )
    {
        gain_lvl = 1;
    }
    else if ( AMBIENT23_GAIN_2 == ( tmp_data & AMBIENT23_GAIN_MSK ) )
    {
        gain_lvl = 2;
    }
    else if ( AMBIENT23_GAIN_4 == ( tmp_data & AMBIENT23_GAIN_MSK ) )
    {
        gain_lvl = 4;
    }
    else
    {
        error_flag |= AMBIENT23_ERROR;
    }
    
    if ( AMBIENT23_DATA_GAIN_2 == ( tmp_data & AMBIENT23_DATA_GAIN_MASK ) )
    {
        data_gain = 2;
    }
    else
    {
        data_gain = 1;
    }
    
    if ( AMBIENT23_INTEGRATION_50_MS == ( tmp_data & AMBIENT23_INTEGRATION_TIME_MSK ) )
    {
        it_val = 1;
    }
    else if ( AMBIENT23_INTEGRATION_100_MS == ( tmp_data & AMBIENT23_INTEGRATION_TIME_MSK ) )
    {
        it_val = 2;
    }
    else if ( AMBIENT23_INTEGRATION_200_MS == ( tmp_data & AMBIENT23_INTEGRATION_TIME_MSK ) )
    {
        it_val = 4;
    }
    else if ( AMBIENT23_INTEGRATION_400_MS == ( tmp_data & AMBIENT23_INTEGRATION_TIME_MSK ) )
    {
        it_val = 8;
    }
    else if ( AMBIENT23_INTEGRATION_800_MS == ( tmp_data & AMBIENT23_INTEGRATION_TIME_MSK ) )
    {
        it_val = 16;
    }
    else
    {
        error_flag |= AMBIENT23_ERROR;
    }
    
    *conversion_mul = AMBIENT23_TYPICAL_RESOLUTION / gain_lvl / data_gain / it_val;
    
    return error_flag;
}

err_t ambient23_read_light_data ( ambient23_t *ctx, float *light_data )
{
    err_t error_flag = AMBIENT23_OK;
    float conversion_mul;
    uint16_t tmp_data; 
    
    error_flag |= ambient23_calculate_res( ctx, &conversion_mul );
    
    error_flag |= ambient23_reg_read( ctx, AMBIENT23_REG_ALS_DATA, &tmp_data );
    
    *light_data = tmp_data * conversion_mul;
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
