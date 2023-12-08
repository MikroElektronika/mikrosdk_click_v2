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
 * @file thunderemu.c
 * @brief Thunder EMU Click Driver.
 */

#include "thunderemu.h"

/**
 * @brief Thunder EMU Click thunder profile data for dac output.
 * @details Thunder profile data for dac output calibrated for up to 15cm distance between inductors.
 */
static uint16_t thunder_profile[ 20 ] = 
{ 
    1030, 730, 520, 370, 270, 200, 150, 110, 90, 70, 60, 50, 45, 43, 40, 37, 35, 33, 32, 31 
};

void thunderemu_cfg_setup ( thunderemu_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->led = HAL_PIN_NC;
    cfg->close = HAL_PIN_NC;
    cfg->mid = HAL_PIN_NC;
    cfg->far_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THUNDEREMU_DEVICE_ADDRESS_0;
}

err_t thunderemu_init ( thunderemu_t *ctx, thunderemu_cfg_t *cfg ) 
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

    digital_out_init( &ctx->led, cfg->led );

    digital_in_init( &ctx->close, cfg->close );
    digital_in_init( &ctx->mid, cfg->mid );
    digital_in_init( &ctx->far_pin, cfg->far_pin );

    return I2C_MASTER_SUCCESS;
}

err_t thunderemu_default_cfg ( thunderemu_t *ctx ) 
{
    return thunderemu_set_dac_output ( ctx, THUNDEREMU_DAC_MODE_FAST_PDOWN_1K, THUNDEREMU_DAC_OUT_MIN );
}

err_t thunderemu_set_dac_output ( thunderemu_t *ctx, uint8_t mode, uint16_t dac_data )
{
    err_t error_flag = THUNDEREMU_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( dac_data > THUNDEREMU_DAC_OUT_MAX )
    {
        return THUNDEREMU_ERROR;
    }
    switch ( mode )
    {
        case THUNDEREMU_DAC_MODE_FAST_NORMAL:
        case THUNDEREMU_DAC_MODE_FAST_PDOWN_1K:
        case THUNDEREMU_DAC_MODE_FAST_PDOWN_100K:
        case THUNDEREMU_DAC_MODE_FAST_PDOWN_500K:
        {
            data_buf[ 0 ] = mode | ( uint8_t ) ( ( dac_data >> 8 ) & 0x0F );
            data_buf[ 1 ] = ( uint8_t ) ( dac_data & 0xFF );
            error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
            break;
        }
        case THUNDEREMU_DAC_MODE_EEPROM_NORMAL:
        case THUNDEREMU_DAC_MODE_EEPROM_PDOWN_1K:
        case THUNDEREMU_DAC_MODE_EEPROM_PDOWN_100K:
        case THUNDEREMU_DAC_MODE_EEPROM_PDOWN_500K:
        {
            data_buf[ 0 ] = mode;
            data_buf[ 1 ] = ( uint8_t ) ( ( dac_data >> 4 ) & 0xFF );
            data_buf[ 2 ] = ( uint8_t ) ( ( dac_data << 4 ) & 0xF0 );
            error_flag = i2c_master_write( &ctx->i2c, data_buf, 3 );
            break;
        }
        default:
        {
            error_flag = THUNDEREMU_ERROR;
            break;
        }
    }
    return error_flag;
}

err_t thunderemu_generate_thunder ( thunderemu_t *ctx, uint8_t mode )
{
    err_t error_flag = THUNDEREMU_OK;
    if ( mode > THUNDEREMU_MODE_FAR )
    {
        return THUNDEREMU_ERROR;
    }
    uint8_t repeat_signal_cnt = 3 - mode;
    thunderemu_led_enable ( ctx );
    while ( repeat_signal_cnt-- )
    {
        for ( uint8_t cnt = 0; cnt < 20; cnt++ )
        {
            error_flag |= thunderemu_set_dac_output ( ctx, THUNDEREMU_DAC_MODE_FAST_NORMAL, 
                                                      thunder_profile[ cnt ] );
            Delay_22us( );
        }
    }
    Delay_10ms ( );
    error_flag |= thunderemu_set_dac_output ( ctx, THUNDEREMU_DAC_MODE_FAST_PDOWN_1K, 
                                              THUNDEREMU_DAC_OUT_MIN );
    thunderemu_led_disable ( ctx );
    return error_flag;
}

void thunderemu_led_enable ( thunderemu_t *ctx )
{
    digital_out_high ( &ctx->led );
}

void thunderemu_led_disable ( thunderemu_t *ctx )
{
    digital_out_low ( &ctx->led );
}

uint8_t thunderemu_get_close_pin ( thunderemu_t *ctx )
{
    return digital_in_read ( &ctx->close );
}

uint8_t thunderemu_get_mid_pin ( thunderemu_t *ctx )
{
    return digital_in_read ( &ctx->mid );
}

uint8_t thunderemu_get_far_pin ( thunderemu_t *ctx )
{
    return digital_in_read ( &ctx->far_pin );
}

// ------------------------------------------------------------------------- END
