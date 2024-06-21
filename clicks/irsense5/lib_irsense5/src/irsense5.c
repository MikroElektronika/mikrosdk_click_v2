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
 * @file irsense5.c
 * @brief IR Sense 5 Click Driver.
 */

#include "irsense5.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void irsense5_cfg_setup ( irsense5_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = IRSENSE5_SET_DEV_ADDR;
    cfg->vref        = IRSENSE5_VREF_3V3;
}

err_t irsense5_init ( irsense5_t *ctx, irsense5_cfg_t *cfg ) 
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

    return IRSENSE5_OK;
}

err_t irsense5_read_raw_adc_thp ( irsense5_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t irsense5_read_raw_adc_thm ( irsense5_t *ctx, uint16_t *raw_adc ) 
{
    uint8_t rx_buf[ 2 ];
    err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
    *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & IRSENSE5_ADC_RESOLUTION;
    return err_flag;
}

err_t irsense5_read_vtg_thp ( irsense5_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t irsense5_read_vtg_thm ( irsense5_t *ctx, float *voltage ) 
{
    uint16_t raw_adc;
    err_t err_flag = irsense5_read_raw_adc_thm( ctx, &raw_adc );
    *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) IRSENSE5_ADC_RESOLUTION );
    return err_flag;
}

err_t irsense5_set_vref ( irsense5_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

err_t irsense5_get_amb_temp ( irsense5_t *ctx, float *amb_temp ) 
{
    uint16_t raw_adc = DUMMY;
    float inv_t0 = IRSENSE5_INVERTED_VALUE / IRSENSE5_ROOM_TEMP_IN_K;
    float inv_beta = IRSENSE5_INVERTED_VALUE / IRSENSE5_THERMISOR_BETA;
    err_t err_flag = irsense5_read_raw_adc_thp( ctx, &raw_adc );
    *amb_temp = IRSENSE5_INVERTED_VALUE;
    *amb_temp /= ( inv_t0 + inv_beta * ( log( ( IRSENSE5_ADC_RESOLUTION / (float) raw_adc ) - IRSENSE5_INVERTED_VALUE ) ) );
    *amb_temp -= IRSENSE5_TEMP_K_TO_C;
    return err_flag;
}

err_t irsense5_get_obj_temp ( irsense5_t *ctx, float *obj_temp ) 
{
    float thp_vtg = DUMMY;
    float thm_vtg = DUMMY;
    float obj_vtg = DUMMY;
    err_t err_flag = irsense5_read_vtg_thp( ctx, &thp_vtg );
    err_flag |= irsense5_read_vtg_thm( ctx, &thm_vtg );
    obj_vtg = thm_vtg - thp_vtg;
    *obj_temp = obj_vtg * IRSENSE5_VREF_GAIN_X10;
    *obj_temp *= IRSENSE5_LIN_FUN_MULT;
    *obj_temp += IRSENSE5_LIN_FUN_ADD;
    return err_flag;
}

// ------------------------------------------------------------------------- END
