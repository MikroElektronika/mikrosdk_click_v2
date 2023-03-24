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
 * @file leddriver18.c
 * @brief LED Driver 18 Click Driver.
 */

#include "leddriver18.h"

/**
 * @brief LED Driver 18 Click PWM set value data.
 * @details Set PWM data value of LED Driver 18 Click driver.
 */
static uint16_t dev_led_pwm_data[ 24 ] = { 0 };

void leddriver18_cfg_setup ( leddriver18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDDRIVER18_DEVICE_ADDRESS;
}

err_t leddriver18_init ( leddriver18_t *ctx, leddriver18_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->sck, cfg->sck );
    digital_out_init( &ctx->mosi, cfg->mosi );
    digital_out_init( &ctx->en, cfg->en );

    digital_out_high( &ctx->rst );

    return I2C_MASTER_SUCCESS;
}

err_t leddriver18_default_cfg ( leddriver18_t *ctx ) 
{
    err_t error_flag = LEDDRIVER18_OK;
    
    leddriver18_enable_output( ctx );
    
    error_flag = leddriver18_set_cc_output( ctx, LEDDRIVER18_CURRENT_30_mA );
    
    leddriver18_write_config( ctx );

    return error_flag;
}

err_t leddriver18_generic_write ( leddriver18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t leddriver18_generic_read ( leddriver18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t leddriver18_set_output_pwm ( uint8_t out_num, float pwm_value )
{
    err_t error_flag = LEDDRIVER18_OK;
    uint16_t temp_data;
    
    if ( pwm_value > 100 || out_num > LEDDRIVER18_MAX_OUTPUT_NUM )
    {
        error_flag = LEDDRIVER18_ERROR;
    }
    else 
    {
        temp_data = ( uint16_t ) ( ( pwm_value / 100 ) * LEDDRIVER18_PWM_MAX_VALUE );
        
        dev_led_pwm_data[ out_num ] = temp_data;
    }
    
    return error_flag;
}

float leddriver18_get_output_pwm ( uint8_t out_num )
{
    uint16_t temp_data;
    float pwm_value;
    
    temp_data = dev_led_pwm_data[ out_num ];
    
    pwm_value = ( ( float ) temp_data / ( LEDDRIVER18_PWM_MAX_VALUE + 1 ) ) * 100;
    
    return pwm_value;
}

void leddriver18_write_config ( leddriver18_t *ctx )
{
    digital_out_low( &ctx->cs );
    
    for ( int8_t n_cnt = LEDDRIVER18_MAX_OUTPUT_NUM - 1; n_cnt >= 0; n_cnt-- )
    {
        for ( int8_t n_bit = LEDDRIVER18_MAX_RES_BITS - 1; n_bit >= 0; n_bit-- )
        {
            digital_out_low( &ctx->sck );
            
            if ( dev_led_pwm_data[ n_cnt ] & ( 0x0001 << n_bit) )
            {
                digital_out_high( &ctx->mosi );
            }
            else
            {
                digital_out_low( &ctx->mosi );
            }
            
            digital_out_high( &ctx->sck );
        }
    }
    
    digital_out_low( &ctx->sck );
    digital_out_high( &ctx->cs );
    digital_out_low( &ctx->cs );
}

void leddriver18_enable_output ( leddriver18_t *ctx )
{
    digital_out_low( &ctx->en );
}

void leddriver18_disable_output ( leddriver18_t *ctx )
{
    digital_out_high( &ctx->en );
}

err_t leddriver18_set_cc_output ( leddriver18_t *ctx, uint8_t current_limit )
{
    err_t error_flag = LEDDRIVER18_OK;
    
    error_flag = leddriver18_generic_write( ctx, LEDDRIVER18_WRITE_TO_RDAC, &current_limit, 1 );

    return error_flag;
}

err_t leddriver18_get_cc_output ( leddriver18_t *ctx, uint8_t *current_limit )
{
    err_t error_flag = LEDDRIVER18_OK;
    uint8_t rx_data = 0;
    
    error_flag = i2c_master_read( &ctx->i2c, &rx_data, 1 );
    
    if( rx_data & LEDDRIVER18_CC_ERROR )
    {
        error_flag = LEDDRIVER18_ERROR;
    }
    else
    {
        *current_limit = rx_data & LEDDRIVER18_CC_MASK;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
