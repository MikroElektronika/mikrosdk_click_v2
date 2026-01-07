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
 * @file ambient26.c
 * @brief Ambient 26 Click Driver.
 */

#include "ambient26.h"

void ambient26_cfg_setup ( ambient26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = AMBIENT26_DEVICE_ADDRESS;
}

err_t ambient26_init ( ambient26_t *ctx, ambient26_cfg_t *cfg ) 
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

err_t ambient26_default_cfg ( ambient26_t *ctx ) 
{
    err_t error_flag = AMBIENT26_OK;

    if ( AMBIENT26_ERROR == ambient26_check_com ( ctx ) )
    {
        return AMBIENT26_ERROR;
    }

    error_flag |= ambient26_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= ambient26_set_sensor_standby ( ctx );
    error_flag |= ambient26_set_data_rate ( ctx, AMBIENT26_DATA_RATE_100_MS );
    error_flag |= ambient26_set_resolution ( ctx, AMBIENT26_RESOLUTION_20_BIT );
    error_flag |= ambient26_set_gain ( ctx, AMBIENT26_GAIN_18 );
    error_flag |= ambient26_set_threshold ( ctx, AMBIENT26_THRESHOLD_UPPER, AMBIENT26_THRESHOLD_LOWER );
    error_flag |= ambient26_set_mode ( ctx, AMBIENT26_MODE_ALS );
    error_flag |= ambient26_enable_interrupt ( ctx, AMBIENT26_INT_MODE_ALS, AMBIENT26_INT_PERSISTANCE_1 );
    Delay_100ms ( );
    
    return error_flag;
}

err_t ambient26_write_reg ( ambient26_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t ambient26_read_reg ( ambient26_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

uint8_t ambient26_get_int_pin ( ambient26_t *ctx )
{
    return !!digital_in_read ( &ctx->int_pin );
}

err_t ambient26_check_com ( ambient26_t *ctx )
{
    uint8_t part_id = 0;
    if ( AMBIENT26_OK == ambient26_read_reg ( ctx, AMBIENT26_REG_PART_ID, &part_id ) )
    {
        if ( AMBIENT26_PART_ID == ( part_id & AMBIENT26_PART_ID_MASK ) )
        {
            return AMBIENT26_OK;
        }
    }
    return AMBIENT26_ERROR;
}

err_t ambient26_soft_reset ( ambient26_t *ctx )
{
    return ambient26_write_reg ( ctx, AMBIENT26_REG_MAIN_CTRL, AMBIENT26_MAIN_CTRL_SW_RESET );
}

err_t ambient26_set_sensor_active ( ambient26_t *ctx )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t main_ctrl = 0;
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_MAIN_CTRL, &main_ctrl );
    if ( AMBIENT26_OK == error_flag )
    {
        main_ctrl |= AMBIENT26_MAIN_CTRL_SENSOR_ACTIVE;
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_MAIN_CTRL, main_ctrl );
    }
    return error_flag;
}

err_t ambient26_set_sensor_standby ( ambient26_t *ctx )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t main_ctrl = 0;
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_MAIN_CTRL, &main_ctrl );
    if ( AMBIENT26_OK == error_flag )
    {
        main_ctrl &= ( ~AMBIENT26_MAIN_CTRL_SENSOR_ACTIVE );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_MAIN_CTRL, main_ctrl );
    }
    return error_flag;
}

err_t ambient26_set_mode ( ambient26_t *ctx, uint8_t mode )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t main_ctrl = 0;
    if ( mode > AMBIENT26_MODE_UVS )
    {
        return AMBIENT26_ERROR;
    }
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_MAIN_CTRL, &main_ctrl );
    if ( AMBIENT26_OK == error_flag )
    {
        main_ctrl &= ( ~AMBIENT26_MAIN_CTRL_UVS_MODE_MASK );
        main_ctrl |= ( ( mode << 3 ) & AMBIENT26_MAIN_CTRL_UVS_MODE_MASK );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_MAIN_CTRL, main_ctrl );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        ctx->mode = mode;
    }
    return error_flag;
}

err_t ambient26_set_resolution ( ambient26_t *ctx, uint8_t resolution )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t meas_rate = 0;
    if ( resolution > AMBIENT26_RESOLUTION_20_BIT )
    {
        return AMBIENT26_ERROR;
    }
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_ALS_UVS_MEAS_RATE, &meas_rate );
    if ( AMBIENT26_OK == error_flag )
    {
        meas_rate &= ( ~AMBIENT26_ALS_UVS_RES_MASK );
        meas_rate |= ( ( ( AMBIENT26_RESOLUTION_20_BIT - resolution ) << 4 ) & AMBIENT26_ALS_UVS_RES_MASK );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_MEAS_RATE, meas_rate );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        if ( AMBIENT26_RESOLUTION_13_BIT == resolution )
        {
            ctx->integration_time = 0.03125;
            ctx->data_res = 13;
        }
        else
        {
            ctx->integration_time = 0.25 * ( 1 << ( resolution - 1 ) );
            ctx->data_res = 15 + resolution;
        }
    }
    return error_flag;
}

