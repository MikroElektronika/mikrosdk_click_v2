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
 * @file ledring2.c
 * @brief LED Ring 2 Click Driver.
 */

#include "ledring2.h"

void ledring2_cfg_setup ( ledring2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->vsy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDRING2_LED_GROUP_U1_LED_1_18;
}

err_t ledring2_init ( ledring2_t *ctx, ledring2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->vsy, cfg->vsy );

    digital_out_low( &ctx->vsy );

    return I2C_MASTER_SUCCESS;
}

err_t ledring2_default_cfg ( ledring2_t *ctx ) 
{   
    err_t err_flag = ledring2_enable( ctx );
    
    err_flag |= ledring2_set_all_led_state( ctx, LEDRING2_LED_ON );
    
    ledring2_set_vsync( ctx );
    return err_flag;
}

err_t ledring2_set_slave_address ( ledring2_t *ctx, uint8_t slave_address ) 
{
    return i2c_master_set_slave_address( &ctx->i2c, slave_address );
}

err_t ledring2_write_reg ( ledring2_t *ctx, uint8_t led_group, uint16_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t slave_address;
    uint8_t data_buf[ 256 ] = { 0 };
    
    slave_address = led_group; 
    slave_address |= ( uint8_t ) ( ( reg >> 8 ) & LEDRING2_8_9_BIT_MASK );
    ledring2_set_slave_address( ctx, slave_address );
    
    data_buf[ 0 ] = ( uint8_t ) reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t ledring2_read_reg ( ledring2_t *ctx, uint8_t led_group, uint16_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t slave_address;
    uint8_t data_buf[ 1 ] = { 0 };
    
    slave_address = led_group; 
    slave_address |= ( uint8_t ) ( ( reg >> 8 ) & LEDRING2_8_9_BIT_MASK );
    ledring2_set_slave_address( ctx, slave_address );
    
    data_buf[ 0 ] = ( uint8_t ) reg;
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 1, data_out, len );
}

void ledring2_set_vsync ( ledring2_t *ctx ) 
{
    digital_out_low( &ctx->vsy );
    Delay_500us( );
    digital_out_high( &ctx->vsy );
    Delay_500us();
    digital_out_low( &ctx->vsy );
    Delay_500us( );
}

err_t ledring2_enable ( ledring2_t *ctx ) 
{
    uint8_t data_buf = LEDRING2_LED_ENABLE;
    err_t err_flag = ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U1_LED_1_18, LEDRING2_REG_CHIP_EN, &data_buf, 1 );
    err_flag |= ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U2_LED_19_36, LEDRING2_REG_CHIP_EN, &data_buf, 1 );
    err_flag |= ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U3_LED_37_54, LEDRING2_REG_CHIP_EN, &data_buf, 1 );
    return err_flag;
}

err_t ledring2_disable ( ledring2_t *ctx ) 
{
    uint8_t data_buf = LEDRING2_LED_DISABLE;
    err_t err_flag = ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U1_LED_1_18, LEDRING2_REG_CHIP_EN, &data_buf, 1 );
    err_flag |= ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U2_LED_19_36, LEDRING2_REG_CHIP_EN, &data_buf, 1 );
    err_flag |= ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U3_LED_37_54, LEDRING2_REG_CHIP_EN, &data_buf, 1 );
    return err_flag;
}

err_t ledring2_set_all_led_state ( ledring2_t *ctx, ledring2_led_state_t led_state ) 
{
    err_t err_flag;
    uint8_t data_buf[ 7 ] = { 0 };
    
    if ( LEDRING2_LED_ON == led_state )
    {
        memset( data_buf, 0xFF, 6 );
    }
    err_flag = ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U1_LED_1_18, LEDRING2_REG_DOT_ONOFF0, &data_buf, 6 );
    err_flag |= ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U2_LED_19_36, LEDRING2_REG_DOT_ONOFF0, &data_buf, 6 );
    err_flag |= ledring2_write_reg( ctx, LEDRING2_LED_GROUP_U3_LED_37_54, LEDRING2_REG_DOT_ONOFF0, &data_buf, 6 );
    return err_flag;
}

