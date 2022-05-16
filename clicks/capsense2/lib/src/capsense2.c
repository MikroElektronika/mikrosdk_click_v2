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
 * @file capsense2.c
 * @brief CapSense 2 Click Driver.
 */

#include "capsense2.h"

void capsense2_cfg_setup ( capsense2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->alt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CAPSENSE2_SET_DEV_ADDR;
}

err_t capsense2_init ( capsense2_t *ctx, capsense2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->alt, cfg->alt );

    return I2C_MASTER_SUCCESS;
}

err_t capsense2_default_cfg ( capsense2_t *ctx ) 
{
    err_t error_flag = CAPSENSE2_OK;
    
    capsense2_reset_device ( ctx );
    
    if ( CAPSENSE2_ERROR == capsense2_check_communication ( ctx ) )
    {
        return CAPSENSE2_ERROR;
    }
    error_flag |= capsense2_write_register ( ctx, CAPSENSE2_REG_MULTIPLE_PRESS_CONFIGURATION, 
                                                  CAPSENSE2_MULTIPLE_PRESS_CONFIG_ENABLE | 
                                                  CAPSENSE2_MULTIPLE_PRESS_CONFIG_BUTTONS_2 |
                                                  CAPSENSE2_MULTIPLE_PRESS_CONFIG_GROUP_4 );
    error_flag |= capsense2_write_register ( ctx, CAPSENSE2_REG_CONFIGURATION, 
                                                  CAPSENSE2_CONFIGURATION_BLK_DIG_NOISE );
    error_flag |= capsense2_write_register ( ctx, CAPSENSE2_REG_SLIDER_VELOCITY_CONFIGURATION, 
                                                  CAPSENSE2_SLIDER_VELOCITY_CONFIG_EXTRA_INT_EN | 
                                                  CAPSENSE2_SLIDER_VELOCITY_CONFIG_MAX_INT_1 |
                                                  CAPSENSE2_SLIDER_VELOCITY_CONFIG_SLIDE_TIME_980 );
    error_flag |= capsense2_write_register ( ctx, CAPSENSE2_REG_LED_DIRECTION, 
                                                  CAPSENSE2_LED_DIRECTION_OUTPUT_LED1 | 
                                                  CAPSENSE2_LED_DIRECTION_OUTPUT_LED2 );
    error_flag |= capsense2_write_register ( ctx, CAPSENSE2_REG_SENSOR_LED_LINKING, 
                                                  CAPSENSE2_SENSOR_LED_LINKING_CS1_LED1 | 
                                                  CAPSENSE2_SENSOR_LED_LINKING_CS2_LED2 | 
                                                  CAPSENSE2_SENSOR_LED_LINKING_UP_DOWN_LINK );
    return error_flag;
}

err_t capsense2_generic_write ( capsense2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t capsense2_generic_read ( capsense2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t capsense2_write_register ( capsense2_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t capsense2_read_register ( capsense2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void capsense2_set_reset_pin ( capsense2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t capsense2_get_alert_pin ( capsense2_t *ctx )
{
    return digital_in_read ( &ctx->alt );
}

void capsense2_reset_device ( capsense2_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_10ms ( );
    Delay_10ms ( );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

err_t capsense2_check_communication ( capsense2_t *ctx )
{
    uint8_t vendor_id = 0, manufacturer_id = 0, product_id = 0;
    err_t error_flag = capsense2_read_register ( ctx, CAPSENSE2_REG_VENDOR_ID, &vendor_id );
    error_flag |= capsense2_read_register ( ctx, CAPSENSE2_REG_MANUFACTURER_ID, &manufacturer_id );
    error_flag |= capsense2_read_register ( ctx, CAPSENSE2_REG_PRODUCT_ID, &product_id );
    if ( ( CAPSENSE2_OK == error_flag ) && 
         ( CAPSENSE2_VENDOR_ID == vendor_id ) &&
         ( CAPSENSE2_MANUFACTURER_ID == manufacturer_id ) &&
         ( CAPSENSE2_PRODUCT_ID == product_id ) )
    {
        return CAPSENSE2_OK;
    }
    return CAPSENSE2_ERROR;
}

err_t capsense2_clear_interrupt ( capsense2_t *ctx )
{
    if ( capsense2_get_alert_pin ( ctx ) )
    {
        uint8_t main_control = 0;
        if ( CAPSENSE2_OK == capsense2_read_register ( ctx, CAPSENSE2_REG_MAIN_STATUS_CONTROL, &main_control ) )
        {
            main_control &= ~CAPSENSE2_MAIN_STATUS_CONTROL_INT;
            return capsense2_write_register ( ctx, CAPSENSE2_REG_MAIN_STATUS_CONTROL, main_control );
        }
    }
    return CAPSENSE2_ERROR;
}

// ------------------------------------------------------------------------- END
