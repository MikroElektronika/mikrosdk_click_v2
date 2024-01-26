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
 * @file accelpressure.c
 * @brief AccelPressure Click Driver.
 */

#include "accelpressure.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void accelpressure_cfg_setup ( accelpressure_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cs  = HAL_PIN_NC;
    cfg->an  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->mot = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ACCELPRESSURE_DEVICE_ADDRESS_ACCEL;
}

err_t accelpressure_init ( accelpressure_t *ctx, accelpressure_cfg_t *cfg ) 
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

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->mot, cfg->mot );

    ctx->sensitivity = ACCELPRESSURE_ACC_FSR_SENS_VAL_2G;

    return I2C_MASTER_SUCCESS;
}

err_t accelpressure_default_cfg ( accelpressure_t *ctx ) 
{
    err_t err_flag = ACCELPRESSURE_OK;
    uint8_t data_buf = DUMMY;
    uint8_t device_id = DUMMY;
    
    do 
    {
        err_flag |= accelpressure_get_status( ctx, &data_buf );
        Delay_10ms( );
    }
    while ( !( data_buf & ACCELPRESSURE_ACC_SRC_BOOT_COMPLETED ) );
    
    err_flag |= accelpressure_sw_reset( ctx );
    Delay_100ms( );

    err_flag |= accelpressure_get_device_id( ctx, &device_id );
    if (  ACCELPRESSURE_ACC_DEVICE_ID_VAL == device_id )
    {        
        err_flag |= accelpressure_set_acc_mode( ctx, ACCELPRESSURE_ACC_OP_MODE_STANDBY );
        Delay_10ms( );

        err_flag |= accelpressure_set_fsr( ctx, ACCELPRESSURE_ACC_FSR_SEL_2G );
        Delay_10ms( );

        err_flag |= accelpressure_set_acc_mode( ctx, ACCELPRESSURE_ACC_OP_MODE_ACTIVE );
        Delay_10ms( );

        data_buf = ACCELPRESSURE_PRESS_CTRL1_SBYB | ACCELPRESSURE_PRESS_CTRL1_ALT | ACCELPRESSURE_PRESS_CTRL1_OS32_130MS;
        accelpressure_press_reg_write( ctx, ACCELPRESSURE_PRESS_REG_CTRL1, &data_buf, 1 );
        Delay_10ms( );

        data_buf = ACCELPRESSURE_PRESS_INT_SOURCE_FLAG_TW;
        err_flag |= accelpressure_press_reg_write( ctx, ACCELPRESSURE_PRESS_REG_CTRL2, &data_buf, 1 );
        Delay_10ms( );
        
        data_buf = ACCELPRESSURE_PRESS_CTRL3_INT1_POL_LOW | ACCELPRESSURE_PRESS_CTRL3_INT2_POL_LOW;
        err_flag |= accelpressure_press_reg_write( ctx, ACCELPRESSURE_PRESS_REG_CTRL3, &data_buf, 1 );
        Delay_10ms( );

        data_buf = ACCELPRESSURE_PRESS_CTRL4_INT_EN_DRDY | ACCELPRESSURE_PRESS_CTRL4_INT_EN_PCHG;
        err_flag |= accelpressure_press_reg_write( ctx, ACCELPRESSURE_PRESS_REG_CTRL4, &data_buf, 1 );
        Delay_10ms( );

        data_buf = ACCELPRESSURE_PRESS_CTRL5_INT1_DRDY;
        err_flag |= accelpressure_press_reg_write( ctx, ACCELPRESSURE_PRESS_REG_CTRL5, &data_buf, 1 );
        Delay_10ms( );

        data_buf = ACCELPRESSURE_PRESS_PT_DATA_DR_EVENT_EN | ACCELPRESSURE_PRESS_PT_DATA_PD_EVENT_EN;
        err_flag |= accelpressure_press_reg_write( ctx, ACCELPRESSURE_PRESS_REG_PT_DATA_CFG, &data_buf, 1 );
        Delay_10ms( );

        err_flag |= accelpressure_set_press_mode( ctx, ACCELPRESSURE_PRESS_MODE_BAROMETER );
    }
    else
    {
        err_flag = ACCELPRESSURE_ERROR;
    }
    return err_flag;
}

