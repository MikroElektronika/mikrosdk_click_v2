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
 * @file ambient24.c
 * @brief Ambient 24 Click Driver.
 */

#include "ambient24.h"

void ambient24_cfg_setup ( ambient24_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT24_DEVICE_ADDRESS;
}

err_t ambient24_init ( ambient24_t *ctx, ambient24_cfg_t *cfg ) 
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

err_t ambient24_default_cfg ( ambient24_t *ctx ) 
{
    err_t error_flag = AMBIENT24_OK;
    if ( AMBIENT24_ERROR == ambient24_check_communication ( ctx ) )
    {
        return AMBIENT24_ERROR;
    }
    error_flag |= ambient24_set_als_config ( ctx, AMBIENT24_ALS_CONFIG_DEFAULT );
    error_flag |= ambient24_set_als_threshold ( ctx, AMBIENT24_THRESHOLD_LOW_DEFAULT, AMBIENT24_THRESHOLD_HIGH_DEFAULT );
    Delay_100ms( );
    return error_flag;
}

err_t ambient24_generic_write ( ambient24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ambient24_generic_read ( ambient24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ambient24_check_communication ( ambient24_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( AMBIENT24_OK == ambient24_generic_read ( ctx, AMBIENT24_REG_VEML4031X00_ID_L, data_buf, 2 ) )
    {
        if ( AMBIENT24_DEVICE_ID == ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] ) )
        {
            return AMBIENT24_OK;
        }
    }
    return AMBIENT24_ERROR;
}

err_t ambient24_set_als_config ( ambient24_t *ctx, uint16_t config )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( config >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( config & 0xFF );
    if ( AMBIENT24_OK == ambient24_generic_write( ctx, AMBIENT24_REG_ALS_CONF, data_buf, 2 ) )
    {
        ctx->als_res = AMBIENT24_ALS_MIN_RES;

        if ( AMBIENT24_ALS_CONFIG_ALS_PDDIV_1_4_PD == ( config & AMBIENT24_ALS_CONFIG_ALS_PDDIV_MASK ) )
        {
            ctx->als_res *= 4;
        }

        if ( AMBIENT24_ALS_CONFIG_ALS_GAIN_X1 == ( config & AMBIENT24_ALS_CONFIG_ALS_GAIN_MASK ) )
        {
            ctx->als_res *= 2;
        }
        else if ( AMBIENT24_ALS_CONFIG_ALS_GAIN_X0_66 == ( config & AMBIENT24_ALS_CONFIG_ALS_GAIN_MASK ) )
        {
            ctx->als_res *= 3;
        }
        else if ( AMBIENT24_ALS_CONFIG_ALS_GAIN_X0_5 == ( config & AMBIENT24_ALS_CONFIG_ALS_GAIN_MASK ) )
        {
            ctx->als_res *= 4;
        }

        ctx->als_res *= ( 1 << ( ( AMBIENT24_ALS_CONFIG_ALS_IT_400_MS - ( config & AMBIENT24_ALS_CONFIG_ALS_IT_MASK ) ) >> 12 ) );
        
        return AMBIENT24_OK;
    }
    return AMBIENT24_ERROR;
}

err_t ambient24_get_als_config ( ambient24_t *ctx, uint16_t *config )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( AMBIENT24_OK == ambient24_generic_read( ctx, AMBIENT24_REG_ALS_CONF, data_buf, 2 ) )
    {
        if ( NULL != config )
        {
            *config = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        }
        return AMBIENT24_OK;
    }
    return AMBIENT24_ERROR;
}

err_t ambient24_set_als_threshold ( ambient24_t *ctx, uint16_t threshold_low, uint16_t threshold_high )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( threshold_high & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( threshold_high >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( threshold_low & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( threshold_low >> 8 ) & 0xFF );
    return ambient24_generic_write( ctx, AMBIENT24_REG_ALS_THDH_L, data_buf, 4 );
}

err_t ambient24_get_als_threshold ( ambient24_t *ctx, uint16_t *threshold_low, uint16_t *threshold_high )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( AMBIENT24_OK == ambient24_generic_read( ctx, AMBIENT24_REG_ALS_THDH_L, data_buf, 4 ) )
    {
        if ( NULL != threshold_high )
        {
            *threshold_high = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        if ( NULL != threshold_low )
        {
            *threshold_low = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        }
        return AMBIENT24_OK;
    }
    return AMBIENT24_ERROR;
}

err_t ambient24_get_int_flag ( ambient24_t *ctx, uint8_t *int_flag )
{
    return ambient24_generic_read( ctx, AMBIENT24_REG_INT_FLAG, int_flag, 1 );
}

err_t ambient24_get_raw_data ( ambient24_t *ctx, uint16_t *als_data, uint16_t *ir_data )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( AMBIENT24_OK == ambient24_generic_read( ctx, AMBIENT24_REG_ALS_DATA_L, data_buf, 4 ) )
    {
        if ( NULL != als_data )
        {
            *als_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        if ( NULL != ir_data )
        {
            *ir_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        }
        return AMBIENT24_OK;
    }
    return AMBIENT24_ERROR;
}

err_t ambient24_get_data ( ambient24_t *ctx, float *als_data, uint16_t *ir_data )
{
    uint16_t als_data_raw = 0;
    if ( AMBIENT24_OK == ambient24_get_raw_data( ctx, &als_data_raw, ir_data ) )
    {
        if ( NULL != als_data )
        {
            *als_data = als_data_raw * ctx->als_res;
        }
        return AMBIENT24_OK;
    }
    return AMBIENT24_ERROR;
}

// ------------------------------------------------------------------------- END
