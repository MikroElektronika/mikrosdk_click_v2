/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file hallcurrent27.c
 * @brief Hall Current 27 Click Driver.
 */

#include "hallcurrent27.h"

void hallcurrent27_cfg_setup ( hallcurrent27_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT27_DEVICE_ADDRESS;
    cfg->vref        = HALLCURRENT27_VREF;
    cfg->drv_sel     = HALLCURRENT27_DRV_SEL_ADC;
}

void hallcurrent27_drv_interface_sel ( hallcurrent27_cfg_t *cfg, hallcurrent27_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t hallcurrent27_init ( hallcurrent27_t *ctx, hallcurrent27_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    /* Nominal values derived from the sensor transfer function and the on-board R3/R7 divider */
    ctx->zero_curr_offset = HALLCURRENT27_ZERO_CURR_OFFSET;
    ctx->data_resolution = HALLCURRENT27_DATA_RESOLUTION;

    if ( HALLCURRENT27_DRV_SEL_I2C == ctx->drv_sel ) 
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

    Delay_100ms( );

    return HALLCURRENT27_OK;
}

err_t hallcurrent27_read_raw_adc ( hallcurrent27_t *ctx, uint16_t *raw_adc ) 
{
    if ( HALLCURRENT27_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        /* 
         * I2C read frame : S | sl_addr + R | A | 0 0 0 0 D11..D8 | A | D7..D0 | N | P
         * The conversion is triggered by the read itself and completes before the first data byte is clocked out.
         */
        uint8_t rx_buf[ 2 ] = { 0 };
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & HALLCURRENT27_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t hallcurrent27_read_voltage ( hallcurrent27_t *ctx, float *voltage ) 
{
    if ( HALLCURRENT27_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc = 0;
        err_t err_flag = hallcurrent27_read_raw_adc( ctx, &raw_adc );

        /* The MCP3221 uses its own supply as the ADC reference ( VDD = VCC ) */
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) HALLCURRENT27_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t hallcurrent27_read_voltage_avg ( hallcurrent27_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    if ( 0 == num_conv )
    {
        return HALLCURRENT27_ERROR;
    }
    while ( cnt < num_conv )
    {
        if ( HALLCURRENT27_OK == hallcurrent27_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > HALLCURRENT27_TIMEOUT_MS )
        {
            return HALLCURRENT27_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return HALLCURRENT27_OK;
}

err_t hallcurrent27_set_vref ( hallcurrent27_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( HALLCURRENT27_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return HALLCURRENT27_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t hallcurrent27_calib_offset ( hallcurrent27_t *ctx )
{
    float voltage = 0;
    err_t error_flag = HALLCURRENT27_OK;

    /* Use zero-current voltage offset instead of nominal value offset */
    error_flag |= hallcurrent27_read_voltage_avg( ctx, HALLCURRENT27_NUM_CONVERSIONS, &voltage );
    if ( HALLCURRENT27_OK == error_flag )
    {
        ctx->zero_curr_offset = voltage;
    }

    return error_flag;
}

err_t hallcurrent27_calib_resolution ( hallcurrent27_t *ctx, float calib_current )
{
    float voltage = 0;
    err_t error_flag = HALLCURRENT27_OK;

    /* Calculate the actual current-to-voltage transfer ratio at a known current */
    error_flag |= hallcurrent27_read_voltage_avg( ctx, HALLCURRENT27_NUM_CONVERSIONS, &voltage );
    if ( HALLCURRENT27_OK == error_flag )
    {
        ctx->data_resolution = calib_current / ( voltage - ctx->zero_curr_offset );
    }

    return error_flag;
}

err_t hallcurrent27_read_current ( hallcurrent27_t *ctx, float *current )
{
    float voltage = 0;
    err_t error_flag = HALLCURRENT27_OK;

    /* Remove the calibrated zero-current offset to allow negative values presentation */
    error_flag |= hallcurrent27_read_voltage_avg( ctx, HALLCURRENT27_NUM_CONVERSIONS, &voltage );
    if ( HALLCURRENT27_OK == error_flag )
    {
        *current = ( voltage - ctx->zero_curr_offset ) * ctx->data_resolution;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
