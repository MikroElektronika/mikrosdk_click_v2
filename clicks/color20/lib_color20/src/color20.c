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
 * @file color20.c
 * @brief Color 20 Click Driver.
 */

#include "color20.h"

void color20_cfg_setup ( color20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR20_DEVICE_ADDRESS;
}

err_t color20_init ( color20_t *ctx, color20_cfg_t *cfg ) 
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

err_t color20_default_cfg ( color20_t *ctx ) 
{
    err_t error_flag = COLOR20_OK;
    if ( COLOR20_ERROR == color20_check_communication ( ctx ) )
    {
        return COLOR20_ERROR;
    }
    error_flag |= color20_set_rgb_config ( ctx, COLOR20_RGB_CONFIG_DEFAULT );
    error_flag |= color20_set_g_threshold ( ctx, COLOR20_THRESHOLD_LOW_DEFAULT, COLOR20_THRESHOLD_HIGH_DEFAULT );
    Delay_100ms( );
    return error_flag;
}

err_t color20_generic_write ( color20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color20_generic_read ( color20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t color20_get_int_pin ( color20_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t color20_check_communication ( color20_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( COLOR20_OK == color20_generic_read ( ctx, COLOR20_REG_VEML6046X00_ID_L, data_buf, 2 ) )
    {
        if ( COLOR20_DEVICE_ID == ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ] ) )
        {
            return COLOR20_OK;
        }
    }
    return COLOR20_ERROR;
}

err_t color20_set_rgb_config ( color20_t *ctx, uint16_t config )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( config >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( config & 0xFF );
    if ( COLOR20_OK == color20_generic_write( ctx, COLOR20_REG_RGB_CONF_0, data_buf, 2 ) )
    {
        ctx->rgb_res = COLOR20_RGB_MIN_RES;

        if ( COLOR20_RGB_CONFIG_RGB_PDDIV_1_2_PD == ( config & COLOR20_RGB_CONFIG_RGB_PDDIV_MASK ) )
        {
            ctx->rgb_res *= 2;
        }

        if ( COLOR20_RGB_CONFIG_RGB_GAIN_X1 == ( config & COLOR20_RGB_CONFIG_RGB_GAIN_MASK ) )
        {
            ctx->rgb_res *= 2;
        }
        else if ( COLOR20_RGB_CONFIG_RGB_GAIN_X0_66 == ( config & COLOR20_RGB_CONFIG_RGB_GAIN_MASK ) )
        {
            ctx->rgb_res *= 3;
        }
        else if ( COLOR20_RGB_CONFIG_RGB_GAIN_X0_5 == ( config & COLOR20_RGB_CONFIG_RGB_GAIN_MASK ) )
        {
            ctx->rgb_res *= 4;
        }

        ctx->rgb_res *= ( 1 << ( ( COLOR20_RGB_CONFIG_RGB_IT_400_MS - ( config & COLOR20_RGB_CONFIG_RGB_IT_MASK ) ) >> 12 ) );
        
        return COLOR20_OK;
    }
    return COLOR20_ERROR;
}

err_t color20_get_rgb_config ( color20_t *ctx, uint16_t *config )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( COLOR20_OK == color20_generic_read( ctx, COLOR20_REG_RGB_CONF_0, data_buf, 2 ) )
    {
        if ( NULL != config )
        {
            *config = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        }
        return COLOR20_OK;
    }
    return COLOR20_ERROR;
}

err_t color20_set_g_threshold ( color20_t *ctx, uint16_t threshold_low, uint16_t threshold_high )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( threshold_high & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( threshold_high >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( threshold_low & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( threshold_low >> 8 ) & 0xFF );
    return color20_generic_write( ctx, COLOR20_REG_G_THDH_L, data_buf, 4 );
}

err_t color20_get_g_threshold ( color20_t *ctx, uint16_t *threshold_low, uint16_t *threshold_high )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( COLOR20_OK == color20_generic_read( ctx, COLOR20_REG_G_THDH_L, data_buf, 4 ) )
    {
        if ( NULL != threshold_high )
        {
            *threshold_high = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        if ( NULL != threshold_low )
        {
            *threshold_low = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        }
        return COLOR20_OK;
    }
    return COLOR20_ERROR;
}

err_t color20_get_int_flag ( color20_t *ctx, uint8_t *int_flag )
{
    return color20_generic_read( ctx, COLOR20_REG_INT_FLAG, int_flag, 1 );
}

err_t color20_get_raw_data ( color20_t *ctx, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *ir_data )
{
    uint8_t data_buf[ 8 ] = { 0 };
    if ( COLOR20_OK == color20_generic_read( ctx, COLOR20_REG_R_DATA_L, data_buf, 8 ) )
    {
        if ( NULL != red )
        {
            *red = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        if ( NULL != green )
        {
            *green = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
        }
        if ( NULL != blue )
        {
            *blue = ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
        }
        if ( NULL != ir_data )
        {
            *ir_data = ( ( uint16_t ) data_buf[ 7 ] << 8 ) | data_buf[ 6 ];
        }
        return COLOR20_OK;
    }
    return COLOR20_ERROR;
}

err_t color20_get_data ( color20_t *ctx, float *red, float *green, float *blue, uint16_t *ir_data )
{
    uint16_t red_raw = 0;
    uint16_t green_raw = 0;
    uint16_t blue_raw = 0;
    if ( COLOR20_OK == color20_get_raw_data( ctx, &red_raw, &green_raw, &blue_raw, ir_data ) )
    {
        if ( NULL != red )
        {
            *red = red_raw * ctx->rgb_res;
        }
        if ( NULL != green )
        {
            *green = green_raw * ctx->rgb_res;
        }
        if ( NULL != blue )
        {
            *blue = blue_raw * ctx->rgb_res;
        }
        return COLOR20_OK;
    }
    return COLOR20_ERROR;
}

// ------------------------------------------------------------------------- END
