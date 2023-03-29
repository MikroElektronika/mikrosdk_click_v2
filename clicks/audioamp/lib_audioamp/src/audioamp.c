/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "audioamp.h"

/**
 * \brief Register Address
 */
#define AUDIOAMP_REG_MODE             0x00
#define AUDIOAMP_REG_DIAG             0x20
#define AUDIOAMP_REG_FAULT            0x40
#define AUDIOAMP_REG_VOL_1            0x60
#define AUDIOAMP_REG_VOL_2            0x80

/**
 * \brief Channel Settings
 */
#define AUDIOAMP_MODE_MUX             0x0C
#define AUDIOAMP_MODE_MUTE            0x00

/**
 * \brief Power Control
 */
#define AUDIOAMP_MODE_POWER_ON        0x10
#define AUDIOAMP_MODE_POWER_OFF       0x00

/**
 * @brief Generic read function.
 *
 * @param ctx  Click object.
 * @param reg  Register address.
 * @param data_in  Data byte to be written.
 * @return    0  - Ok,
 *          (-1) - Error.
 *
 * @description This function writes one byte data to the selected register via I2C serial communication.
 */
static err_t audioamp_generic_write ( audioamp_t *ctx, uint8_t reg, uint8_t data_in );

void audioamp_cfg_setup ( audioamp_cfg_t *cfg )
{
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AUDIOAMP_I2C_ADDRESS_0;
}

err_t audioamp_init ( audioamp_t *ctx, audioamp_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.speed = cfg->i2c_speed;
    i2c_cfg.scl   = cfg->scl;
    i2c_cfg.sda   = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AUDIOAMP_INIT_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR )
    {
        return AUDIOAMP_INIT_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR )
    {
        return AUDIOAMP_INIT_ERROR;
    }

    if ( i2c_master_set_timeout( &ctx->i2c, 0 ) == I2C_MASTER_ERROR )
    {
        return AUDIOAMP_INIT_ERROR;
    }

    if ( digital_in_init( &ctx->int_pin, cfg->int_pin ) == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return AUDIOAMP_INIT_ERROR;
    }

    return AUDIOAMP_OK;
}

err_t audioamp_power_on ( audioamp_t *ctx )
{
    return audioamp_generic_write( ctx, AUDIOAMP_REG_MODE, AUDIOAMP_MODE_POWER_ON | AUDIOAMP_MODE_MUX );
}

err_t audioamp_power_off ( audioamp_t *ctx )
{
    return audioamp_generic_write( ctx, AUDIOAMP_REG_MODE, AUDIOAMP_MODE_POWER_OFF );
}

err_t audioamp_set_volume ( audioamp_t *ctx, uint8_t in_sel, uint8_t volume_level )
{
    if ( ( volume_level < 1 ) || ( volume_level > 32 ) )
    {
        return AUDIOAMP_INIT_ERROR;
    }

    if ( in_sel == AUDIOAMP_IN_1 )
    {
        if ( audioamp_generic_write( ctx, AUDIOAMP_REG_VOL_1, volume_level - 1 ) == I2C_MASTER_ERROR )
        {
            return AUDIOAMP_INIT_ERROR;
        }
    }
    else if ( in_sel == AUDIOAMP_IN_2 )
    {
        if ( audioamp_generic_write( ctx, AUDIOAMP_REG_VOL_2, volume_level - 1 ) == I2C_MASTER_ERROR )
        {
            return AUDIOAMP_INIT_ERROR;
        }
    }
    else if ( in_sel == AUDIOAMP_IN_1 | AUDIOAMP_IN_2 )
    {
        if ( audioamp_generic_write( ctx, AUDIOAMP_REG_VOL_1, volume_level - 1 ) == I2C_MASTER_ERROR )
        {
            return AUDIOAMP_INIT_ERROR;
        }

        if ( audioamp_generic_write( ctx, AUDIOAMP_REG_VOL_2, volume_level - 1 ) == I2C_MASTER_ERROR )
        {
            return AUDIOAMP_INIT_ERROR;
        }
    }
    else
    {
        return AUDIOAMP_INIT_ERROR;
    }

    return AUDIOAMP_OK;
}

err_t audioamp_mute ( audioamp_t *ctx )
{
    return audioamp_generic_write( ctx, AUDIOAMP_REG_MODE, AUDIOAMP_MODE_POWER_ON | AUDIOAMP_MODE_MUTE );
}

err_t audioamp_unmute ( audioamp_t *ctx )
{
    return audioamp_generic_write( ctx, AUDIOAMP_REG_MODE, AUDIOAMP_MODE_POWER_ON | AUDIOAMP_MODE_MUX );
}

err_t audioamp_set_fault_normal_operation ( audioamp_t *ctx )
{
    return audioamp_generic_write( ctx, AUDIOAMP_REG_FAULT, 0x00 );
}

err_t audioamp_set_fault_detecton_control ( audioamp_t *ctx, uint8_t input_command )
{
    return audioamp_generic_write( ctx, AUDIOAMP_REG_FAULT, input_command );
}

err_t audioamp_set_diagnostic_control ( audioamp_t *ctx, uint8_t input_command )
{
    return audioamp_generic_write( ctx, AUDIOAMP_REG_DIAG, input_command & 0x1E );
}

uint8_t audioamp_check_fault ( audioamp_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t audioamp_generic_write ( audioamp_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_data = ( reg & 0xE0 ) | ( data_in & 0x1F );

    return i2c_master_write( &ctx->i2c, &tx_data, 1 );
}

// ------------------------------------------------------------------------ END
