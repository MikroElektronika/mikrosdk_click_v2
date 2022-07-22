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
 * @file ambient19.c
 * @brief Ambient 19 Click Driver.
 */

#include "ambient19.h"

void ambient19_cfg_setup ( ambient19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT19_DEVICE_ADDRESS;
}

err_t ambient19_init ( ambient19_t *ctx, ambient19_cfg_t *cfg ) 
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

err_t ambient19_default_cfg ( ambient19_t *ctx ) 
{
    err_t error_flag = AMBIENT19_OK;
    if ( AMBIENT19_ERROR == ambient19_check_communication ( ctx ) )
    {
        return AMBIENT19_ERROR;
    }
    error_flag |= ambient19_write_register ( ctx, AMBIENT19_REG_SYSM_CTRL, AMBIENT19_SYSM_EN_WAIT | 
                                                                           AMBIENT19_SYSM_EN_PS | 
                                                                           AMBIENT19_SYSM_EN_ALS );
    error_flag |= ambient19_write_register ( ctx, AMBIENT19_REG_PERSISTENCE, AMBIENT19_PERSISTANCE_EVERY_ALS_CONV );
    error_flag |= ambient19_write_register ( ctx, AMBIENT19_REG_INT_CTRL, AMBIENT19_INT_CTRL_EN_AINT );
    error_flag |= ambient19_set_wait_time ( ctx, AMBIENT19_WAIT_TIME_DEFAULT );
    error_flag |= ambient19_set_als_time ( ctx, AMBIENT19_ALS_TIME_DEFAULT );
    error_flag |= ambient19_set_als_gain ( ctx, AMBIENT19_ALS_GAIN_1X );
    error_flag |= ambient19_write_register ( ctx, AMBIENT19_REG_LED_CTRL, AMBIENT19_LED_CTRL_IRDR_SEL_100mA );
    error_flag |= ambient19_write_register ( ctx, AMBIENT19_REG_PS_GAIN, AMBIENT19_PS_GAIN_1X );
    error_flag |= ambient19_write_register ( ctx, AMBIENT19_REG_PS_TIME, AMBIENT19_PS_TIME_MAX_COUNT_4095 );
    Delay_1sec ( ); 
    return error_flag;
}

err_t ambient19_generic_write ( ambient19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 34 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ambient19_generic_read ( ambient19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ambient19_write_register ( ambient19_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return ambient19_generic_write( ctx, reg, &data_in, 1 );
}

err_t ambient19_read_register ( ambient19_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return ambient19_generic_read( ctx, reg, data_out, 1 );
}

err_t ambient19_check_communication ( ambient19_t *ctx )
{
    uint8_t data_buf[ 2 ];
    if ( AMBIENT19_OK == ambient19_generic_read ( ctx, AMBIENT19_REG_PNO_LB, data_buf, 2 ) ) 
    {
        if ( ( AMBIENT19_PRODUCT_NUM_LOW == data_buf[ 0 ] ) && 
             ( AMBIENT19_PRODUCT_NUM_HIGH == data_buf[ 1 ] ) )
        {
            return AMBIENT19_OK;
        }
    }
    return AMBIENT19_ERROR;
}

uint8_t ambient19_get_int_pin ( ambient19_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ambient19_clear_interrupts ( ambient19_t *ctx )
{
    uint8_t int_flag;
    err_t error_flag = ambient19_read_register ( ctx, AMBIENT19_REG_INT_FLAG, &int_flag );
    error_flag |= ambient19_write_register ( ctx, AMBIENT19_REG_INT_FLAG, ~int_flag );
    return error_flag;
}

err_t ambient19_set_wait_time ( ambient19_t *ctx, float wait_time_ms )
{
    uint8_t wait_time = 0;
    if ( wait_time_ms >= AMBIENT19_WAIT_TIME_MAX ) 
    {
        wait_time = 0xFF;
    }
    else if ( wait_time_ms <= AMBIENT19_WAIT_TIME_MIN )
    {
        wait_time = 0;
    }
    else
    {
        wait_time = ( uint8_t ) ( ( wait_time_ms - AMBIENT19_WAIT_TIME_MIN ) / AMBIENT19_WAIT_TIME_STEP );
    }
    return ambient19_write_register( ctx, AMBIENT19_REG_WAIT_TIME, wait_time );
}

err_t ambient19_set_als_time ( ambient19_t *ctx, float als_time_ms )
{
    if ( als_time_ms >= AMBIENT19_ALS_TIME_MAX ) 
    {
        ctx->alsconv = 0xFF;
    }
    else if ( als_time_ms <= AMBIENT19_ALS_TIME_MIN )
    {
        ctx->alsconv = 0;
    }
    else
    {
        ctx->alsconv = ( uint8_t ) ( ( als_time_ms - AMBIENT19_ALS_TIME_MIN ) / AMBIENT19_ALS_TIME_STEP );
    }
    return ambient19_write_register( ctx, AMBIENT19_REG_ALS_TIME, ctx->alsconv );
}

err_t ambient19_set_als_gain ( ambient19_t *ctx, uint8_t als_gain )
{
    switch ( als_gain )
    {
        case AMBIENT19_ALS_GAIN_1X:
        {
            ctx->pga_als = 1;
            break;
        }
        case AMBIENT19_ALS_GAIN_4X:
        {
            ctx->pga_als = 4;
            break;
        }
        case AMBIENT19_ALS_GAIN_8X:
        {
            ctx->pga_als = 8;
            break;
        }
        case AMBIENT19_ALS_GAIN_32X:
        {
            ctx->pga_als = 32;
            break;
        }
        case AMBIENT19_ALS_GAIN_96X:
        {
            ctx->pga_als = 96;
            break;
        }
        default:
        {
            return AMBIENT19_ERROR;
        }
    }
    return ambient19_write_register( ctx, AMBIENT19_REG_ALS_GAIN, als_gain );
}

err_t ambient19_read_raw_als ( ambient19_t *ctx, uint16_t *ch_0, uint16_t *ch_1 )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = ambient19_generic_read ( ctx, AMBIENT19_REG_CH0_DATA_L, data_buf, 4 );
    *ch_0 = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    *ch_1 = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
    return error_flag;
}

err_t ambient19_read_raw_proximity ( ambient19_t *ctx, uint16_t *ps_data, uint16_t *ir_data )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = ambient19_generic_read ( ctx, AMBIENT19_REG_PS_DATA_L, data_buf, 4 );
    *ps_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    *ir_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
    return error_flag;
}

err_t ambient19_measure_light_level ( ambient19_t *ctx, uint16_t *lux )
{
    uint16_t ch_0, ch_1;
    if ( AMBIENT19_ERROR == ambient19_read_raw_als ( ctx, &ch_0, &ch_1 ) )
    {
        return AMBIENT19_ERROR;
    }
    if ( ( ( float ) ch_0 / ch_1 ) < 0.30 )
    {
        *lux = ( ( float ) ch_0 / ctx->pga_als ) * ( ( float ) 64 / ( ctx->alsconv + 1 ) ) * AMBIENT19_LUX_K1;
    }
    else if ( ( ( float ) ch_0 / ch_1 ) > 0.60 )
    {
        *lux = ( ( float ) ch_0 / ctx->pga_als ) * ( ( float ) 64 / ( ctx->alsconv + 1 ) ) * AMBIENT19_LUX_K2;
    }
    else
    {
        *lux = ( ( float ) ch_0 / ctx->pga_als ) * ( ( float ) 64 / ( ctx->alsconv + 1 ) ) * AMBIENT19_LUX_K3;
    }
    return AMBIENT19_OK;
}

// ------------------------------------------------------------------------- END
