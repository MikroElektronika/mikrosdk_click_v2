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
 * @file pir3.c
 * @brief PIR 3 Click Driver.
 */

#include "pir3.h"

void pir3_cfg_setup ( pir3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->on = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PIR3_DEVICE_ADDRESS;
}

err_t pir3_init ( pir3_t *ctx, pir3_cfg_t *cfg ) 
{
    digital_out_init( &ctx->on, cfg->on );
    digital_out_high ( &ctx->on );
    Delay_1sec ( );

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

    return I2C_MASTER_SUCCESS;
}

err_t pir3_default_cfg ( pir3_t *ctx ) 
{
    pir3_set_detection_level ( ctx, PIR3_CONFIG_DETLVL_DEFAULT );
    pir3_set_trigger_out ( ctx, PIR3_CONFIG_TRIGOM_DEFAULT );
    pir3_set_filter_step ( ctx, PIR3_CONFIG_FSTEP_DEFAULT );
    pir3_set_filter_type ( ctx, PIR3_CONFIG_FILSEL_DEFAULT );

    err_t error_flag = pir3_write_config ( ctx );
    Delay_1sec ( );
    Delay_1sec ( );
    int16_t dummy_read = 0;
    error_flag |= pir3_read_peak_hold ( ctx, &dummy_read );
    Delay_100ms ( );
    return error_flag;
}

err_t pir3_write_config ( pir3_t *ctx )
{
    uint8_t data_buf[ 7 ] = { 0 };
    data_buf[ 3 ] = ( ( ctx->config.filsel & PIR3_CONFIG_FILSEL_MASK ) << 2 ) | 
                    ( ctx->config.fstep & PIR3_CONFIG_FSTEP_MASK );
    data_buf[ 4 ] = ( ( ctx->config.trigom & PIR3_CONFIG_TRIGOM_MASK ) << 7 ) | 
                    ( ( ctx->config.detlvl >> 1 ) & PIR3_CONFIG_DETLVL_MASK_MSB );
    data_buf[ 5 ] = ( ( ctx->config.detlvl & PIR3_CONFIG_DETLVL_MASK_LSB ) << 7 );
    return i2c_master_write( &ctx->i2c, data_buf, 7 );
}

err_t pir3_read_peak_hold ( pir3_t *ctx, int16_t *peak_hold )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_read( &ctx->i2c, data_buf, 2 );
    if ( ( PIR3_OK == error_flag ) && ( NULL != peak_hold ) )
    {
        *peak_hold = ( ( int16_t ) ( data_buf[ 0 ] & 0x0F ) << 8 ) | data_buf[ 1 ];
        *peak_hold <<= 4;
        *peak_hold >>= 4;
    }
    return error_flag;
}

void pir3_enable_device ( pir3_t *ctx )
{
    digital_out_high ( &ctx->on );
}

void pir3_disable_device ( pir3_t *ctx )
{
    digital_out_low ( &ctx->on );
}

void pir3_set_detection_level ( pir3_t *ctx, uint8_t detlvl )
{
    ctx->config.detlvl = detlvl;
}

void pir3_set_trigger_out ( pir3_t *ctx, uint8_t trigom )
{
    ctx->config.trigom = trigom & PIR3_CONFIG_TRIGOM_MASK;
}

void pir3_set_filter_step ( pir3_t *ctx, uint8_t fstep )
{
    ctx->config.fstep = fstep & PIR3_CONFIG_FSTEP_MASK;
}

void pir3_set_filter_type ( pir3_t *ctx, uint8_t filsel )
{
    ctx->config.filsel = filsel & PIR3_CONFIG_FILSEL_MASK;
}

// ------------------------------------------------------------------------- END
