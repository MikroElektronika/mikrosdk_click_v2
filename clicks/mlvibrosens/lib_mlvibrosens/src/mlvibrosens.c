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
 * @file mlvibrosens.c
 * @brief ML Vibro Sens Click Driver.
 */

#include "mlvibrosens.h"

void mlvibrosens_cfg_setup ( mlvibrosens_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->bal = HAL_PIN_NC;
    cfg->unb = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = MLVIBROSENS_DEVICE_ADDRESS_0;
}

err_t mlvibrosens_init ( mlvibrosens_t *ctx, mlvibrosens_cfg_t *cfg ) 
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

    digital_out_init( &ctx->bal, cfg->bal );
    digital_out_init( &ctx->unb, cfg->unb );
    digital_out_low ( &ctx->bal );
    digital_out_low ( &ctx->unb );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t mlvibrosens_default_cfg ( mlvibrosens_t *ctx ) 
{
    err_t error_flag = MLVIBROSENS_OK;
    uint8_t reg_data = 0;
    uint8_t num_tries = 0;
    mlvibrosens_set_vibro_state ( ctx, MLVIBROSENS_VIBRO_STATE_IDLE );
    for ( ; ; )
    {
        Delay_100ms ( );
        // Wait for a boot sequence completed flag
        if ( ( MLVIBROSENS_OK == mlvibrosens_get_status( ctx, &reg_data ) ) &&
             ( reg_data & MLVIBROSENS_INT_STATUS_SRC_BOOT ) )
        {
            break;
        }
        if ( ++num_tries > 10 )
        {
            return MLVIBROSENS_ERROR;
        }
    }
    error_flag |= mlvibrosens_sw_reset ( ctx );
    Delay_100ms ( );
    if ( MLVIBROSENS_ERROR == mlvibrosens_check_comm ( ctx ) )
    {
        return MLVIBROSENS_ERROR;
    }
    error_flag |= mlvibrosens_set_mode ( ctx, MLVIBROSENS_MODE_STANDBY );
    Delay_100ms ( );
    error_flag |= mlvibrosens_set_fsr ( ctx, MLVIBROSENS_FSR_4G );
    error_flag |= mlvibrosens_set_odr ( ctx, MLVIBROSENS_ODR_100_HZ );
    // Enable data ready interrupt on INT1 pin open-drain active low
    error_flag |= mlvibrosens_write_reg ( ctx, MLVIBROSENS_REG_INT_EN, MLVIBROSENS_INT_EN_DRDY );
    error_flag |= mlvibrosens_write_reg ( ctx, MLVIBROSENS_REG_INT_PIN_SEL, MLVIBROSENS_INT_PIN_SEL_ALL_INT1 );
    error_flag |= mlvibrosens_write_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG4, MLVIBROSENS_SENS_CONFIG4_INT_PP_LOW );
    Delay_10ms ( );
    error_flag |= mlvibrosens_set_mode ( ctx, MLVIBROSENS_MODE_ACTIVE );
    Delay_100ms ( );
    return error_flag;

    return error_flag;
}

err_t mlvibrosens_write_regs ( mlvibrosens_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t mlvibrosens_read_regs ( mlvibrosens_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t mlvibrosens_write_reg ( mlvibrosens_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return mlvibrosens_write_regs( ctx, reg, &data_in, 1 );
}

err_t mlvibrosens_read_reg ( mlvibrosens_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return mlvibrosens_read_regs( ctx, reg, data_out, 1 );
}

void mlvibrosens_balanced_enable ( mlvibrosens_t *ctx )
{
    digital_out_high ( &ctx->bal );
}

void mlvibrosens_balanced_disable ( mlvibrosens_t *ctx )
{
    digital_out_low ( &ctx->bal );
}

void mlvibrosens_unbalanced_enable ( mlvibrosens_t *ctx )
{
    digital_out_high ( &ctx->unb );
}

void mlvibrosens_unbalanced_disable ( mlvibrosens_t *ctx )
{
    digital_out_low ( &ctx->unb );
}

uint8_t mlvibrosens_get_int_pin ( mlvibrosens_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void mlvibrosens_set_vibro_state ( mlvibrosens_t *ctx, uint8_t state )
{
    switch ( state )
    {
        case MLVIBROSENS_VIBRO_STATE_BALANCED:
        {
            mlvibrosens_balanced_enable ( ctx );
            mlvibrosens_unbalanced_disable ( ctx );
            break;
        }
        case MLVIBROSENS_VIBRO_STATE_UNBALANCED:
        {
            mlvibrosens_balanced_disable ( ctx );
            mlvibrosens_unbalanced_enable ( ctx );
            break;
        }
        case MLVIBROSENS_VIBRO_STATE_BOTH:
        {
            mlvibrosens_balanced_enable ( ctx );
            mlvibrosens_unbalanced_enable ( ctx );
            break;
        }
        default:
        {
            mlvibrosens_balanced_disable ( ctx );
            mlvibrosens_unbalanced_disable ( ctx );
            break;
        }
    }
}

err_t mlvibrosens_check_comm ( mlvibrosens_t *ctx )
{
    uint8_t device_id = 0;
    if ( MLVIBROSENS_OK == mlvibrosens_read_reg ( ctx, MLVIBROSENS_REG_WHO_AM_I, &device_id ) )
    {
        if ( MLVIBROSENS_WHO_AM_I == device_id )
        {
            return MLVIBROSENS_OK;
        }
    }
    return MLVIBROSENS_ERROR;
}

err_t mlvibrosens_get_status ( mlvibrosens_t *ctx, uint8_t *status ) 
{
    return mlvibrosens_read_reg ( ctx, MLVIBROSENS_REG_INT_STATUS, status );
}

err_t mlvibrosens_sw_reset ( mlvibrosens_t *ctx ) 
{
    return mlvibrosens_write_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG1, MLVIBROSENS_SENS_CONFIG1_RST );
}

err_t mlvibrosens_set_mode ( mlvibrosens_t *ctx, uint8_t mode ) 
{
    uint8_t reg_data = 0;
    if ( mode > MLVIBROSENS_MODE_ACTIVE )
    {
        return MLVIBROSENS_ERROR;
    }
    err_t error_flag = mlvibrosens_read_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG1, &reg_data );
    reg_data &= ( ~MLVIBROSENS_SENS_CONFIG1_MODE_MASK );
    reg_data |= mode;
    error_flag |= mlvibrosens_write_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG1, reg_data );
    return error_flag;
}

