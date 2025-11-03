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
 * @file bldcfoc2.c
 * @brief BLDC FOC 2 Click Driver.
 */

#include "bldcfoc2.h"

void bldcfoc2_cfg_setup ( bldcfoc2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->fgo = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->dev_pwm_freq = BLDCFOC2_PWM_FREQ;
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BLDCFOC2_DEVICE_ADDRESS;
}

err_t bldcfoc2_init ( bldcfoc2_t *ctx, bldcfoc2_cfg_t *cfg ) 
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

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dir, cfg->dir );

    // Input pins
    digital_in_init( &ctx->fgo, cfg->fgo );
    digital_in_init( &ctx->fault, cfg->fault );

    return BLDCFOC2_OK;
}

err_t bldcfoc2_default_cfg ( bldcfoc2_t *ctx ) 
{
    err_t error_flag = BLDCFOC2_OK;
    
    bldcfoc2_set_direction ( ctx, BLDCFOC2_DIR_CW );
    bldcfoc2_pull_brake ( ctx );
    error_flag |= bldcfoc2_set_duty_cycle ( ctx, BLDCFOC2_PWM_ZERO_DUTY );
    error_flag |= bldcfoc2_pwm_start( ctx );
    bldcfoc2_release_brake ( ctx );

    return error_flag;
}

err_t bldcfoc2_write_reg ( bldcfoc2_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 4 );
}

err_t bldcfoc2_read_reg ( bldcfoc2_t *ctx, uint8_t reg, uint32_t *data_out )
{
    return bldcfoc2_read_regs( ctx, reg, data_out, 1 );
}

err_t bldcfoc2_read_regs ( bldcfoc2_t *ctx, uint8_t reg, uint32_t *data_out, uint8_t len )
{
    err_t error_flag = BLDCFOC2_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( NULL == data_out )
    {
        return BLDCFOC2_ERROR;
    }
    error_flag |= i2c_master_write( &ctx->i2c, &reg, 1 );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        error_flag |= i2c_master_read( &ctx->i2c, data_buf, 3 );
        if ( BLDCFOC2_OK == error_flag )
        {
            data_out[ cnt ] = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
        }
    }
    return error_flag;
}

err_t bldcfoc2_set_duty_cycle ( bldcfoc2_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t bldcfoc2_pwm_stop ( bldcfoc2_t *ctx )
{
    return pwm_stop( &ctx->pwm );
}

err_t bldcfoc2_pwm_start ( bldcfoc2_t *ctx )
{
    return pwm_start( &ctx->pwm );
}

void bldcfoc2_pull_brake ( bldcfoc2_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void bldcfoc2_release_brake ( bldcfoc2_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void bldcfoc2_set_direction ( bldcfoc2_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void bldcfoc2_switch_direction ( bldcfoc2_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

uint8_t bldcfoc2_get_fgo_pin ( bldcfoc2_t *ctx )
{
    return digital_in_read ( &ctx->fgo );
}

uint8_t bldcfoc2_get_fault_pin ( bldcfoc2_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

err_t bldcfoc2_eeprom_access_lock ( bldcfoc2_t *ctx )
{
    return bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_ACCESS, BLDCFOC2_EEPROM_ACCESS_LOCK );
}

err_t bldcfoc2_eeprom_access_unlock ( bldcfoc2_t *ctx )
{
    return bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_ACCESS, BLDCFOC2_EEPROM_ACCESS_UNLOCK );
}

err_t bldcfoc2_eeprom_erase ( bldcfoc2_t *ctx, uint8_t addr )
{
    err_t error_flag = BLDCFOC2_OK;
    error_flag |= bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_ADDR, addr );
    error_flag |= bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_DATA, BLDCFOC2_EEPROM_DATA_CLEAR );
    error_flag |= bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_CTRL, BLDCFOC2_EEPROM_CTRL_ER | BLDCFOC2_EEPROM_CTRL_EN );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_CTRL, BLDCFOC2_EEPROM_CTRL_ER | BLDCFOC2_EEPROM_CTRL_EN );
    Delay_10ms ( );
    Delay_10ms ( );
    return error_flag;
}