err_t ledring2_set_led_pos_state ( ledring2_t *ctx, uint8_t led_pos, ledring2_led_state_t led_state ) 
{
    err_t err_flag;
    uint8_t slave_address;
    uint16_t reg;
    uint8_t data_buf;
    
    if ( ( led_pos < 1 ) || ( led_pos > 54 ) )
    {
        err_flag = LEDRING2_ERROR;
    }
    else
    {
        if ( led_pos > 36 )
        {
            slave_address = LEDRING2_LED_GROUP_U3_LED_37_54;
            led_pos -= 36;
        }
        else if ( led_pos > 18 )
        {
            slave_address = LEDRING2_LED_GROUP_U2_LED_19_36;
            led_pos -= 18;
        }
        else
        {
            slave_address = LEDRING2_LED_GROUP_U1_LED_1_18;
        }
        
        if ( led_pos > 16 )
        {
            reg = LEDRING2_REG_DOT_ONOFF5;
            led_pos -= 17;
        }
        else if ( led_pos > 9 )
        {
            reg = LEDRING2_REG_DOT_ONOFF4;
            led_pos -= 9;
        }
        else if ( led_pos < 9 )
        {
            reg = LEDRING2_REG_DOT_ONOFF0;
            led_pos -= 1;
        }
        else
        {
            reg = LEDRING2_REG_DOT_ONOFF1;
            led_pos = 0;
        }
    }
    
    err_flag |= ledring2_read_reg( ctx, slave_address, reg, &data_buf, 1 );
    if ( LEDRING2_LED_ON == led_state )
    {
        data_buf |= ( uint8_t ) ( 1 << led_pos );
    }
    else
    {
        data_buf &= ~( ( uint8_t ) ( 1 << led_pos ) );
    }
    err_flag = ledring2_write_reg( ctx, slave_address, reg, &data_buf, 1 );
    return err_flag;
}

err_t ledring2_set_led_brightness ( ledring2_t *ctx, uint8_t led_pos, uint16_t led_brightness ) 
{
    err_t err_flag;
    uint8_t slave_address;
    uint16_t reg;
    uint8_t data_buf[ 2 ] = { 0 };
    
    data_buf[ 0 ] = ( uint8_t ) led_brightness;
    data_buf[ 1 ] = ( uint8_t ) ( led_brightness >> 8 );
    if ( ( led_pos < 1 ) || ( led_pos > 54 ) )
    {
        err_flag = LEDRING2_ERROR;    
    }
    else
    {   
        slave_address = LEDRING2_LED_GROUP_U3_LED_37_54;
        if ( led_pos > 45 )
        {
            reg = LEDRING2_REG_PWM_BRI54 + ( led_pos - 46 ) * 2;
        }
        else if ( led_pos > 36 )
        {
            reg = LEDRING2_REG_PWM_BRI0 + ( led_pos - 37 ) * 2;
        }
        else if ( led_pos > 27 )
        {
            slave_address = LEDRING2_LED_GROUP_U2_LED_19_36;
            reg = LEDRING2_REG_PWM_BRI54 + ( led_pos - 28 ) * 2;
        }
        else if ( led_pos > 18 )
        {
            slave_address = LEDRING2_LED_GROUP_U2_LED_19_36;
            reg = LEDRING2_REG_PWM_BRI0 + ( led_pos - 19 ) * 2;
        }
        else if ( led_pos > 9 )
        {
            slave_address = LEDRING2_LED_GROUP_U1_LED_1_18;
            reg = LEDRING2_REG_PWM_BRI54 + ( led_pos - 10 ) * 2;
        }
        else
        {
            slave_address = LEDRING2_LED_GROUP_U1_LED_1_18;
            reg = LEDRING2_REG_PWM_BRI0 + ( led_pos - 1 ) * 2;
        }
    }
    
    uint8_t rx_buf = 0;
    err_flag |= ledring2_read_reg( ctx, slave_address, LEDRING2_REG_DEV_INITIAL, &rx_buf, 1 );
    rx_buf >>= 1;
    rx_buf &= LEDRING2_OP_MODE_3;
    if ( LEDRING2_OP_MODE_3 != rx_buf )
    {
        data_buf[ 1 ] = ( uint8_t ) led_brightness;
        reg++;
    }
    err_flag = ledring2_write_reg( ctx, slave_address, reg, data_buf, 2 );
    return err_flag;
}

// ------------------------------------------------------------------------- END
