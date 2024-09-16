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
 * @file buck18.c
 * @brief Buck 18 Click Driver.
 */

#include "buck18.h"

void buck18_cfg_setup ( buck18_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCK18_SET_DEV_ADDR_0;
    cfg->vref        = BUCK18_VREF_3V3;
}

err_t buck18_init ( buck18_t *ctx, buck18_cfg_t *cfg ) 
{
    ctx->vref = cfg->vref;
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
    analog_in_config_t adc_cfg;
    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin = cfg->an;
    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }
    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }
    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    return BUCK18_OK;
}

err_t buck18_default_cfg ( buck18_t *ctx ) 
{
    buck18_disable( ctx );
    Delay_100ms();

    err_t err_flag = buck18_set_resistance( ctx, BUCK18_RES_50_KOHM );
    Delay_100ms();

    buck18_enable( ctx );
    Delay_100ms();

    return err_flag;
}

err_t buck18_read_raw_adc ( buck18_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t buck18_read_voltage ( buck18_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t buck18_set_vref ( buck18_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void buck18_enable ( buck18_t *ctx ) 
{
    digital_out_high( &ctx->rst );
}

void buck18_disable ( buck18_t *ctx ) 
{
    digital_out_low( &ctx->rst );
}

err_t buck18_write_data ( buck18_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t buck18_read_data ( buck18_t *ctx, uint8_t *data_out ) 
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t buck18_write_rdac ( buck18_t *ctx, uint8_t wiper_pos ) 
{
    err_t err_flag = BUCK18_ERROR;
    if ( BUCK18_WIPER_POS_MAX >= wiper_pos )
    {
        err_flag = buck18_write_data( ctx, BUCK18_CMD_RDAC_OTP, wiper_pos );
    }
    return err_flag;
}

err_t buck18_set_resistance ( buck18_t *ctx, float res_kohm ) 
{
    err_t err_flag = BUCK18_ERROR;
    if ( BUCK18_RES_55_KOHM > res_kohm )
    {
        err_flag = buck18_write_rdac( ctx, ( uint8_t ) ( BUCK18_WIPER_POS_MAX - 
                                                       ( ( BUCK18_WIPER_POS_MAX * 
                                                       ( res_kohm - BUCK18_RES_5_KOHM ) ) /
                                                       BUCK18_RES_50_KOHM ) ) );
    }
    return err_flag;
}

err_t buck18_set_vout ( buck18_t *ctx, buck18_vout_t vout ) 
{
    uint8_t vout_table[ 15 ] = { BUCK18_RDAC_WIPER_POSITION };
    buck18_disable( ctx );
    err_t err_flag = buck18_write_rdac( ctx, vout_table[ vout ] );
    Delay_10ms( );
    buck18_enable( ctx );
    Delay_10ms( );
    return err_flag;
}

// ------------------------------------------------------------------------- END
