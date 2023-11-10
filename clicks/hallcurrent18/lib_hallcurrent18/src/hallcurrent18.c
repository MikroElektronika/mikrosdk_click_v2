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
 * @file hallcurrent18.c
 * @brief Hall Current 18 Click Driver.
 */

#include "hallcurrent18.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY    0x00

void hallcurrent18_cfg_setup ( hallcurrent18_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT18_SET_DEV_ADDR;
    cfg->vref        = HALLCURRENT18_VREF_3V3;
    cfg->zero_vref   = HALLCURRENT18_HALF_SCALE_3V3;
    cfg->drv_sel     = HALLCURRENT18_DRV_SEL_I2C;
}

void hallcurrent18_drv_interface_selection ( hallcurrent18_cfg_t *cfg, hallcurrent18_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t hallcurrent18_init ( hallcurrent18_t *ctx, hallcurrent18_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;
    ctx->zero_vref = cfg->zero_vref;

    if ( HALLCURRENT18_DRV_SEL_I2C == ctx->drv_sel ) 
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
    
    return HALLCURRENT18_OK;
}

err_t hallcurrent18_default_cfg ( hallcurrent18_t *ctx ) 
{
    float current = DUMMY;
    return hallcurrent18_read_current( ctx, &current );
}

err_t hallcurrent18_read_raw_adc ( hallcurrent18_t *ctx, uint16_t *raw_adc ) 
{
    if ( HALLCURRENT18_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ] = { 0 };
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] ) & HALLCURRENT18_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t hallcurrent18_read_voltage ( hallcurrent18_t *ctx, float *voltage ) 
{
    if ( HALLCURRENT18_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc = DUMMY;
        err_t err_flag = hallcurrent18_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) HALLCURRENT18_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t hallcurrent18_set_vref ( hallcurrent18_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( HALLCURRENT18_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return HALLCURRENT18_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t hallcurrent18_read_current ( hallcurrent18_t *ctx, float *current ) 
{
    float voltage = DUMMY, vtg_sum = DUMMY;
    uint16_t cnt = DUMMY;
    err_t err_flag = HALLCURRENT18_OK;
    while ( cnt < HALLCURRENT18_ADC_NUM_OF_MEASURE )
    {
        err_flag |= hallcurrent18_read_voltage ( ctx, &voltage );
        vtg_sum += voltage * HALLCURRENT18_CONV_TO_MILI;
        cnt++;
        Delay_1ms( );
    }
    vtg_sum /= ( float ) cnt;
    *current = vtg_sum;
    *current -= ctx->zero_vref * HALLCURRENT18_CONV_TO_MILI;
    *current /= HALLCURRENT18_SENSITIVITY_MV_A;
    return err_flag;
}

err_t hallcurrent18_set_zero_ref ( hallcurrent18_t *ctx ) 
{
    float voltage = DUMMY, vtg_sum = DUMMY;
    uint16_t cnt = DUMMY;
    err_t err_flag = HALLCURRENT18_OK;
    while ( cnt < HALLCURRENT18_ADC_NUM_OF_MEASURE )
    {
        err_flag |= hallcurrent18_read_voltage ( ctx, &voltage );
        vtg_sum += voltage;
        cnt++;
        Delay_1ms( );
    }
    vtg_sum /= ( float ) cnt;
    ctx->zero_vref = vtg_sum;
    return err_flag;
}

// ------------------------------------------------------------------------- END
