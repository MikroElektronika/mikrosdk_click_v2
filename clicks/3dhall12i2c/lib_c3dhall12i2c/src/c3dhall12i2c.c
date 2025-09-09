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
 * @file c3dhall12i2c.c
 * @brief 3D Hall 12 I2C Click Driver.
 */

#include "c3dhall12i2c.h"
#include "math.h"

void c3dhall12i2c_cfg_setup ( c3dhall12i2c_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sample = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C3DHALL12I2C_DEVICE_ADDRESS;
}

err_t c3dhall12i2c_init ( c3dhall12i2c_t *ctx, c3dhall12i2c_cfg_t *cfg ) 
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

    digital_out_init( &ctx->sample, cfg->sample );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t c3dhall12i2c_default_cfg ( c3dhall12i2c_t *ctx ) 
{
    err_t error_flag = C3DHALL12I2C_OK;
    error_flag |= c3dhall12i2c_write_reg ( ctx, C3DHALL12I2C_REG_CTRL1, C3DHALL12I2C_CTRL1_START_SAMPLE_CLEAR | 
                                                                        C3DHALL12I2C_CTRL1_INTERRUPT_FLAG_CLEAR | 
                                                                        C3DHALL12I2C_CTRL1_STATUS_READY_CLEAR | 
                                                                        C3DHALL12I2C_CTRL1_SLEEP_CNT_68_18_MS | 
                                                                        C3DHALL12I2C_CTRL1_OP_MODE_ACTIVE_SAM );
    
    error_flag |= c3dhall12i2c_write_reg ( ctx, C3DHALL12I2C_REG_CTRL3, C3DHALL12I2C_CTRL3_AFE_CHAN_DIS_Z_DIR_EN | 
                                                                        C3DHALL12I2C_CTRL3_AFE_CHAN_DIS_Y_DIR_EN | 
                                                                        C3DHALL12I2C_CTRL3_AFE_CHAN_DIS_X_DIR_EN | 
                                                                        C3DHALL12I2C_CTRL3_POL_F_Z_DIR_NORMAL | 
                                                                        C3DHALL12I2C_CTRL3_POL_F_Y_DIR_NORMAL | 
                                                                        C3DHALL12I2C_CTRL3_POL_F_X_DIR_NORMAL | 
                                                                        C3DHALL12I2C_CTRL3_INT_SEL_DIR_X | 
                                                                        C3DHALL12I2C_CTRL3_INT_SIGN_DIR_LESS | 
                                                                        C3DHALL12I2C_CTRL3_INT_FLAG_LATCH_DIR_DIS | 
                                                                        C3DHALL12I2C_CTRL3_SAMPLE_INT_POL_DIR_LOW );
    
    error_flag |= c3dhall12i2c_write_reg ( ctx, C3DHALL12I2C_REG_CTRL4, C3DHALL12I2C_CTRL4_CIC_BW_SEL_LPM_DIR_195_5_HZ | 
                                                                        C3DHALL12I2C_CTRL4_CIC_BW_SEL_DIR_195_5_HZ | 
                                                                        C3DHALL12I2C_CTRL4_CORDIC_POL_DIR_NORMAL | 
                                                                        C3DHALL12I2C_CTRL4_CORDIC_SEL_DIR_COS_X_SINE_Y );
    return error_flag;
}