err_t accelpressure_acc_reg_write ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, ACCELPRESSURE_DEVICE_ADDRESS_ACCEL );
    err_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 1 );
    return err_flag;
}

err_t accelpressure_acc_reg_read ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, ACCELPRESSURE_DEVICE_ADDRESS_ACCEL );
    err_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
    return err_flag;
}

err_t accelpressure_press_reg_write ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, ACCELPRESSURE_DEVICE_ADDRESS_PRESS );
    err_flag |= i2c_master_write( &ctx->i2c, data_buf, len + 1 );
    return err_flag;
}

err_t accelpressure_press_reg_read ( accelpressure_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, ACCELPRESSURE_DEVICE_ADDRESS_PRESS );
    err_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
    return err_flag;
}

err_t accelpressure_get_device_id ( accelpressure_t *ctx, uint8_t *device_id ) 
{
    return accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_WHO_AM_I, device_id, 1 );
}

err_t accelpressure_get_status ( accelpressure_t *ctx, uint8_t *status ) 
{
    return accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_INT_STATUS, status, 1 );
}

err_t accelpressure_sw_reset ( accelpressure_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_SENS_CONFIG1, &data_buf, 1 );
    data_buf |= ACCELPRESSURE_ACC_SW_RESET_BIT_MASK;
    err_flag |= accelpressure_acc_reg_write( ctx, ACCELPRESSURE_ACC_REG_SENS_CONFIG1, &data_buf, 1 );
    return err_flag;
}

err_t accelpressure_set_acc_mode ( accelpressure_t *ctx, uint8_t op_mode ) 
{
    err_t err_flag = ACCELPRESSURE_ERROR;
    if ( ACCELPRESSURE_ACC_OP_MODE_ACTIVE >= op_mode )
    {
        uint8_t data_buf = DUMMY;
        err_flag = accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_SENS_CONFIG1, &data_buf, 1 );
        data_buf &= ACCELPRESSURE_ACC_OP_MODE_BIT_MASK;
        data_buf |= op_mode;
        err_flag |= accelpressure_acc_reg_write( ctx, ACCELPRESSURE_ACC_REG_SENS_CONFIG1, &data_buf, 1 );
    }
    return err_flag;
}

err_t accelpressure_set_fsr ( accelpressure_t *ctx, uint8_t fsr ) 
{
    err_t err_flag = ACCELPRESSURE_ERROR;
    if ( ACCELPRESSURE_ACC_FSR_SEL_16G >= fsr )
    {
        uint8_t data_buf = DUMMY;
        ctx->sensitivity = ACCELPRESSURE_ACC_FSR_SENS_VAL_2G;
        if ( fsr == ACCELPRESSURE_ACC_FSR_SEL_4G )
        {
            ctx->sensitivity = ACCELPRESSURE_ACC_FSR_SENS_VAL_4G;
        }
        else if ( fsr == ACCELPRESSURE_ACC_FSR_SEL_8G )
        {
            ctx->sensitivity = ACCELPRESSURE_ACC_FSR_SENS_VAL_8G;
        }
        else if ( fsr == ACCELPRESSURE_ACC_FSR_SEL_16G )
        {
            ctx->sensitivity = ACCELPRESSURE_ACC_FSR_SENS_VAL_16G;
        }

        fsr <<= 1;
        err_flag = accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_SENS_CONFIG1, &data_buf, 1 );
        data_buf &= ACCELPRESSURE_ACC_FSR_SEL_BIT_MASK;
        data_buf |= fsr;
        err_flag |= accelpressure_acc_reg_write( ctx, ACCELPRESSURE_ACC_REG_SENS_CONFIG1, &data_buf, 1 );
    }
    
    return err_flag;
}

