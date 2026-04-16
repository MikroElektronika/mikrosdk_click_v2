/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file light6.c
 * @brief Light 6 Click Driver.
 */

#include "light6.h"

void light6_cfg_setup ( light6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LIGHT6_DEVICE_ADDRESS;
}

err_t light6_init ( light6_t *ctx, light6_cfg_t *cfg ) 
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

err_t light6_default_cfg ( light6_t *ctx ) 
{
    err_t error_flag = LIGHT6_OK;
    if ( LIGHT6_ERROR == light6_check_communication ( ctx ) )
    {
        return LIGHT6_ERROR;
    }
    error_flag |= light6_set_als_config ( ctx, LIGHT6_ALS_CONFIG_DEFAULT );
    error_flag |= light6_set_als_threshold ( ctx, LIGHT6_THRESHOLD_LOW_DEFAULT, LIGHT6_THRESHOLD_HIGH_DEFAULT );
    Delay_100ms( );
    return error_flag;
}

err_t light6_generic_write ( light6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t light6_generic_read ( light6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t light6_get_int_pin ( light6_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t light6_check_communication ( light6_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( LIGHT6_OK == light6_generic_read ( ctx, LIGHT6_REG_VEML6031X01_ID_L, data_buf, 2 ) )
    {
        if ( LIGHT6_DEVICE_ID == ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] ) )
        {
            return LIGHT6_OK;
        }
    }
    return LIGHT6_ERROR;
}

err_t light6_set_als_config ( light6_t *ctx, uint16_t config )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( config >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( config & 0xFF );
    if ( LIGHT6_OK == light6_generic_write( ctx, LIGHT6_REG_ALS_CONF, data_buf, 2 ) )
    {
        ctx->als_res = LIGHT6_ALS_MIN_RES;

        if ( LIGHT6_ALS_CONFIG_ALS_PDDIV_1_4_PD == ( config & LIGHT6_ALS_CONFIG_ALS_PDDIV_MASK ) )
        {
            ctx->als_res *= 4;
        }

        if ( LIGHT6_ALS_CONFIG_ALS_GAIN_X1 == ( config & LIGHT6_ALS_CONFIG_ALS_GAIN_MASK ) )
        {
            ctx->als_res *= 2;
        }
        else if ( LIGHT6_ALS_CONFIG_ALS_GAIN_X0_66 == ( config & LIGHT6_ALS_CONFIG_ALS_GAIN_MASK ) )
        {
            ctx->als_res *= 3;
        }
        else if ( LIGHT6_ALS_CONFIG_ALS_GAIN_X0_5 == ( config & LIGHT6_ALS_CONFIG_ALS_GAIN_MASK ) )
        {
            ctx->als_res *= 4;
        }

        ctx->als_res *= ( 1 << ( ( LIGHT6_ALS_CONFIG_ALS_IT_400_MS - ( config & LIGHT6_ALS_CONFIG_ALS_IT_MASK ) ) >> 12 ) );
        
        return LIGHT6_OK;
    }
    return LIGHT6_ERROR;
}

err_t light6_get_als_config ( light6_t *ctx, uint16_t *config )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( LIGHT6_OK == light6_generic_read( ctx, LIGHT6_REG_ALS_CONF, data_buf, 2 ) )
    {
        if ( NULL != config )
        {
            *config = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        }
        return LIGHT6_OK;
    }
    return LIGHT6_ERROR;
}

err_t light6_set_als_threshold ( light6_t *ctx, uint16_t threshold_low, uint16_t threshold_high )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( threshold_high & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( threshold_high >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( threshold_low & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( threshold_low >> 8 ) & 0xFF );
    return light6_generic_write( ctx, LIGHT6_REG_ALS_THDH_L, data_buf, 4 );
}

err_t light6_get_als_threshold ( light6_t *ctx, uint16_t *threshold_low, uint16_t *threshold_high )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( LIGHT6_OK == light6_generic_read( ctx, LIGHT6_REG_ALS_THDH_L, data_buf, 4 ) )
    {
        if ( NULL != threshold_high )
        {
            *threshold_high = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        if ( NULL != threshold_low )
        {
            *threshold_low = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        }
        return LIGHT6_OK;
    }
    return LIGHT6_ERROR;
}

err_t light6_get_int_flag ( light6_t *ctx, uint8_t *int_flag )
{
    return light6_generic_read( ctx, LIGHT6_REG_INT_FLAG, int_flag, 1 );
}

err_t light6_get_raw_data ( light6_t *ctx, uint16_t *als_data, uint16_t *ir_data )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( LIGHT6_OK == light6_generic_read( ctx, LIGHT6_REG_ALS_DATA_L, data_buf, 4 ) )
    {
        if ( NULL != als_data )
        {
            *als_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        if ( NULL != ir_data )
        {
            *ir_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        }
        return LIGHT6_OK;
    }
    return LIGHT6_ERROR;
}

err_t light6_get_data ( light6_t *ctx, float *als_data, uint16_t *ir_data )
{
    uint16_t als_data_raw = 0;
    if ( LIGHT6_OK == light6_get_raw_data( ctx, &als_data_raw, ir_data ) )
    {
        if ( NULL != als_data )
        {
            *als_data = als_data_raw * ctx->als_res;
        }
        return LIGHT6_OK;
    }
    return LIGHT6_ERROR;
}

// ------------------------------------------------------------------------- END
