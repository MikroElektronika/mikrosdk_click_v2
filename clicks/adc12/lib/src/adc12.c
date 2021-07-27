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
 * @file adc12.c
 * @brief ADC 12 Click Driver.
 */

#include "adc12.h"

void adc12_cfg_setup ( adc12_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ADC12_DEV_ADDR_DEFAULT;
}

err_t adc12_init ( adc12_t *ctx, adc12_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t adc12_send_cmd ( adc12_t *ctx, uint8_t cmd_byte )
{
    return i2c_master_write( &ctx->i2c, &cmd_byte, 1 );
}

err_t adc12_read_data ( adc12_t *ctx, uint16_t *data_out )
{
    uint8_t rx_buf[ 2 ];

    err_t error_check = i2c_master_read( &ctx->i2c, rx_buf, 2 );

    *data_out = ( uint16_t )( ( rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] );
    *data_out &= 0x0FFF;

    return error_check;
}

void adc12_set_sd_mode ( adc12_t *ctx, uint8_t sd_mode )
{
    ctx->adc12_sd_mode = sd_mode & ADC12_CMD_SD_MASK;
}

uint8_t adc12_get_sd_mode ( adc12_t *ctx )
{
    return ctx->adc12_sd_mode;
}

void adc12_set_pd_mode ( adc12_t *ctx, uint8_t pd_mode )
{
    ctx->adc12_pd_mode = pd_mode & ADC12_CMD_PD_MASK;
}

uint8_t adc12_get_pd_mode ( adc12_t *ctx )
{
    return ctx->adc12_pd_mode;
}

err_t adc12_read_raw_data ( adc12_t *ctx, uint8_t ch, uint16_t *data_out )
{
    uint8_t cfg = 0;

    cfg |= ctx->adc12_sd_mode;

    cfg |= ctx->adc12_pd_mode;
    cfg |= ( ch % 8 ) << 4;
    
    err_t error_check = adc12_send_cmd( ctx, cfg );

    Delay_100ms( );
    
    error_check |= adc12_read_data( ctx, data_out );
    
    return error_check;
}

err_t adc12_read_voltage ( adc12_t *ctx, uint8_t ch, uint16_t vref, float *data_out )
{
    uint16_t raw_adc = 0;
    
    err_t error_check = adc12_read_raw_data( ctx, ch, &raw_adc );
    *data_out = ( float ) raw_adc * ( ( float ) vref / ADC12_RES );

    return error_check;
}

// ------------------------------------------------------------------------- END
