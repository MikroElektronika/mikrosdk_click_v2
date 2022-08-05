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
 * @file ldctouch.c
 * @brief LDC Touch Click Driver.
 */

#include "ldctouch.h"

void ldctouch_cfg_setup ( ldctouch_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->s2 = HAL_PIN_NC;
    cfg->s0 = HAL_PIN_NC;
    cfg->s1 = HAL_PIN_NC;
    cfg->s3 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LDCTOUCH_DEVICE_ADDRESS;
}

err_t ldctouch_init ( ldctouch_t *ctx, ldctouch_cfg_t *cfg ) 
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

    digital_in_init( &ctx->s0, cfg->s0 );
    digital_in_init( &ctx->s1, cfg->s1 );
    digital_in_init( &ctx->s2, cfg->s2 );
    digital_in_init( &ctx->s3, cfg->s3 );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t ldctouch_default_cfg ( ldctouch_t *ctx ) 
{
    err_t error_flag = LDCTOUCH_OK;
    if ( LDCTOUCH_ERROR == ldctouch_check_communication ( ctx ) )
    {
        return LDCTOUCH_ERROR;
    }
    error_flag |= ldctouch_set_operation_mode ( ctx, LDCTOUCH_MODE_FULL_RESET );
    Delay_100ms ( );
    error_flag |= ldctouch_set_operation_mode ( ctx, LDCTOUCH_MODE_CONFIG );
#if ( LDCTOUCH_BUTTON_MODE == LDCTOUCH_BUTTON_MODE_FINGER )
    error_flag |= ldctouch_write_register ( ctx, LDCTOUCH_REG_OPOL_DPOL, LDCTOUCH_OPOL3_ACTIVE_HIGH |
                                                                         LDCTOUCH_OPOL2_ACTIVE_HIGH | 
                                                                         LDCTOUCH_OPOL1_ACTIVE_HIGH | 
                                                                         LDCTOUCH_OPOL0_ACTIVE_HIGH | 
                                                                         LDCTOUCH_DPOL3_DATA_DECREASES | 
                                                                         LDCTOUCH_DPOL2_DATA_DECREASES | 
                                                                         LDCTOUCH_DPOL1_DATA_DECREASES | 
                                                                         LDCTOUCH_DPOL0_DATA_DECREASES );
#else
    error_flag |= ldctouch_write_register ( ctx, LDCTOUCH_REG_OPOL_DPOL, LDCTOUCH_OPOL3_ACTIVE_HIGH |
                                                                         LDCTOUCH_OPOL2_ACTIVE_HIGH | 
                                                                         LDCTOUCH_OPOL1_ACTIVE_HIGH | 
                                                                         LDCTOUCH_OPOL0_ACTIVE_HIGH | 
                                                                         LDCTOUCH_DPOL3_DATA_INCREASES | 
                                                                         LDCTOUCH_DPOL2_DATA_INCREASES | 
                                                                         LDCTOUCH_DPOL1_DATA_INCREASES | 
                                                                         LDCTOUCH_DPOL0_DATA_INCREASES );
#endif
    error_flag |= ldctouch_write_register ( ctx, LDCTOUCH_REG_EN, LDCTOUCH_EN_CH3_LP | 
                                                                  LDCTOUCH_EN_CH2_LP | 
                                                                  LDCTOUCH_EN_CH1_LP | 
                                                                  LDCTOUCH_EN_CH0_LP | 
                                                                  LDCTOUCH_EN_CH3_NP | 
                                                                  LDCTOUCH_EN_CH2_NP | 
                                                                  LDCTOUCH_EN_CH1_NP | 
                                                                  LDCTOUCH_EN_CH0_NP );
    error_flag |= ldctouch_set_operation_mode ( ctx, LDCTOUCH_MODE_NORMAL );
    return error_flag;
}

