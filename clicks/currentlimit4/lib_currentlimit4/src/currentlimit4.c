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
 * @file currentlimit4.c
 * @brief Current Limit 4 Click Driver.
 */

#include "currentlimit4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY          0x00

void currentlimit4_cfg_setup ( currentlimit4_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENTLIMIT4_SET_DEV_ADDR;
    cfg->vref        = CURRENTLIMIT4_VREF_3V3;
}

err_t currentlimit4_init ( currentlimit4_t *ctx, currentlimit4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return CURRENTLIMIT4_OK;
}

err_t currentlimit4_default_cfg ( currentlimit4_t *ctx ) 
{
    Delay_100ms( );
    currentlimit4_disable( ctx );
    Delay_100ms( );
    err_t err_flag = currentlimit4_set_limit( ctx, CURRENTLIMIT4_ILIMIT_DEFAULT );
    currentlimit4_enable( ctx );
    Delay_100ms( );
    return err_flag;
}

void currentlimit4_enable ( currentlimit4_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

void currentlimit4_disable ( currentlimit4_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

uint8_t currentlimit4_get_power_good ( currentlimit4_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

err_t currentlimit4_read_raw_adc ( currentlimit4_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t currentlimit4_read_voltage ( currentlimit4_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t currentlimit4_set_vref ( currentlimit4_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t currentlimit4_get_current ( currentlimit4_t *ctx, float *current ) 
{
    err_t err_flag = CURRENTLIMIT4_OK;
    float voltage = DUMMY;
    for ( uint8_t n_cnt = 0; n_cnt < CURRENTLIMIT4_MEASURE_NUM; n_cnt++ )
    {
        err_flag |= currentlimit4_read_voltage( ctx, &voltage );
        *current += ( voltage * CURRENTLIMIT4_SENSITIVITY_A_PER_V );
        Delay_1ms( );
    }
    *current /= ( float ) CURRENTLIMIT4_MEASURE_NUM;
    return err_flag;
}

err_t currentlimit4_set_wiper_pos ( currentlimit4_t *ctx, uint16_t wiper_pos )
{
    uint8_t data_buf[ 2 ] = { ( ( wiper_pos >> 8 ) & 0x01 ), ( wiper_pos & 0xFF ) };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t currentlimit4_set_res ( currentlimit4_t *ctx, uint16_t res_ohm )
{
    err_t err_flag = CURRENTLIMIT4_OK;
    float wiper = 0;
    if ( res_ohm > CURRENTLIMIT4_DIGIPOT_MAX )
    {
        err_flag = CURRENTLIMIT4_ERROR;
    }
    else
    {
        wiper = ( float ) ( CURRENTLIMIT4_DIGIPOT_MAX - res_ohm ) / CURRENTLIMIT4_DIGIPOT_MAX;
        wiper = wiper * CURRENTLIMIT4_DIGIPOT_RES + CURRENTLIMIT4_ROUND_TO_NEAREST_INT;
        err_flag = currentlimit4_set_wiper_pos( ctx, ( uint16_t ) wiper );
    }
    return err_flag;
}

err_t currentlimit4_set_limit ( currentlimit4_t *ctx, uint16_t ilimit_ma )
{
    if ( ( ilimit_ma < CURRENTLIMIT4_ILIMIT_MIN ) || ( ilimit_ma > CURRENTLIMIT4_ILIMIT_MAX ) )
    {
        return CURRENTLIMIT4_ERROR;
    }
    float rlimit = CURRENTLIMIT4_RILIM_DIVIDEND / ( ilimit_ma - CURRENTLIMIT4_RILIM_OFFSET );
    rlimit -= ( CURRENTLIMIT4_DIGIPOT_R8 + CURRENTLIMIT4_DIGIPOT_OFFSET );
    rlimit += CURRENTLIMIT4_ROUND_TO_NEAREST_INT;
    if ( rlimit < 0 )
    {
        rlimit = 0;
    }
    return currentlimit4_set_res( ctx, ( uint16_t ) rlimit );
}

// ------------------------------------------------------------------------- END
