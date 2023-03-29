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
 * @file proximity17.c
 * @brief Proximity 17 Click Driver.
 */

#include "proximity17.h"

void proximity17_cfg_setup ( proximity17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY17_DEVICE_ADDRESS;
}

err_t proximity17_init ( proximity17_t *ctx, proximity17_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;
    digital_out_t scl, sda;
    digital_out_init ( &sda, cfg->sda );
    digital_out_high ( &sda );
    digital_out_init ( &scl, cfg->scl );
    digital_out_high ( &scl );
    Delay_1ms ( );

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
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t proximity17_default_cfg ( proximity17_t *ctx ) 
{
    err_t error_flag = PROXIMITY17_OK;
    if ( PROXIMITY17_ERROR == proximity17_check_communication ( ctx ) )
    {
        return PROXIMITY17_ERROR;
    }
    error_flag |= proximity17_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_ENABLE, PROXIMITY17_ENABLE_PON );
    Delay_100ms ( );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_CFG8, PROXIMITY17_PDSELECT_BOTH_PDIODE );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_PCFG0, PROXIMITY17_PGAIN_1X | 
                                                                           PROXIMITY17_PPULSE_DEFAULT );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_CFG6, PROXIMITY17_APC_ENABLE );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_PCFG1, PROXIMITY17_PPULSE_LEN_8US | 
                                                                           PROXIMITY17_PLDRIVE_7mA );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_STATUS, PROXIMITY17_STATUS_CLEAR_ALL );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_INTENAB, PROXIMITY17_INTENAB_CIEN );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_CALIBCFG, PROXIMITY17_BINSRCH_TARGET_15 | 
                                                                              PROXIMITY17_CALIBCFG_RESERVED | 
                                                                              PROXIMITY17_AUTO_OFFSET_ADJ | 
                                                                              PROXIMITY17_PROX_AVG_DISABLE );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_CALIB, PROXIMITY17_START_OFFSET_CAL );
    uint8_t status = 0;
    while ( PROXIMITY17_CALIB_FINISHED != ( status & PROXIMITY17_CALIB_FINISHED ) )
    {
        error_flag |= proximity17_read_register ( ctx, PROXIMITY17_REG_CALIBSTAT, &status );
        Delay_100ms ( );
    }
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_INTENAB, PROXIMITY17_INTENAB_DISABLE );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_STATUS, PROXIMITY17_STATUS_CLEAR_ALL );
    error_flag |= proximity17_write_register ( ctx, PROXIMITY17_REG_ENABLE, PROXIMITY17_ENABLE_PEN | 
                                                                            PROXIMITY17_ENABLE_PON );
    Delay_100ms ( );
    return error_flag;
}

err_t proximity17_generic_write ( proximity17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t proximity17_generic_read ( proximity17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t proximity17_write_register ( proximity17_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return proximity17_generic_write( ctx, reg, &data_in, 1 );
}

err_t proximity17_read_register ( proximity17_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return proximity17_generic_read( ctx, reg, data_out, 1 );
}

err_t proximity17_check_communication ( proximity17_t *ctx )
{
    uint8_t dev_id;
    for ( uint8_t to_cnt = 0; to_cnt < 10; to_cnt++ )
    {
        if ( PROXIMITY17_OK == proximity17_read_register ( ctx, PROXIMITY17_REG_ID, &dev_id ) )
        {
            if ( PROXIMITY17_DEVICE_ID == dev_id )
            {
                return PROXIMITY17_OK;
            }
        }
        Delay_100ms ( );
    }
    return PROXIMITY17_ERROR;
}

err_t proximity17_soft_reset ( proximity17_t *ctx )
{
    return proximity17_write_register ( ctx, PROXIMITY17_REG_SOFTRST, PROXIMITY17_SOFT_RESET );
}

err_t proximity17_read_proximity ( proximity17_t *ctx, uint16_t *prox_data )
{
    err_t error_flag = PROXIMITY17_OK;
    uint8_t rx_buf[ 2 ] = { 0 };
    error_flag |= proximity17_generic_read( ctx, PROXIMITY17_REG_PDATAL, rx_buf, 2 );
    *prox_data = ( ( uint16_t ) rx_buf[ 1 ] << 8 ) | rx_buf[ 0 ];
    return error_flag;
}

uint8_t proximity17_get_int_pin ( proximity17_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