err_t ldctouch_generic_write ( ldctouch_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ldctouch_generic_read ( ldctouch_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t ldctouch_write_register ( ldctouch_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ldctouch_generic_write ( ctx, reg, &data_in, 1 );
}

err_t ldctouch_read_register ( ldctouch_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ldctouch_generic_read ( ctx, reg, data_out, 1 );
}

uint8_t ldctouch_get_s0_pin ( ldctouch_t *ctx )
{
    return digital_in_read ( &ctx->s0 );
}

uint8_t ldctouch_get_s1_pin ( ldctouch_t *ctx )
{
    return digital_in_read ( &ctx->s1 );
}

uint8_t ldctouch_get_s2_pin ( ldctouch_t *ctx )
{
    return digital_in_read ( &ctx->s2 );
}

uint8_t ldctouch_get_s3_pin ( ldctouch_t *ctx )
{
    return digital_in_read ( &ctx->s3 );
}

uint8_t ldctouch_get_int_pin ( ldctouch_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ldctouch_check_communication ( ldctouch_t *ctx )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( LDCTOUCH_OK == ldctouch_generic_read ( ctx, LDCTOUCH_REG_MANUFACTURER_ID_LSB, data_buf, 4 ) )
    {
        if ( ( LDCTOUCH_MANUFACTURER_ID_LSB == data_buf[ 0 ] ) &&
             ( LDCTOUCH_MANUFACTURER_ID_MSB == data_buf[ 1 ] ) &&
             ( LDCTOUCH_DEVICE_ID_LSB == data_buf[ 2 ] ) &&
             ( LDCTOUCH_DEVICE_ID_MSB == data_buf[ 3 ] ) )
        {
            return LDCTOUCH_OK;
        }
    }
    return LDCTOUCH_ERROR;
}

err_t ldctouch_set_operation_mode ( ldctouch_t *ctx, uint8_t mode )
{
    err_t error_flag = LDCTOUCH_OK;
    uint8_t status;
    if ( LDCTOUCH_MODE_NORMAL == mode )
    {
        error_flag |= ldctouch_write_register ( ctx, LDCTOUCH_REG_RESET, mode );
        Delay_10ms ( );
        error_flag |= ldctouch_read_register ( ctx, LDCTOUCH_REG_STATUS, &status );
        if ( LDCTOUCH_STATUS_READY_TO_WRITE != ( status & LDCTOUCH_STATUS_READY_TO_WRITE ) )
        {
            return error_flag;
        }
    }
    else if ( LDCTOUCH_MODE_CONFIG == mode )
    {
        error_flag |= ldctouch_write_register ( ctx, LDCTOUCH_REG_RESET, mode );
        Delay_10ms ( );
        error_flag |= ldctouch_read_register ( ctx, LDCTOUCH_REG_STATUS, &status );
        if ( status & LDCTOUCH_STATUS_READY_TO_WRITE )
        {
            return error_flag;
        }
    }
    else if ( LDCTOUCH_MODE_FULL_RESET == mode )
    {
        error_flag |= ldctouch_write_register ( ctx, LDCTOUCH_REG_RESET, mode );
        Delay_100ms ( );
        error_flag |= ldctouch_read_register ( ctx, LDCTOUCH_REG_STATUS, &status );
        if ( status & LDCTOUCH_STATUS_CHIP_READY )
        {
            return error_flag;
        }
    }
    return LDCTOUCH_ERROR;
}

err_t ldctouch_get_data ( ldctouch_t *ctx, ldctouch_data_t *button_data )
{
    uint8_t data_buf[ 10 ] = { 0 };
    if ( LDCTOUCH_OK == ldctouch_generic_read ( ctx, LDCTOUCH_REG_STATUS, data_buf, 10 ) )
    {
        button_data->status = data_buf[ 0 ];
        button_data->out_state = data_buf[ 1 ];
        button_data->ch0_raw_button = ( ( ( int16_t ) data_buf[ 3 ] << 12 ) >> 4 ) | data_buf[ 2 ];
        button_data->ch1_raw_button = ( ( ( int16_t ) data_buf[ 5 ] << 12 ) >> 4 ) | data_buf[ 4 ];
        button_data->ch2_raw_button = ( ( ( int16_t ) data_buf[ 7 ] << 12 ) >> 4 ) | data_buf[ 6 ];
        button_data->ch3_raw_button = ( ( ( int16_t ) data_buf[ 9 ] << 12 ) >> 4 ) | data_buf[ 8 ];
        return LDCTOUCH_OK;
    }
    return LDCTOUCH_ERROR;
}

// ------------------------------------------------------------------------- END