err_t ambient26_set_data_rate ( ambient26_t *ctx, uint8_t data_rate )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t meas_rate = 0;
    if ( data_rate > AMBIENT26_DATA_RATE_2000_MS )
    {
        return AMBIENT26_ERROR;
    }
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_ALS_UVS_MEAS_RATE, &meas_rate );
    if ( AMBIENT26_OK == error_flag )
    {
        meas_rate &= ( ~AMBIENT26_ALS_UVS_RATE_MASK );
        meas_rate |= ( data_rate & AMBIENT26_ALS_UVS_RATE_MASK );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_MEAS_RATE, meas_rate );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        ctx->data_rate = data_rate;
    }
    return error_flag;
}

err_t ambient26_set_gain ( ambient26_t *ctx, uint8_t gain )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t reg_gain = 0;
    if ( gain > AMBIENT26_GAIN_18 )
    {
        return AMBIENT26_ERROR;
    }
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_ALS_UVS_GAIN, &reg_gain );
    if ( AMBIENT26_OK == error_flag )
    {
        reg_gain &= ( ~AMBIENT26_ALS_UVS_GAIN_MASK );
        reg_gain |= ( gain & AMBIENT26_ALS_UVS_GAIN_MASK );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_GAIN, reg_gain );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        switch ( gain )
        {
            case AMBIENT26_GAIN_1:
            {
                ctx->gain = 1;
                break;
            }
            case AMBIENT26_GAIN_3:
            {
                ctx->gain = 3;
                break;
            }
            case AMBIENT26_GAIN_6:
            {
                ctx->gain = 6;
                break;
            }
            case AMBIENT26_GAIN_9:
            {
                ctx->gain = 9;
                break;
            }
            case AMBIENT26_GAIN_18:
            {
                ctx->gain = 18;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return error_flag;
}

err_t ambient26_get_main_status ( ambient26_t *ctx )
{
    return ambient26_read_reg ( ctx, AMBIENT26_REG_MAIN_STATUS, &ctx->main_status );
}

err_t ambient26_enable_interrupt ( ambient26_t *ctx, uint8_t int_mode, uint8_t persistance )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t int_cfg = 0;
    uint8_t int_pst = 0;
    if ( ( int_mode > AMBIENT26_INT_MODE_UVS ) || ( persistance > AMBIENT26_INT_PERSISTANCE_16 ) )
    {
        return AMBIENT26_ERROR;
    }
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_INT_PST, &int_pst );
    if ( AMBIENT26_OK == error_flag )
    {
        int_pst &= ( ~AMBIENT26_INT_PST_MASK );
        int_pst |= ( ( persistance << 4 ) & AMBIENT26_INT_PST_MASK );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_INT_PST, int_pst );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_INT_CFG, &int_cfg );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        int_cfg &= ( ~AMBIENT26_INT_CFG_LS_INT_SEL_MASK );
        if ( AMBIENT26_INT_MODE_UVS == int_mode )
        {
            int_cfg |= AMBIENT26_INT_CFG_LS_INT_SEL_UVS;
        }
        else
        {
            int_cfg |= AMBIENT26_INT_CFG_LS_INT_SEL_ALS;
        }
        int_cfg |= AMBIENT26_INT_CFG_LS_INT_EN_ENABLE;
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_INT_CFG, int_cfg );
    }
    return error_flag;
}

err_t ambient26_disable_interrupt ( ambient26_t *ctx )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t int_cfg = 0;
    error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_INT_CFG, &int_cfg );
    if ( AMBIENT26_OK == error_flag )
    {
        int_cfg &= ( ~AMBIENT26_INT_CFG_LS_INT_EN_ENABLE );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_INT_CFG, int_cfg );
    }
    return error_flag;
}

err_t ambient26_set_threshold ( ambient26_t *ctx, uint32_t upper, uint32_t lower )
{
    err_t error_flag = AMBIENT26_OK;
    uint8_t thres = ( uint8_t ) ( upper & 0xFF );
    error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_THRES_UP_0, thres );
    if ( AMBIENT26_OK == error_flag )
    {
        thres = ( uint8_t ) ( ( upper >> 8 ) & 0xFF );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_THRES_UP_1, thres );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        thres = ( uint8_t ) ( ( upper >> 16 ) & 0x0F );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_THRES_UP_2, thres );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        thres = ( uint8_t ) ( lower & 0xFF );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_THRES_LOW_0, thres );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        thres = ( uint8_t ) ( ( lower >> 8 ) & 0xFF );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_THRES_LOW_1, thres );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        thres = ( uint8_t ) ( ( lower >> 16 ) & 0x0F );
        error_flag = ambient26_write_reg ( ctx, AMBIENT26_REG_ALS_UVS_THRES_LOW_2, thres );
    }
    return error_flag;
}