err_t mlvibrosens_set_fsr ( mlvibrosens_t *ctx, uint8_t fsr ) 
{
    uint8_t reg_data = 0;
    if ( fsr > MLVIBROSENS_FSR_16G )
    {
        return MLVIBROSENS_ERROR;
    }
    err_t error_flag = mlvibrosens_read_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG1, &reg_data );
    reg_data &= ( ~MLVIBROSENS_SENS_CONFIG1_FSR_MASK );
    reg_data |= ( fsr << 1 );
    error_flag |= mlvibrosens_write_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG1, reg_data );
    if ( MLVIBROSENS_OK == error_flag )
    {
        ctx->lsb_per_g = MLVIBROSENS_LSB_PER_G_FSR_2G >> fsr;
    }
    return error_flag;
}

err_t mlvibrosens_set_odr ( mlvibrosens_t *ctx, uint8_t odr ) 
{
    uint8_t reg_data = 0;
    if ( odr > MLVIBROSENS_ODR_0_781_HZ )
    {
        return MLVIBROSENS_ERROR;
    }
    err_t error_flag = mlvibrosens_read_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG3, &reg_data );
    reg_data &= ( ~MLVIBROSENS_SENS_CONFIG3_WAKE_ODR_MASK );
    reg_data |= ( odr << 4 );
    error_flag |= mlvibrosens_write_reg ( ctx, MLVIBROSENS_REG_SENS_CONFIG3, reg_data );
    return error_flag;
}

err_t mlvibrosens_get_data ( mlvibrosens_t *ctx, mlvibrosens_data_t *data_out )
{
    uint8_t data_buf[ 7 ] = { 0 };
    int16_t raw_data = 0;
    uint8_t status = 0;
    err_t error_flag = mlvibrosens_get_status ( ctx, &status );
    if ( ( MLVIBROSENS_OK == error_flag ) && ( status & MLVIBROSENS_INT_STATUS_SRC_DRDY ) )
    {
        error_flag |= mlvibrosens_read_regs ( ctx, MLVIBROSENS_REG_OUT_X_LSB, data_buf, 6 );
        error_flag |= mlvibrosens_read_reg ( ctx, MLVIBROSENS_REG_TEMP_OUT, &data_buf[ 6 ] );
        if ( ( MLVIBROSENS_OK == error_flag ) && ( NULL != data_out ) )
        {
            raw_data = data_buf[ 1 ];
            raw_data <<= 8;
            raw_data |= data_buf[ 0 ];
            data_out->x = ( float ) raw_data / ctx->lsb_per_g;
            raw_data = data_buf[ 3 ];
            raw_data <<= 8;
            raw_data |= data_buf[ 2 ];
            data_out->y = ( float ) raw_data / ctx->lsb_per_g;
            raw_data = data_buf[ 5 ];
            raw_data <<= 8;
            raw_data |= data_buf[ 4 ];
            data_out->z = ( float ) raw_data / ctx->lsb_per_g;
            data_out->temperature = ( int8_t ) data_buf[ 6 ] + MLVIBROSENS_TEMP_OFFSET;
            return MLVIBROSENS_OK;
        }
    }
    return MLVIBROSENS_ERROR;
}

// ------------------------------------------------------------------------- END
