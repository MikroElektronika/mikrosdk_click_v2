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
 * @file diffpress5.c
 * @brief Diff Press 5 Click Driver.
 */

#include "diffpress5.h"

void diffpress5_cfg_setup ( diffpress5_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIFFPRESS5_SET_DEV_ADDR;
    cfg->drv_sel     = DIFFPRESS5_DRV_SEL_I2C;
    cfg->vref        = DIFFPRESS5_VREF_3V3;
    if ( DIFFPRESS5_DRV_SEL_I2C == cfg->drv_sel )
    {
        cfg->vref = DIFFPRESS5_VREF_5V;
    }
}

void diffpress5_drv_interface_sel ( diffpress5_cfg_t *cfg, diffpress5_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
    cfg->vref = DIFFPRESS5_VREF_3V3;
    if ( DIFFPRESS5_DRV_SEL_I2C == cfg->drv_sel )
    {
        cfg->vref = DIFFPRESS5_VREF_5V;
    }
}

err_t diffpress5_init ( diffpress5_t *ctx, diffpress5_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( DIFFPRESS5_DRV_SEL_I2C == ctx->drv_sel ) 
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
    }
    else
    {
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
    }

    return DIFFPRESS5_OK;
}

err_t diffpress5_read_adc_raw ( diffpress5_t *ctx, uint16_t *raw_adc ) 
{
    if ( DIFFPRESS5_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ] = { 0 };
        err_t error_flag = i2c_master_read ( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & DIFFPRESS5_ADC_RESOLUTION;
        return error_flag;
    }
    else
    {
        return analog_in_read ( &ctx->adc, raw_adc );
    }
}

err_t diffpress5_read_adc_voltage ( diffpress5_t *ctx, float *voltage ) 
{
    if ( DIFFPRESS5_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc = 0;
        err_t error_flag = diffpress5_read_adc_raw ( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) DIFFPRESS5_ADC_RESOLUTION );
        return error_flag;
    }
    else
    {
        return analog_in_read_voltage ( &ctx->adc, voltage );
    }
}

err_t diffpress5_set_vref ( diffpress5_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( DIFFPRESS5_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return DIFFPRESS5_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t diffpress5_read_vout ( diffpress5_t *ctx, float *vout )
{
    float voltage = 0;
    err_t error_flag = diffpress5_read_adc_voltage ( ctx, &voltage );
    if ( DIFFPRESS5_OK == error_flag )
    {
        if ( DIFFPRESS5_DRV_SEL_ADC == ctx->drv_sel ) 
        {
            *vout = voltage * DIFFPRESS5_ADC_VOUT_MULTIPLIER;
        }
        else
        {
            *vout = voltage;
        }
    }
    return error_flag;
}

err_t diffpress5_read_vout_avg ( diffpress5_t *ctx, uint16_t num_conv, float *vout_avg )
{
    float vout = 0;
    float vout_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( DIFFPRESS5_OK == diffpress5_read_vout ( ctx, &vout ) )
        {
            vout_sum += vout;
            timeout_cnt = 0;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > DIFFPRESS5_TIMEOUT_MS )
        {
            return DIFFPRESS5_ERROR;
        }
    }
    *vout_avg = ( vout_sum / num_conv );
    return DIFFPRESS5_OK;
}

err_t diffpress5_calib_offset ( diffpress5_t *ctx )
{
    float voltage = 0;
    err_t error_flag = diffpress5_read_vout_avg ( ctx, DIFFPRESS5_NUM_CONVERSIONS, &voltage );
    ctx->zero_press_offset = voltage;
    return error_flag;
}

err_t diffpress5_read_pressure ( diffpress5_t *ctx, uint16_t *pressure )
{
    int16_t pressure_pa = 0;
    float voltage = 0;
    err_t error_flag = diffpress5_read_vout_avg ( ctx, DIFFPRESS5_NUM_CONVERSIONS, &voltage );
    pressure_pa = ( int16_t ) ( ( voltage - ctx->zero_press_offset ) / DIFFPRESS5_PRESSURE_SENS_PA );
    if ( pressure_pa < DIFFPRESS5_PRESSURE_PA_MIN )
    {
        pressure_pa = DIFFPRESS5_PRESSURE_PA_MIN;
    }
    else if ( pressure_pa > DIFFPRESS5_PRESSURE_PA_MAX )
    {
        pressure_pa = DIFFPRESS5_PRESSURE_PA_MAX;
    }
    if ( DIFFPRESS5_OK == error_flag )
    {
        *pressure = ( uint16_t ) pressure_pa;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
