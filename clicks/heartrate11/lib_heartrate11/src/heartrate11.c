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
 * @file heartrate11.c
 * @brief Heart Rate 11 Click Driver.
 */

#include "heartrate11.h"

void heartrate11_cfg_setup ( heartrate11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HEARTRATE11_DEVICE_ADDRESS;
}

err_t heartrate11_init ( heartrate11_t *ctx, heartrate11_cfg_t *cfg ) 
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

err_t heartrate11_default_cfg ( heartrate11_t *ctx ) 
{
    err_t error_flag = HEARTRATE11_OK;
    error_flag |= heartrate11_reset_device ( ctx );
    Delay_100ms ( );
    error_flag |= heartrate11_write_register ( ctx, HEARTRATE11_REG_MAIN_CTRL_1, HEARTRATE11_PS_SAI_OFF | 
                                                                                 HEARTRATE11_HR_MODE | 
                                                                                 HEARTRATE11_PPG_PS_ON );
    error_flag |= heartrate11_write_register ( ctx, HEARTRATE11_REG_INT_CFG_1, HEARTRATE11_PPG_INT_ON );
    error_flag |= heartrate11_set_led_current ( ctx, HEARTRATE11_IR_LED, HEARTRATE11_IR_LED_DEFAULT_CURRENT );
    error_flag |= heartrate11_write_register ( ctx, HEARTRATE11_REG_PPG_PS_GAIN, HEARTRATE11_PPG_PS_GAIN_1 | 
                                                                                 HEARTRATE11_PPG_PS_GAIN_RESERVED );
    error_flag |= heartrate11_write_register ( ctx, HEARTRATE11_REG_PPG_AVG, HEARTRATE11_PPG_AVG_32 | 
                                                                             HEARTRATE11_PPG_AVG_RESERVED );
    error_flag |= heartrate11_write_register ( ctx, HEARTRATE11_REG_PPG_PWIDTH_PERIOD, HEARTRATE11_PPG_PWIDTH_247US | 
                                                                                       HEARTRATE11_PPG_RATE_1MS );
    return error_flag;
}

err_t heartrate11_generic_write ( heartrate11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t heartrate11_generic_read ( heartrate11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t heartrate11_write_register ( heartrate11_t *ctx, uint8_t reg, uint8_t data_in )
{
    return heartrate11_generic_write ( ctx, reg, &data_in, 1 );
}

err_t heartrate11_read_register ( heartrate11_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return heartrate11_generic_read ( ctx, reg, data_out, 1 );
}

uint8_t heartrate11_get_int_pin ( heartrate11_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t heartrate11_reset_device ( heartrate11_t *ctx )
{
    return heartrate11_write_register ( ctx, HEARTRATE11_REG_MAIN_CTRL_0, HEARTRATE11_SW_RESET );
}

err_t heartrate11_set_led_current ( heartrate11_t *ctx, uint8_t led, float current )
{
    if ( ( ( HEARTRATE11_RED_LED == led ) && ( current > HEARTRATE11_RED_LED_MAX_CURRENT ) ) ||
         ( led > HEARTRATE11_RED_LED ) || ( current > HEARTRATE11_PS_IR_LED_MAX_CURRENT ) )
    {
        return HEARTRATE11_ERROR;
    }
    uint16_t raw_curr;
    uint8_t reg;
    if ( HEARTRATE11_RED_LED == led )
    {
        raw_curr = ( uint16_t ) ( ( current / HEARTRATE11_RED_LED_MAX_CURRENT ) * HEARTRATE11_RED_LED_CURRENT_RES + 
                                  HEARTRATE11_ROUND_TO_NEAREST_INT );
        raw_curr &= HEARTRATE11_RED_LED_CURRENT_RES;
        reg = HEARTRATE11_REG_PPG_RLED_CURR_0;
    }
    else
    {
        raw_curr = ( uint16_t ) ( ( current / HEARTRATE11_PS_IR_LED_MAX_CURRENT ) * HEARTRATE11_PS_IR_LED_CURRENT_RES + 
                                  HEARTRATE11_ROUND_TO_NEAREST_INT );
        raw_curr &= HEARTRATE11_PS_IR_LED_CURRENT_RES;
        if ( HEARTRATE11_PS_LED == led )
        {
            reg = HEARTRATE11_REG_PS_LED_CURR_0;
        }
        else
        {
            reg = HEARTRATE11_REG_PPG_IRLED_CURR_0;
        }
    }
    uint8_t data_buf[ 2 ];
    data_buf[ 0 ] = ( uint8_t ) ( raw_curr & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( raw_curr >> 8 ) & 0xFF );
    return heartrate11_generic_write ( ctx, reg, data_buf, 2 );
}

err_t heartrate11_read_proximity ( heartrate11_t *ctx, uint16_t *proximity )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = heartrate11_generic_read ( ctx, HEARTRATE11_REG_PS_DATA_0, data_buf, 2 );
    *proximity = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    return error_flag;
}

err_t heartrate11_read_fifo ( heartrate11_t *ctx, uint32_t *fifo_data )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t error_flag = heartrate11_generic_read ( ctx, HEARTRATE11_REG_FIFO_DATA, data_buf, 3 );
    *fifo_data = ( ( uint32_t ) data_buf[ 2 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    return error_flag;
}

// ------------------------------------------------------------------------- END