err_t c3dhall12i2c_write_reg ( c3dhall12i2c_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t c3dhall12i2c_read_reg ( c3dhall12i2c_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = C3DHALL12I2C_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( NULL == data_out )
    {
        return C3DHALL12I2C_ERROR;
    }
    error_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( C3DHALL12I2C_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

void c3dhall12i2c_set_sample_pin ( c3dhall12i2c_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sample, state );
}

uint8_t c3dhall12i2c_get_int_pin ( c3dhall12i2c_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void c3dhall12i2c_start_measurement ( c3dhall12i2c_t *ctx )
{
    digital_out_low ( &ctx->sample );
    Delay_1ms ( );
    digital_out_high ( &ctx->sample );
    Delay_1ms ( );
}

err_t c3dhall12i2c_read_data ( c3dhall12i2c_t *ctx, c3dhall12i2c_data_t *data_out )
{
    err_t error_flag = C3DHALL12I2C_OK;
    uint16_t reg_data[ 6 ] = { 0 };
    int16_t raw_data_s = 0;
    if ( NULL == data_out )
    {
        return C3DHALL12I2C_ERROR;
    }
    c3dhall12i2c_start_measurement ( ctx );
    error_flag |= c3dhall12i2c_read_reg ( ctx, C3DHALL12I2C_REG_CTRL1, reg_data );
    if ( C3DHALL12I2C_OK == error_flag )
    {
        if ( C3DHALL12I2C_CTRL1_STATUS_READY_CLEAR == ( reg_data[ 0 ] & C3DHALL12I2C_CTRL1_STATUS_READY_MASK ) )
        {
            error_flag = C3DHALL12I2C_DATA_NOT_READY;
        }
    }
    if ( C3DHALL12I2C_OK == error_flag )
    {
        reg_data[ 0 ] = reg_data[ 0 ] & ( ~C3DHALL12I2C_CTRL1_STATUS_READY_MASK );
        error_flag |= c3dhall12i2c_write_reg ( ctx, C3DHALL12I2C_REG_CTRL1, reg_data[ 0 ] );
    }
    if ( C3DHALL12I2C_OK == error_flag )
    {
        error_flag |= c3dhall12i2c_read_reg ( ctx, C3DHALL12I2C_REG_TEMPERATURE, &reg_data[ 0 ] );
        error_flag |= c3dhall12i2c_read_reg ( ctx, C3DHALL12I2C_REG_X_CHANNEL, &reg_data[ 1 ] );
        error_flag |= c3dhall12i2c_read_reg ( ctx, C3DHALL12I2C_REG_Y_CHANNEL, &reg_data[ 2 ] );
        error_flag |= c3dhall12i2c_read_reg ( ctx, C3DHALL12I2C_REG_Z_CHANNEL, &reg_data[ 3 ] );
        error_flag |= c3dhall12i2c_read_reg ( ctx, C3DHALL12I2C_REG_ANGLE, &reg_data[ 4 ] );
        error_flag |= c3dhall12i2c_read_reg ( ctx, C3DHALL12I2C_REG_RADIUS, &reg_data[ 5 ] );
    }
    if ( C3DHALL12I2C_OK == error_flag )
    {
        raw_data_s = reg_data[ 0 ];
        if ( reg_data[ 0 ] & C3DHALL12I2C_TEMP_SIGN_BIT )
        {
            raw_data_s |= C3DHALL12I2C_TEMP_SIGN_MASK;
        }
        data_out->temperature = raw_data_s / C3DHALL12I2C_TEMP_RES + C3DHALL12I2C_TEMP_OFFSET;
        
        raw_data_s = reg_data[ 1 ];
        if ( reg_data[ 1 ] & C3DHALL12I2C_XYZ_SIGN_BIT )
        {
            raw_data_s |= C3DHALL12I2C_XYZ_SIGN_MASK;
        }
        data_out->x = raw_data_s / C3DHALL12I2C_XYZ_RES_MT;
        
        raw_data_s = reg_data[ 2 ];
        if ( reg_data[ 2 ] & C3DHALL12I2C_XYZ_SIGN_BIT )
        {
            raw_data_s |= C3DHALL12I2C_XYZ_SIGN_MASK;
        }
        data_out->y = raw_data_s / C3DHALL12I2C_XYZ_RES_MT;
        
        raw_data_s = reg_data[ 3 ];
        if ( reg_data[ 3 ] & C3DHALL12I2C_XYZ_SIGN_BIT )
        {
            raw_data_s |= C3DHALL12I2C_XYZ_SIGN_MASK;
        }
        data_out->z = raw_data_s / C3DHALL12I2C_XYZ_RES_MT;
        
        data_out->angle = reg_data[ 4 ] * C3DHALL12I2C_ANGLE_RES_DEG;

        data_out->magnitude = sqrt( reg_data[ 5 ] );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
