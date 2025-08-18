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
 * @file haptic5.c
 * @brief Haptic 5 Click Driver.
 */

#include "haptic5.h"

void haptic5_cfg_setup ( haptic5_cfg_t *cfg ) 
{
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->trg = HAL_PIN_NC;

    cfg->dev_pwm_freq = HAPTIC5_PWM_DEF_FREQ;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HAPTIC5_DEVICE_ADDRESS_1;
}

err_t haptic5_init ( haptic5_t *ctx, haptic5_cfg_t *cfg ) 
{
#if ( HAPTIC5_DEFAULT_COM == HAPTIC5_COM_I2C )
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

    digital_out_init( &ctx->trg, cfg->trg );
#else
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    
    digital_out_init( &ctx->dir, cfg->dir );
#endif
    digital_out_init( &ctx->rst, cfg->rst );

    return PWM_SUCCESS;
}

err_t haptic5_default_cfg ( haptic5_t *ctx ) 
{
    err_t error_flag = HAPTIC5_OK;

    haptic5_disable_device ( ctx );
    Delay_100ms ( );
    haptic5_enable_device ( ctx );
    Delay_100ms ( );

#if ( HAPTIC5_DEFAULT_COM == HAPTIC5_COM_I2C )
    if ( HAPTIC5_ERROR == haptic5_check_communication( ctx ) )
    {
        return HAPTIC5_ERROR;
    }
    error_flag |= haptic5_write_reg_byte ( ctx, HAPTIC5_REG_SYSTEM_SETTINGS, 
                                           HAPTIC5_SYSTEM_SETTINGS_MODE_CONTINUOUS | 
                                           HAPTIC5_SYSTEM_SETTINGS_TRIGGER_LEVEL | 
                                           HAPTIC5_SYSTEM_SETTINGS_TIMEOUT_4096MS | 
                                           HAPTIC5_SYSTEM_SETTINGS_PWR_MODE_AUTO );
    error_flag |= haptic5_write_reg_byte ( ctx, HAPTIC5_REG_SYSTEM_CONTROL, 
                                           HAPTIC5_SYSTEM_CONTROL_ACK_RESET );
#else
    haptic5_set_dir_forward ( ctx );
    
    error_flag |= haptic5_set_duty_cycle ( ctx, HAPTIC5_PWM_DEF_DUTY );
    error_flag |= haptic5_pwm_start( ctx );
#endif

    return error_flag;
}

#if ( HAPTIC5_DEFAULT_COM == HAPTIC5_COM_I2C )

err_t haptic5_write_regs ( haptic5_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t haptic5_read_regs ( haptic5_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, len );
}

err_t haptic5_write_reg_byte ( haptic5_t *ctx, uint16_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 2 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t haptic5_read_reg_byte ( haptic5_t *ctx, uint16_t reg, uint8_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, 1 );
}

err_t haptic5_write_reg_word ( haptic5_t *ctx, uint16_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 4 );
}

err_t haptic5_read_reg_word ( haptic5_t *ctx, uint16_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 2, &data_buf[ 2 ], 2 );
    if ( ( HAPTIC5_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

err_t haptic5_check_communication ( haptic5_t *ctx )
{
    uint16_t product_num = 0;
    if ( HAPTIC5_OK == haptic5_read_reg_word ( ctx, HAPTIC5_REG_PRODUCT_NUM, &product_num ) )
    {
        if ( HAPTIC5_PRODUCT_NUM == product_num )
        {
            return HAPTIC5_OK;
        }
    }
    return HAPTIC5_ERROR;
}

void haptic5_set_trg_low ( haptic5_t *ctx )
{
    digital_out_low ( &ctx->trg );
}

void haptic5_set_trg_high ( haptic5_t *ctx )
{
    digital_out_high ( &ctx->trg );
}

#else

err_t haptic5_set_duty_cycle ( haptic5_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t haptic5_pwm_stop ( haptic5_t *ctx )
{
    return pwm_stop( &ctx->pwm );
}

err_t haptic5_pwm_start ( haptic5_t *ctx )
{
    return pwm_start( &ctx->pwm );
}

void haptic5_set_dir_forward ( haptic5_t *ctx )
{
    digital_out_low ( &ctx->dir );
}

void haptic5_set_dir_reverse ( haptic5_t *ctx )
{
    digital_out_high ( &ctx->dir );
}

void haptic5_toggle_dir ( haptic5_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

#endif

void haptic5_enable_device ( haptic5_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void haptic5_disable_device ( haptic5_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

// ------------------------------------------------------------------------- END
