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
 * @file magaccel.c
 * @brief MagAccel Click Driver.
 */

#include "magaccel.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void magaccel_cfg_setup ( magaccel_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->fld = HAL_PIN_NC;
    cfg->mot = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = MAGACCEL_DEVICE_ADDRESS;
}

err_t magaccel_init ( magaccel_t *ctx, magaccel_cfg_t *cfg ) 
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

    digital_in_init( &ctx->fld, cfg->fld );
    digital_in_init( &ctx->mot, cfg->mot );
    ctx->sensitivity = MAGACCEL_FSR_SENS_VAL_2G;

    return I2C_MASTER_SUCCESS;
}

err_t magaccel_default_cfg ( magaccel_t *ctx ) 
{
    err_t err_flag = MAGACCEL_OK;
    uint8_t data_buf = DUMMY;
    uint8_t device_id = DUMMY;
    
    // Wait for the powerup status
    do 
    {
        err_flag |= magaccel_get_status( ctx, &data_buf );
        Delay_10ms( );
    }
    while ( !( data_buf & MAGACCEL_SRC_BOOT_COMPLETED ) );
    
    err_flag |= magaccel_sw_reset( ctx );
    Delay_100ms( );

    err_flag |= magaccel_get_device_id( ctx, &device_id );
    if ( MAGACCEL_DEVICE_ID_VAL == device_id )
    {        
        // Standby
        err_flag |= magaccel_set_op_mode( ctx, MAGACCEL_OP_MODE_STANDBY );
        Delay_10ms( );

        //Enable Interrupt for boot and data ready
        err_flag |= magaccel_en_data_ready( ctx );
        Delay_10ms( );

        // Set full-scale measurement range
        err_flag |= magaccel_set_fsr( ctx, MAGACCEL_FSR_SEL_2G );
        Delay_10ms( );

        // Active
        err_flag |= magaccel_set_op_mode( ctx, MAGACCEL_OP_MODE_ACTIVE );
        Delay_10ms( );
    }
    else
    {
        err_flag = MAGACCEL_ERROR;
    }
    return err_flag;
}

err_t magaccel_generic_write ( magaccel_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t magaccel_generic_read ( magaccel_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t magaccel_get_device_id ( magaccel_t *ctx, uint8_t *device_id ) 
{
    return magaccel_generic_read( ctx, MAGACCEL_REG_WHO_AM_I, device_id, 1 );
}

err_t magaccel_get_status ( magaccel_t *ctx, uint8_t *status ) 
{
    return magaccel_generic_read( ctx, MAGACCEL_REG_INT_STATUS, status, 1 );
}

err_t magaccel_sw_reset ( magaccel_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = magaccel_generic_read( ctx, MAGACCEL_REG_SENS_CONFIG1, &data_buf, 1 );
    data_buf |= MAGACCEL_SW_RESET_BIT_MASK;
    err_flag |= magaccel_generic_write( ctx, MAGACCEL_REG_SENS_CONFIG1, &data_buf, 1 );
    return err_flag;
}

err_t magaccel_set_op_mode ( magaccel_t *ctx, uint8_t op_mode ) 
{
    err_t err_flag = MAGACCEL_ERROR;
    if ( MAGACCEL_OP_MODE_ACTIVE >= op_mode )
    {
        uint8_t data_buf = DUMMY;
        err_flag = magaccel_generic_read( ctx, MAGACCEL_REG_SENS_CONFIG1, &data_buf, 1 );
        data_buf &= MAGACCEL_OP_MODE_BIT_MASK;
        data_buf |= op_mode;
        err_flag |= magaccel_generic_write( ctx, MAGACCEL_REG_SENS_CONFIG1, &data_buf, 1 );
    }
    return err_flag;
}

err_t magaccel_set_fsr ( magaccel_t *ctx, uint8_t fsr ) 
{
    err_t err_flag = MAGACCEL_ERROR;
    if ( MAGACCEL_FSR_SEL_16G >= fsr )
    {
        uint8_t data_buf = DUMMY;
        ctx->sensitivity = MAGACCEL_FSR_SENS_VAL_2G;
        if ( fsr == MAGACCEL_FSR_SEL_4G )
        {
            ctx->sensitivity = MAGACCEL_FSR_SENS_VAL_4G;
        }
        else if ( fsr == MAGACCEL_FSR_SEL_8G )
        {
            ctx->sensitivity = MAGACCEL_FSR_SENS_VAL_8G;
        }
        else if ( fsr == MAGACCEL_FSR_SEL_16G )
        {
            ctx->sensitivity = MAGACCEL_FSR_SENS_VAL_16G;
        }

        fsr <<= 1;
        err_flag = magaccel_generic_read( ctx, MAGACCEL_REG_SENS_CONFIG1, &data_buf, 1 );
        data_buf &= MAGACCEL_FSR_SEL_BIT_MASK;
        data_buf |= fsr;
        err_flag |= magaccel_generic_write( ctx, MAGACCEL_REG_SENS_CONFIG1, &data_buf, 1 );
    }
    
    return err_flag;
}

err_t magaccel_en_data_ready ( magaccel_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = magaccel_generic_read( ctx, MAGACCEL_REG_INT_EN, &data_buf, 1 );
    data_buf |= MAGACCEL_INT_EN_DRDY_EN;
    err_flag |= magaccel_generic_write( ctx, MAGACCEL_REG_INT_EN, &data_buf, 1 );
    return err_flag;
}

err_t magaccel_get_axes_data ( magaccel_t *ctx, magaccel_axes_t *axes )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t axis_data = DUMMY;
    
    err_t err_flag = magaccel_generic_read( ctx, MAGACCEL_REG_OUT_X_LSB, data_buf, 2 );
    axis_data = data_buf[ 1 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 0 ];
    axes->x = ( float ) axis_data * ctx->sensitivity;
    
    err_flag |= magaccel_generic_read( ctx, MAGACCEL_REG_OUT_Y_LSB, data_buf, 2 );
    axis_data = data_buf[ 1 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 0 ];
    axes->y = ( float ) axis_data * ctx->sensitivity;
    
    err_flag |= magaccel_generic_read( ctx, MAGACCEL_REG_OUT_Z_LSB, data_buf, 2 );
    axis_data = data_buf[ 1 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 0 ];
    axes->z = ( float ) axis_data * ctx->sensitivity;
    
    return err_flag;
}

uint8_t magaccel_check_data_ready ( magaccel_t *ctx )
{
    return digital_in_read( &ctx->mot );
}

uint8_t magaccel_check_mag_field ( magaccel_t *ctx ) 
{
    return digital_in_read( &ctx->fld );
}

// ------------------------------------------------------------------------- END