err_t bldcfoc2_eeprom_write ( bldcfoc2_t *ctx, uint8_t addr, uint32_t data_in )
{
    err_t error_flag = BLDCFOC2_OK;
    error_flag |= bldcfoc2_eeprom_erase ( ctx, addr );
    error_flag |= bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_ADDR, addr );
    error_flag |= bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_DATA, data_in );
    error_flag |= bldcfoc2_write_reg ( ctx, BLDCFOC2_REG_EEPROM_CTRL, BLDCFOC2_EEPROM_CTRL_WR | BLDCFOC2_EEPROM_CTRL_EN );
    Delay_10ms ( );
    Delay_10ms ( );
    return error_flag;
}

err_t bldcfoc2_eeprom_read ( bldcfoc2_t *ctx, uint8_t addr, uint32_t *data_out )
{
    return bldcfoc2_read_reg ( ctx, addr, data_out );
}

err_t bldcfoc2_eeprom_set_config ( bldcfoc2_t *ctx )
{
    err_t error_flag = BLDCFOC2_OK;
    // Default config for motor F80 PRO KV1900, configured for 11.2V 10A power supply
    // PWM input frequency 20KHz with duty cycle range 10 to 50%.
    error_flag |= bldcfoc2_eeprom_access_unlock ( ctx );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_8, BLDCFOC2_EEPROM_8 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_9, BLDCFOC2_EEPROM_9 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_10, BLDCFOC2_EEPROM_10 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_11, BLDCFOC2_EEPROM_11 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_12, BLDCFOC2_EEPROM_12 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_13, BLDCFOC2_EEPROM_13 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_14, BLDCFOC2_EEPROM_14 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_15, BLDCFOC2_EEPROM_15 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_16, BLDCFOC2_EEPROM_16 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_17, BLDCFOC2_EEPROM_17 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_18, BLDCFOC2_EEPROM_18 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_19, BLDCFOC2_EEPROM_19 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_20, BLDCFOC2_EEPROM_20 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_21, BLDCFOC2_EEPROM_21 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_22, BLDCFOC2_EEPROM_22 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_23, BLDCFOC2_EEPROM_23 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_24, BLDCFOC2_EEPROM_24 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_25, BLDCFOC2_EEPROM_25 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_26, BLDCFOC2_EEPROM_26 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_27, BLDCFOC2_EEPROM_27 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_28, BLDCFOC2_EEPROM_28 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_29, BLDCFOC2_EEPROM_29 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_30, BLDCFOC2_EEPROM_30 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_31, BLDCFOC2_EEPROM_31 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_32, BLDCFOC2_EEPROM_32 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_33, BLDCFOC2_EEPROM_33 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_34, BLDCFOC2_EEPROM_34 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_35, BLDCFOC2_EEPROM_35 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_36, BLDCFOC2_EEPROM_36 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_37, BLDCFOC2_EEPROM_37 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_38, BLDCFOC2_EEPROM_38 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_39, BLDCFOC2_EEPROM_39 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_40, BLDCFOC2_EEPROM_40 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_41, BLDCFOC2_EEPROM_41 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_42, BLDCFOC2_EEPROM_42 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_43, BLDCFOC2_EEPROM_43 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_44, BLDCFOC2_EEPROM_44 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_45, BLDCFOC2_EEPROM_45 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_46, BLDCFOC2_EEPROM_46 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_47, BLDCFOC2_EEPROM_47 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_48, BLDCFOC2_EEPROM_48 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_49, BLDCFOC2_EEPROM_49 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_50, BLDCFOC2_EEPROM_50 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_51, BLDCFOC2_EEPROM_51 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_52, BLDCFOC2_EEPROM_52 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_53, BLDCFOC2_EEPROM_53 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_54, BLDCFOC2_EEPROM_54 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_55, BLDCFOC2_EEPROM_55 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_56, BLDCFOC2_EEPROM_56 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_57, BLDCFOC2_EEPROM_57 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_58, BLDCFOC2_EEPROM_58 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_59, BLDCFOC2_EEPROM_59 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_60, BLDCFOC2_EEPROM_60 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_61, BLDCFOC2_EEPROM_61 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_62, BLDCFOC2_EEPROM_62 );
    error_flag |= bldcfoc2_eeprom_write ( ctx, BLDCFOC2_REG_EEPROM_63, BLDCFOC2_EEPROM_63 );
    error_flag |= bldcfoc2_eeprom_access_lock ( ctx );
    return error_flag;
}

// ------------------------------------------------------------------------- END
