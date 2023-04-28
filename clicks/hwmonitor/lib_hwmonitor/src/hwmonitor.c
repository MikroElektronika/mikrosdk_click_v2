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
 * @file hwmonitor.c
 * @brief HW Monitor Click Driver.
 */

#include "hwmonitor.h"

/**
 * @brief HW Monitor voltage and temperature calculation values.
 * @details Definition of voltage and temperature calculation values.
 */
#define HWMONITOR_TEMP_9_BIT_RESOLUTION       0.5f
#define HWMONITOR_TEMP_12_BITRESOLUTION       0.0625f
#define HWMONITOR_VOLTAGE_RESOLUTION          2.5f

void hwmonitor_cfg_setup ( hwmonitor_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HWMONITOR_DEVICE_ADDRESS_0;
}

err_t hwmonitor_init ( hwmonitor_t *ctx, hwmonitor_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return I2C_MASTER_SUCCESS;
}

err_t hwmonitor_default_cfg ( hwmonitor_t *ctx ) 
{
    uint8_t manufacture_id, revision_id, data_buf;
    hwmonitor_reset( ctx );
    Delay_10ms( );
    
    err_t err_flag = hwmonitor_get_device_id( ctx, &manufacture_id, &revision_id );
    if ( HWMONITOR_MANUFACTURERS_ID == manufacture_id )
    {
        hwmonitor_config_t config;
        config.start       = HWMONITOR_SET_CONFIG_START_EN;
        config.int_enable  = HWMONITOR_SET_CONFIG_INT_DIS;
        config.int_pol_sel = HWMONITOR_SET_CONFIG_INT_OPEN_DRAIN;
        config.int_clear   = HWMONITOR_SET_CONFIG_INT_CLR_DIS;
        config.chas_clear  = HWMONITOR_SET_CONFIG_CHA_NCLR_GPI;
        config.gpo         = HWMONITOR_SET_CONFIG_GPO_LOW;
        config.init        = HWMONITOR_SET_CONFIG_PWR_ON;
        err_flag |= hwmonitor_set_config( ctx, config );
        Delay_10ms( );

        data_buf = HWMONITOR_SET_FAN1_MODE_COUNT;
        data_buf |= HWMONITOR_SET_FAN2_MODE_COUNT;
        data_buf |= HWMONITOR_SET_FAN1_CTRL_SPEED_DIV2;
        data_buf |= HWMONITOR_SET_FAN2_CTRL_SPEED_DIV2;
        data_buf |= HWMONITOR_SET_MODE_OS_DISABLE;
        data_buf |= HWMONITOR_SET_MODE_RST_DISABLE;
        err_flag |= hwmonitor_generic_write( ctx, HWMONITOR_REG_FAN_DIVISOR, &data_buf, 1 );
        Delay_10ms( );

        err_flag |= hwmonitor_set_temp_res( ctx, HWMONITOR_SET_TEMP_RES_11_bit );
        Delay_10ms( );

        err_flag |= hwmonitor_set_ch_out( ctx, HWMONITOR_SET_ALL_CH_ENABLE );
        Delay_10ms( );
    }
    else
    {
        err_flag = HWMONITOR_ERROR;
    }
    return err_flag;
}

