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
 * @file hallcurrent15.c
 * @brief Hall Current 15 Click Driver.
 */

#include "hallcurrent15.h"

void hallcurrent15_cfg_setup ( hallcurrent15_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HALLCURRENT15_SET_DEV_ADDR;
    cfg->vref        = HALLCURRENT15_VREF_3V3;
    cfg->drv_sel     = HALLCURRENT15_DRV_SEL_ADC;
}

void hallcurrent15_drv_interface_selection ( hallcurrent15_cfg_t *cfg, hallcurrent15_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t hallcurrent15_init ( hallcurrent15_t *ctx, hallcurrent15_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( HALLCURRENT15_DRV_SEL_I2C == ctx->drv_sel ) 
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

    digital_in_init( &ctx->alr, cfg->alr );

    return HALLCURRENT15_OK;
}

err_t hallcurrent15_write_register ( hallcurrent15_t *ctx, uint8_t reg, uint16_t data_in )
{
    if ( reg > HALLCURRENT15_REG_HIGHEST_CONVERSION )
    {
        return HALLCURRENT15_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    if ( ( reg == HALLCURRENT15_REG_ALERT_STATUS ) || ( reg == HALLCURRENT15_REG_CONFIGURATION ) )
    {
        data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
        return i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
    else
    {
        data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
        return i2c_master_write( &ctx->i2c, data_buf, 3 );
    }
}

err_t hallcurrent15_read_register ( hallcurrent15_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( reg > HALLCURRENT15_REG_HIGHEST_CONVERSION )
    {
        return HALLCURRENT15_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    if ( ( reg == HALLCURRENT15_REG_ALERT_STATUS ) || ( reg == HALLCURRENT15_REG_CONFIGURATION ) )
    {
        err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 1 );
        *data_out = data_buf[ 1 ];
        return error_flag;
    }
    else
    {
        err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
        return error_flag;
    }
}

uint8_t hallcurrent15_get_alert_pin ( hallcurrent15_t *ctx )
{
    return digital_in_read ( &ctx->alr );
}

err_t hallcurrent15_read_raw_adc ( hallcurrent15_t *ctx, uint16_t *raw_adc ) 
{
    if ( HALLCURRENT15_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t reg_data;
        err_t err_flag = hallcurrent15_read_register ( ctx, HALLCURRENT15_REG_CONVERSION_RESULT, &reg_data );
        *raw_adc = ( reg_data >> 2 ) & HALLCURRENT15_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t hallcurrent15_read_voltage ( hallcurrent15_t *ctx, float *voltage ) 
{
    if ( HALLCURRENT15_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc;
        err_t err_flag = hallcurrent15_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) HALLCURRENT15_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t hallcurrent15_set_vref ( hallcurrent15_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( HALLCURRENT15_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return HALLCURRENT15_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t hallcurrent15_read_current ( hallcurrent15_t *ctx, float *current )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < HALLCURRENT15_NUM_CONVERSIONS )
    {
        if ( HALLCURRENT15_OK == hallcurrent15_read_voltage( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        else
        {
            timeout_cnt++;
            if ( timeout_cnt >= HALLCURRENT15_NUM_CONVERSIONS )
            {
                return HALLCURRENT15_ERROR;
            }
        }
    }
    *current = ( ( voltage_sum / HALLCURRENT15_NUM_CONVERSIONS ) - 
                 ( ctx->vref * HALLCURRENT15_ZERO_CURRENT_OFFSET ) ) / HALLCURRENT15_SENSITIVITY_V_TO_A;
    return HALLCURRENT15_OK;
}

// ------------------------------------------------------------------------- END
