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
 * @file press.c
 * @brief PRESS Click Driver.
 */

#include "press.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void press_cfg_setup ( press_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESS_DEVICE_ADDRESS;
}

err_t press_init ( press_t *ctx, press_cfg_t *cfg ) 
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

err_t press_default_cfg ( press_t *ctx ) 
{
    uint8_t device_who_am_i = DUMMY;
    err_t err_flag = press_sw_reset( ctx );
    Delay_100ms( );
    
    err_flag |= press_reg_read( ctx, PRESS_REG_WHO_AM_I, &device_who_am_i );
    if ( PRESS_WHO_AM_I == device_who_am_i )
    {
        err_flag |= press_reg_write( ctx, PRESS_REG_CTRL_REG1, PRESS_ODR_100HZ | 
                                                               PRESS_AVG_32 );
    
        err_flag |= press_reg_write( ctx, PRESS_REG_CTRL_REG2, PRESS_BOOT_NORMAL_MODE | 
                                                               PRESS_FS_MODE_2_4060HPA | 
                                                               PRESS_LFPF_CFG_ODR_4 | 
                                                               PRESS_DISABLE_LPFP | 
                                                               PRESS_BDU_CONTINUOUS | 
                                                               PRESS_ONESHOT_IDLE );
        
        err_flag |= press_config_ah_qvar( ctx, PRESS_AH_QVAR_DISABLE );
        Delay_100ms( );
    }
    else
    {
        err_flag = PRESS_ERROR;
    }
    return err_flag;
}

err_t press_generic_write ( press_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t press_generic_read ( press_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t press_reg_write ( press_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return press_generic_write( ctx, reg, &data_in, 1 );
}

err_t press_reg_read ( press_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return press_generic_read( ctx, reg, data_out, 1 );
}

err_t press_sw_reset ( press_t *ctx )
{
    return press_reg_write( ctx, PRESS_REG_CTRL_REG2, PRESS_SW_RESET );
}

err_t press_config_ah_qvar ( press_t *ctx, uint8_t ah_qvar_en )
{
    uint8_t tmp = DUMMY;
    err_t err_flag = press_reg_read( ctx, PRESS_REG_CTRL_REG3, &tmp );
    tmp &= ~PRESS_REBOOT_AH_QVAR_EN;
    if ( PRESS_AH_QVAR_ENABLE & ah_qvar_en )
    {
        tmp |= PRESS_REBOOT_AH_QVAR_EN;
    }
    err_flag |= press_reg_write( ctx, PRESS_REG_CTRL_REG3, tmp );
    return err_flag;
}

err_t press_get_raw_data ( press_t *ctx, uint32_t *press_data, uint32_t *qvar_data, uint16_t *temp_data )
{
    uint8_t status = DUMMY, fs_mode = DUMMY, ah_qvar_en = DUMMY;
    uint32_t tmp = DUMMY;
    err_t err_flag = press_reg_read( ctx, PRESS_REG_CTRL_REG2, &fs_mode );
    err_flag |= press_reg_read( ctx, PRESS_REG_CTRL_REG3, &ah_qvar_en );
    err_flag |= press_reg_read( ctx, PRESS_REG_STATUS, &status );
    
    uint8_t data_buf[ 5 ] = { 0 };
    if ( ( status & PRESS_STATUS_TEMP_AVAILABLE ) && ( status & PRESS_STATUS_PRESS_AVAILABLE ) )
    {
        err_flag |= press_generic_read ( ctx, PRESS_REG_PRESSURE_OUT_XL, data_buf, 5 );
        tmp = data_buf[ 2 ];
        tmp <<= 8;
        tmp |= data_buf[ 1 ];
        tmp <<= 8;
        tmp |= data_buf[ 0 ];
        if ( PRESS_REBOOT_AH_QVAR_EN & ah_qvar_en )
        {
            *qvar_data = tmp;
            *press_data = DUMMY;
        }
        else
        {
            *qvar_data = DUMMY;
            *press_data = tmp;
            if ( !( fs_mode & PRESS_FS_MODE_2_4060HPA ) )
            {
                *press_data >>= 1;
            }
            *temp_data = data_buf[ 4 ];
            *temp_data <<= 8;
            *temp_data |= data_buf[ 3 ];
        }
    }
    else
    {
        err_flag = PRESS_ERROR;
    }
    return err_flag;
}

err_t press_get_measurement_data ( press_t *ctx, float *pressure, float *temperature )
{
    uint32_t press_data = DUMMY, qvar_data = DUMMY;
    uint16_t temp_data = DUMMY;
    err_t err_flag = press_get_raw_data( ctx, &press_data, &qvar_data, &temp_data );
    *pressure = ( ( float ) press_data ) / PRESS_LSB_HPA_FS_MODE_2048;
    *temperature = ( ( float ) temp_data ) / PRESS_TEMP_SENS;
    return err_flag;
}

err_t press_get_ah_qvar_data ( press_t *ctx, float *ah_qvar )
{
    uint32_t press_data = DUMMY, qvar_data = DUMMY;
    uint16_t temp_data = DUMMY;
    uint8_t ah_qvar_en = DUMMY;
    err_t err_flag = press_reg_read( ctx, PRESS_REG_CTRL_REG3, &ah_qvar_en );
    if ( PRESS_REBOOT_AH_QVAR_EN & ah_qvar_en )
    {
        err_flag |= press_get_raw_data( ctx, &press_data, &qvar_data, &temp_data );
        *ah_qvar = ( ( float ) qvar_data ) / PRESS_QVAR_GAIN_LSB_MV;
    }
    else
    {
        err_flag = PRESS_ERROR;
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END