err_t ambient26_get_als_raw ( ambient26_t *ctx, uint32_t *als_raw )
{
    err_t error_flag = AMBIENT26_OK;
    uint16_t timeout_cnt = 0;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( AMBIENT26_MODE_ALS != ctx->mode )
    {
        error_flag = ambient26_set_mode ( ctx, AMBIENT26_MODE_ALS );
        if ( AMBIENT26_OK == error_flag )
        {
            error_flag = ambient26_enable_interrupt ( ctx, AMBIENT26_INT_MODE_ALS, AMBIENT26_INT_PERSISTANCE_1 );
        }
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_set_sensor_active ( ctx );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        while ( ambient26_get_int_pin ( ctx ) )
        {
            Delay_1ms ( );
            if ( ++timeout_cnt > AMBIENT26_TIMEOUT_MS )
            {
                error_flag = AMBIENT26_ERROR;
            }
        }
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_get_main_status ( ctx );
        if ( AMBIENT26_MAIN_STATUS_DATA != ( ctx->main_status & AMBIENT26_MAIN_STATUS_DATA ) )
        {
            error_flag = AMBIENT26_ERROR;
        }
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_ALS_DATA_0, &data_buf[ 0 ] );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_ALS_DATA_1, &data_buf[ 1 ] );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_ALS_DATA_2, &data_buf[ 2 ] );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        if ( NULL != als_raw )
        {
            *als_raw = ( ( uint32_t ) ( data_buf[ 2 ] & 0x0F ) << 16 ) |
                       ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        error_flag = ambient26_set_sensor_standby ( ctx );
    }
    return error_flag;
}

err_t ambient26_get_uvs_raw ( ambient26_t *ctx, uint32_t *uvs_raw )
{
    err_t error_flag = AMBIENT26_OK;
    uint16_t timeout_cnt = 0;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( AMBIENT26_MODE_UVS != ctx->mode )
    {
        error_flag = ambient26_set_mode ( ctx, AMBIENT26_MODE_UVS );
        if ( AMBIENT26_OK == error_flag )
        {
            error_flag = ambient26_enable_interrupt ( ctx, AMBIENT26_INT_MODE_UVS, AMBIENT26_INT_PERSISTANCE_1 );
        }
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_set_sensor_active ( ctx );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        while ( ambient26_get_int_pin ( ctx ) )
        {
            Delay_1ms ( );
            if ( ++timeout_cnt > AMBIENT26_TIMEOUT_MS )
            {
                error_flag = AMBIENT26_ERROR;
            }
        }
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_get_main_status ( ctx );
        if ( AMBIENT26_MAIN_STATUS_DATA != ( ctx->main_status & AMBIENT26_MAIN_STATUS_DATA ) )
        {
            error_flag = AMBIENT26_ERROR;
        }
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_UVS_DATA_0, &data_buf[ 0 ] );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_UVS_DATA_1, &data_buf[ 1 ] );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        error_flag = ambient26_read_reg ( ctx, AMBIENT26_REG_UVS_DATA_2, &data_buf[ 2 ] );
    }
    if ( AMBIENT26_OK == error_flag )
    {
        if ( NULL != uvs_raw )
        {
            *uvs_raw = ( ( uint32_t ) ( data_buf[ 2 ] & 0x0F ) << 16 ) |
                       ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        }
        error_flag = ambient26_set_sensor_standby ( ctx );
    }
    return error_flag;
}

err_t ambient26_get_als_lux ( ambient26_t *ctx, float *als_lux )
{
    err_t error_flag = AMBIENT26_OK;
    uint32_t als_raw = 0;
    error_flag = ambient26_get_als_raw ( ctx, &als_raw );
    if ( AMBIENT26_OK == error_flag )
    {
        if ( NULL != als_lux )
        {
            *als_lux = ( AMBIENT26_ALS_SENS * als_raw ) / ( ctx->gain * ctx->integration_time );
        }
    }
    return error_flag;
}

err_t ambient26_get_uv_index ( ambient26_t *ctx, float *uvi )
{
    err_t error_flag = AMBIENT26_OK;
    uint32_t uvs_raw = 0;
    error_flag = ambient26_get_uvs_raw ( ctx, &uvs_raw );
    if ( AMBIENT26_OK == error_flag )
    {
        if ( NULL != uvi )
        {
            *uvi = uvs_raw / ( ( ( float ) ctx->gain / AMBIENT26_MAX_GAIN ) * 
                               ( ( float ) 1 / ( ( uint32_t ) 1 << 
                                                 ( AMBIENT26_MAX_RES - ctx->data_res ) ) ) * 
                               AMBIENT26_UVI_SENS );
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
