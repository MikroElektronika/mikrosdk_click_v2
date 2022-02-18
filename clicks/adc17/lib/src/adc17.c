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
 * @file adc17.c
 * @brief ADC 17 Click Driver.
 */

#include "adc17.h"

void adc17_cfg_setup ( adc17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ADC17_SET_DEV_ADDR;
}

err_t adc17_init ( adc17_t *ctx, adc17_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t adc17_default_cfg ( adc17_t *ctx ) 
{
    err_t error_flag = ADC17_OK;
    
    error_flag |= adc17_write_setup_byte ( ctx, ADC17_SETUP_VREF_INT_REF_OUT_ON | 
                                                ADC17_SETUP_CLK_INT | 
                                                ADC17_SETUP_UNIPOLAR | 
                                                ADC17_SETUP_RST_NO_ACTION );
    error_flag |= adc17_write_config_byte ( ctx, ADC17_CONFIG_SCAN_CS0 | 
                                                 ADC17_CONFIG_CS0_AIN0 | 
                                                 ADC17_CONFIG_SINGLE_ENDED );
    return error_flag;
}

err_t adc17_write_setup_byte ( adc17_t *ctx, uint8_t setup_byte )
{
    ctx->setup_byte = ( setup_byte & ( ~ADC17_REG_BIT_MASK ) ) | ADC17_REG_SETUP;
    return i2c_master_write( &ctx->i2c, &ctx->setup_byte, 1 );
}

err_t adc17_write_config_byte ( adc17_t *ctx, uint8_t config_byte )
{
    ctx->config_byte = ( config_byte & ( ~ADC17_REG_BIT_MASK ) ) | ADC17_REG_CONFIG;
    return i2c_master_write( &ctx->i2c, &ctx->config_byte, 1 );
}

err_t adc17_set_channel ( adc17_t *ctx, uint8_t channel )
{
    if ( channel > ADC17_CHANNEL_1 )
    {
        return ADC17_ERROR;
    }
    ctx->config_byte &= ~ADC17_CONFIG_CS0_BIT_MASK;
    if ( ADC17_CHANNEL_1 == channel )
    {
        ctx->config_byte |= ADC17_CONFIG_CS0_AIN1;
    }
    return adc17_write_config_byte( ctx, ctx->config_byte );
}

err_t adc17_get_voltage ( adc17_t *ctx, float *voltage )
{
    uint8_t rx_buf[ 2 ];
    int16_t raw_adc;
    err_t error_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
    raw_adc = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
    raw_adc &= ADC17_RESOLUTION;
    if ( ( ADC17_SETUP_BIPOLAR == ( ctx->setup_byte & ADC17_SETUP_UNI_BIP_BIT_MASK ) ) && 
         ( ADC17_CONFIG_DIFFERENTIAL == ( ctx->config_byte & ADC17_CONFIG_SGL_DIF_BIT_MASK ) ) )
    {
        raw_adc = ( int16_t ) ( raw_adc << 4 ) >> 4;
        *voltage = ( ( float ) raw_adc / ADC17_RESOLUTION ) * ADC17_VREF;
    }
    else
    {
        *voltage = ( ( float ) raw_adc / ADC17_RESOLUTION ) * ADC17_VREF;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