err_t accelpressure_get_axes_data ( accelpressure_t *ctx, accelpressure_axes_t *axes )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t axis_data = DUMMY;
    
    err_t err_flag = accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_OUT_X_LSB, data_buf, 2 );
    axis_data = data_buf[ 1 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 0 ];
    axes->x = ( float ) axis_data * ctx->sensitivity;
    
    err_flag |= accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_OUT_Y_LSB, data_buf, 2 );
    axis_data = data_buf[ 1 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 0 ];
    axes->y = ( float ) axis_data * ctx->sensitivity;
    
    err_flag |= accelpressure_acc_reg_read( ctx, ACCELPRESSURE_ACC_REG_OUT_Z_LSB, data_buf, 2 );
    axis_data = data_buf[ 1 ];
    axis_data <<= 8;
    axis_data |= data_buf[ 0 ];
    axes->z = ( float ) axis_data * ctx->sensitivity;
    
    return err_flag;
}

err_t accelpressure_set_press_mode ( accelpressure_t *ctx, uint8_t op_mode )
{
    err_t err_flag = ACCELPRESSURE_ERROR;
    if ( op_mode <= ACCELPRESSURE_PRESS_MODE_ALTIMETER )
    {
        uint8_t data_buf = DUMMY;
        err_flag = accelpressure_press_reg_read( ctx, ACCELPRESSURE_PRESS_REG_CTRL1, &data_buf, 1 );
        data_buf &= ACCELPRESSURE_PRESS_CTRL1_ALT_BITMASK;
        data_buf |= op_mode << 7;
        err_flag |= accelpressure_press_reg_write( ctx, ACCELPRESSURE_PRESS_REG_CTRL1, &data_buf, 1 );
    }
    return err_flag;
}

err_t accelpressure_get_drdy_status ( accelpressure_t *ctx, uint8_t *drdy )
{
    err_t err_flag = accelpressure_press_reg_read( ctx, ACCELPRESSURE_PRESS_REG_DR_STATUS, drdy, 1 );
    *drdy &= ACCELPRESSURE_PRESS_STATUS_FLAG_PDR;
    return err_flag;
}

err_t accelpressure_get_pressure ( accelpressure_t *ctx, float *pressure )
{
    uint8_t data_buf[ 3 ] = { 0 };
    uint32_t press_data = DUMMY;

    err_t err_flag = accelpressure_press_reg_read( ctx, ACCELPRESSURE_PRESS_REG_OUT_P_MSB, data_buf, 3 );
    press_data = data_buf[ 0 ];
    press_data <<= 8;
    press_data |= data_buf[ 1 ];
    press_data <<= 8;
    press_data |= data_buf[ 2 ];
    press_data >>= 4;

    *pressure = press_data;
    *pressure *= ACCELPRESSURE_PRESS_PRESSURE_SENS;
    *pressure /= ACCELPRESSURE_PRESS_CONVERT_PA_TO_MBAR;

    return err_flag;
}

err_t accelpressure_get_temperature ( accelpressure_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t temp_data = DUMMY;

    err_t err_flag = accelpressure_press_reg_read( ctx, ACCELPRESSURE_PRESS_REG_OUT_T_MSB, data_buf, 2 );
    temp_data = data_buf[ 0 ];
    temp_data <<= 8;
    temp_data |= data_buf[ 1 ];
    temp_data >>= 4;

    *temperature = temp_data;
    *temperature *= ACCELPRESSURE_PRESS_TEMP_SENS;

    return err_flag;
}

uint8_t accelpressure_get_mot_det ( accelpressure_t *ctx )
{
    return digital_in_read( &ctx->mot );
}

// ------------------------------------------------------------------------- END