err_t hwmonitor_generic_write ( hwmonitor_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t hwmonitor_generic_read ( hwmonitor_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void hwmonitor_reset ( hwmonitor_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_10ms();
    digital_out_high( &ctx->rst );
    Delay_10ms();
}

err_t hwmonitor_get_config ( hwmonitor_t *ctx, hwmonitor_config_t *config ) 
{
    uint8_t data_buf = 0;
    err_t err_flag = hwmonitor_generic_read( ctx, HWMONITOR_REG_CONFIGURATION, &data_buf, 1 );
    config->start       =   data_buf        & 0x01;
    config->int_enable  = ( data_buf >> 1 ) & 0x01;
    config->int_pol_sel = ( data_buf >> 2 ) & 0x01;
    config->int_clear   = ( data_buf >> 3 ) & 0x01;
    config->chas_clear  = ( data_buf >> 5 ) & 0x01;
    config->gpo         = ( data_buf >> 6 ) & 0x01;
    config->init        = ( data_buf >> 7 ) & 0x01;
    return err_flag;
}

err_t hwmonitor_set_config ( hwmonitor_t *ctx, hwmonitor_config_t config ) 
{
    uint8_t data_buf = config.start  & 0x01;
    data_buf |= ( config.int_enable  & 0x01 ) << 1;
    data_buf |= ( config.int_pol_sel & 0x01 ) << 2;
    data_buf |= ( config.int_clear   & 0x01 ) << 3;
    data_buf |= ( config.chas_clear  & 0x01 ) << 5;
    data_buf |= ( config.gpo         & 0x01 ) << 6;
    data_buf |= ( config.init        & 0x01 ) << 7;
    return hwmonitor_generic_write( ctx, HWMONITOR_REG_CONFIGURATION, &data_buf, 1 );
}

err_t hwmonitor_get_device_id ( hwmonitor_t *ctx, uint8_t *manufacture_id, uint8_t *revision_id ) 
{
    err_t err_flag = hwmonitor_generic_read( ctx, HWMONITOR_REG_RAM_MANUFACTURE_ID, manufacture_id, 1 );
    err_flag |= hwmonitor_generic_read( ctx, HWMONITOR_REG_RAM_REVISION_ID, revision_id, 1 );
    return err_flag;
}

err_t hwmonitor_set_temp_res ( hwmonitor_t *ctx, uint8_t temp_res ) 
{
    err_t err_flag = HWMONITOR_OK;
    uint8_t data_buf = 0;
    if ( temp_res > HWMONITOR_SET_TEMP_RES_11_bit )
    {
        err_flag = HWMONITOR_ERROR;
    }
    else
    {
        err_t err_flag = hwmonitor_generic_read( ctx, HWMONITOR_REG_OS_T_RES_CONFIG, &data_buf, 1 );
        Delay_1ms( );
        data_buf |= temp_res << 3;
        err_flag |= hwmonitor_generic_write( ctx, HWMONITOR_REG_OS_T_RES_CONFIG, &data_buf, 1 );
    }
    return err_flag;
}

err_t hwmonitor_set_ch_out ( hwmonitor_t *ctx, uint8_t ch_out ) 
{
    return hwmonitor_generic_write( ctx, HWMONITOR_REG_CHANNEL_DISABLE, &ch_out, 1 );
}

err_t hwmonitor_get_temperature ( hwmonitor_t *ctx, float *temperature ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t check_t_res;
    int16_t data_tmp = 0;
    err_t err_flag = hwmonitor_generic_read( ctx, HWMONITOR_REG_OS_T_RES_CONFIG, &check_t_res, 1 );
    Delay_10ms( );
    err_flag |= hwmonitor_generic_read( ctx, HWMONITOR_REG_RAM_TEMPERATURE, data_buf, 2 );
    data_tmp = data_buf[ 0 ];
    data_tmp <<= 8;
    data_tmp |= data_buf[ 1 ];
    if ( check_t_res & HWMONITOR_TEMP_RES_11_bit_BIT_MASK )
    {
        data_tmp >>= 4;
        *temperature = ( float ) data_tmp;
        *temperature *= HWMONITOR_TEMP_12_BITRESOLUTION;
    }
    else
    {
        data_tmp >>= 7;
        *temperature = ( float ) data_tmp;
        *temperature *= HWMONITOR_TEMP_9_BIT_RESOLUTION;
    }
    return err_flag;
}

err_t hwmonitor_get_analog_inputs ( hwmonitor_t *ctx, uint8_t in_pos, float *voltage ) 
{
    err_t err_flag = HWMONITOR_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t data_tmp = 0;
    if ( in_pos > HWMONITOR_IN_6 )
    {
        err_flag = HWMONITOR_ERROR;
    }
    else
    {
        err_flag |= hwmonitor_generic_read( ctx, HWMONITOR_REG_RAM_IN_0 + in_pos , data_buf, 2 );
        data_tmp = data_buf[ 0 ];
        data_tmp <<= 8;
        data_tmp |= data_buf[ 1 ];
        data_tmp >>= 6;
        *voltage = ( float ) data_tmp;
        *voltage *= HWMONITOR_VOLTAGE_RESOLUTION;
    }
    return err_flag;
}

err_t hwmonitor_get_fan_output ( hwmonitor_t *ctx, uint8_t fan_pos, uint8_t *fan_output ) 
{
    err_t err_flag = HWMONITOR_OK;
    if ( ( fan_pos < HWMONITOR_FAN_1 ) || ( fan_pos > HWMONITOR_FAN_2 ) )
    {
        err_flag = HWMONITOR_ERROR;
    }
    else
    {
        fan_pos--;
        err_flag |= hwmonitor_generic_read( ctx, HWMONITOR_REG_RAM_FAN_1 + fan_pos , fan_output, 1 );
    }
    return err_flag;
}

err_t hwmonitor_set_analog_in_limit ( hwmonitor_t *ctx, uint8_t in_pos, uint16_t upper_limit, uint16_t lower_limit ) 
{
    err_t err_flag = HWMONITOR_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( in_pos > HWMONITOR_IN_6 ) || ( upper_limit < lower_limit ) )
    {
        err_flag = HWMONITOR_ERROR;
    }
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( upper_limit >> 8 );
        data_buf[ 1 ] = ( uint8_t ) ( upper_limit >> 8 );
        err_flag |= hwmonitor_generic_write( ctx, HWMONITOR_REG_RAM_LIM_IN_0_H + ( in_pos * 2 ), data_buf, 2 );
        Delay_1ms( );
        data_buf[ 0 ] = ( uint8_t ) ( lower_limit >> 8 );
        data_buf[ 1 ] = ( uint8_t ) ( lower_limit >> 8 );
        err_flag |= hwmonitor_generic_write( ctx, HWMONITOR_REG_RAM_LIM_IN_0_L + ( in_pos * 2 ) , data_buf, 2 );
    }
    return err_flag;
}

uint8_t hwmonitor_get_int_pin ( hwmonitor_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
