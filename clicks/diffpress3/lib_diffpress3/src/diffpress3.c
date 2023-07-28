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
 * @file diffpress3.c
 * @brief Diff Press 3 Click Driver.
 */

#include "diffpress3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                          0

void diffpress3_cfg_setup ( diffpress3_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIFFPRESS3_SET_DEV_ADDR;
    cfg->vref        = DIFFPRESS3_VREF_3V3;
    cfg->drv_sel     = DIFFPRESS3_DRV_SEL_I2C;
    cfg->an_sel      = DIFFPRESS3_AN_SEL_2V5;
    cfg->data_sel    = DIFFPRESS3_RAW_DATA_PRESSURE;
}

void diffpress3_drv_interface_selection ( diffpress3_cfg_t *cfg, diffpress3_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t diffpress3_init ( diffpress3_t *ctx, diffpress3_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;
    ctx->data_sel = cfg->data_sel;

    if ( DIFFPRESS3_DRV_SEL_I2C == ctx->drv_sel ) 
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
        ctx->an_sel = cfg->an_sel;
        
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
    return DIFFPRESS3_OK;
}

err_t diffpress3_read_raw_adc ( diffpress3_t *ctx, uint16_t *raw_adc, diffpress3_d_sel_t data_sel ) 
{
    ctx->data_sel = data_sel;
    if ( DIFFPRESS3_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 4 ] = { 0 };
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 4 );
        *raw_adc = rx_buf[ data_sel ];
        *raw_adc <<= 8;
        *raw_adc |= rx_buf[ data_sel + 1 ];
        *raw_adc &= DIFFPRESS3_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t diffpress3_read_voltage ( diffpress3_t *ctx, float *voltage ) 
{
    if ( DIFFPRESS3_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc = DUMMY;
        err_t err_flag = diffpress3_read_raw_adc( ctx, &raw_adc, ctx->data_sel );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) DIFFPRESS3_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t diffpress3_set_vref ( diffpress3_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( DIFFPRESS3_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return DIFFPRESS3_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t diffpress3_get_pressure ( diffpress3_t *ctx, float *pressure ) 
{
    err_t err_flag = DIFFPRESS3_OK;
    uint16_t press_data = DUMMY, temp_data = DUMMY;
    if ( DIFFPRESS3_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        err_flag |= diffpress3_get_digit_out_data( ctx, &press_data, &temp_data );
        *pressure = ( float ) press_data;
        *pressure -= DIFFPRESS3_DIG_OUTP_MIN;
        *pressure *= DIFFPRESS3_SENP;
        *pressure += DIFFPRESS3_PMIN;
    }
    else
    {
        float voltage = DUMMY;
        err_flag |= diffpress3_read_voltage( ctx, &voltage );
        *pressure = ( float ) voltage;
        *pressure -= ( DIFFPRESS3_AN_OUTOFF / ( float ) ctx->an_sel );
        *pressure *= ( DIFFPRESS3_AN_SENP / ( float ) ctx->an_sel );
    }
    return err_flag;
}

err_t diffpress3_get_temperature ( diffpress3_t *ctx, float *temperature ) 
{
    err_t err_flag = DIFFPRESS3_ERROR;
    uint16_t press_data = DUMMY, temp_data = DUMMY;
    if ( DIFFPRESS3_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        err_flag = diffpress3_get_digit_out_data( ctx, &press_data, &temp_data );
        *temperature = ( float ) temp_data;
        *temperature -= DIFFPRESS3_OUTT_MIN;
        *temperature *= DIFFPRESS3_SENT;
    }
    return err_flag;
}

err_t diffpress3_get_digit_out_data ( diffpress3_t *ctx, uint16_t *press_data, uint16_t *temp_data ) 
{
    if ( DIFFPRESS3_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 8 ] = { 0 };
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 4 );
        *press_data = rx_buf[ 0 ];
        *press_data <<= 8;
        *press_data |= rx_buf[ 1 ];
        *press_data &= DIFFPRESS3_PRES;
        *temp_data = rx_buf[ 2 ];
        *temp_data <<= 8;
        *temp_data |= rx_buf[ 3 ];
        *temp_data &= DIFFPRESS3_TRES;
        return err_flag;
    }
    else
    {
        return DIFFPRESS3_ERROR;
    }
}

// ------------------------------------------------------------------------- END
