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
 * @file vcpmonitor7.c
 * @brief VCP Monitor 7 Click Driver.
 */

#include "vcpmonitor7.h"

void vcpmonitor7_cfg_setup ( vcpmonitor7_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->ren = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VCPMONITOR7_DEVICE_ADDRESS;
    cfg->vref        = VCPMONITOR7_VREF;
    cfg->drv_sel     = VCPMONITOR7_DRV_SEL_I2C;
}

void vcpmonitor7_drv_interface_sel ( vcpmonitor7_cfg_t *cfg, vcpmonitor7_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t vcpmonitor7_init ( vcpmonitor7_t *ctx, vcpmonitor7_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( VCPMONITOR7_DRV_SEL_I2C == ctx->drv_sel ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->ren, cfg->ren );

    /* Enable both the reference buffer and the amplifier, reference buffer first */
    digital_out_high( &ctx->ren );
    Delay_1ms( );
    digital_out_high( &ctx->en );
    Delay_1ms( );

    return VCPMONITOR7_OK;
}

void vcpmonitor7_enable_device ( vcpmonitor7_t *ctx )
{
    digital_out_high( &ctx->en );
}

void vcpmonitor7_disable_device ( vcpmonitor7_t *ctx )
{
    digital_out_low( &ctx->en );
}

void vcpmonitor7_enable_ref ( vcpmonitor7_t *ctx )
{
    digital_out_high( &ctx->ren );
}

void vcpmonitor7_disable_ref ( vcpmonitor7_t *ctx )
{
    digital_out_low( &ctx->ren );
}

err_t vcpmonitor7_read_raw_adc ( vcpmonitor7_t *ctx, uint16_t *raw_adc ) 
{
    /* 
     * I2C read frame : S | slave_addr + R | A | MSB_byte | A | LSB_byte | NA | P
     *  - data[11:8] = MSB_byte[3:0]
     *  - data[7:0]  = LSB_byte[7:0]
     */
    if ( VCPMONITOR7_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ] = { 0 };
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & VCPMONITOR7_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t vcpmonitor7_read_voltage ( vcpmonitor7_t *ctx, float *voltage ) 
{
    if ( VCPMONITOR7_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        /* The on board ADC ( MCP3221 ) uses its own supply as the conversion reference */
        uint16_t raw_adc = 0;
        err_t err_flag = vcpmonitor7_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) VCPMONITOR7_ADC_NUM_OF_STEPS  );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t vcpmonitor7_read_voltage_avg ( vcpmonitor7_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    if ( 0 == num_conv )
    {
        return VCPMONITOR7_ERROR;
    }
    while ( cnt < num_conv )
    {
        if ( VCPMONITOR7_OK == vcpmonitor7_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > VCPMONITOR7_TIMEOUT_MS )
        {
            return VCPMONITOR7_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return VCPMONITOR7_OK;
}

err_t vcpmonitor7_read_diff_voltage ( vcpmonitor7_t *ctx, float *diff_volt )
{
    float voltage = 0;
    err_t error_flag = VCPMONITOR7_OK;

    /* 
     * VOUT = G * ( V_INP - V_INN ) + VREF
     *  - G = 0.5 (for INA151C variant)
     *  - VREF = VCC / 2 (schematic R14/R11 voltage divider)
     *
     * => V_DIFF = ( VOUT - VCC / 2 ) / 0.5
     */
    error_flag = vcpmonitor7_read_voltage_avg( ctx, VCPMONITOR7_NUM_CONVERSIONS, &voltage );
    if ( VCPMONITOR7_OK == error_flag )
    {
        *diff_volt = ( voltage - ( ctx->vref / VCPMONITOR7_MID_SUPPLY_DIV ) ) / VCPMONITOR7_AMP_GAIN;
    }

    return error_flag;
}

err_t vcpmonitor7_set_vref ( vcpmonitor7_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( VCPMONITOR7_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return VCPMONITOR7_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

// ------------------------------------------------------------------------- END
