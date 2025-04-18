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
 * @file thermostat5.c
 * @brief Thermostat 5 Click Driver.
 */

#include "thermostat5.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void thermostat5_cfg_setup ( thermostat5_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->on  = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMOSTAT5_SET_DEV_ADDR;
    cfg->vref        = THERMOSTAT5_VREF_3V3;
    cfg->drv_sel     = THERMOSTAT5_DRV_SEL_I2C;
}

void thermostat5_drv_interface_sel ( thermostat5_cfg_t *cfg, thermostat5_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t thermostat5_init ( thermostat5_t *ctx, thermostat5_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( THERMOSTAT5_DRV_SEL_I2C == ctx->drv_sel ) 
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

    digital_out_init( &ctx->on, cfg->on );

    return THERMOSTAT5_OK;
}

err_t thermostat5_read_raw_adc ( thermostat5_t *ctx, uint16_t *raw_adc ) 
{
    if ( THERMOSTAT5_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t data_buf[ 2 ] = { 0 };
        err_t err_flag = i2c_master_read( &ctx->i2c, data_buf, 2 );
        *raw_adc = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        *raw_adc &= THERMOSTAT5_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t thermostat5_read_voltage ( thermostat5_t *ctx, float *voltage ) 
{
    if ( THERMOSTAT5_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc;
        err_t err_flag = thermostat5_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) THERMOSTAT5_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t thermostat5_set_vref ( thermostat5_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( THERMOSTAT5_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return THERMOSTAT5_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t thermostat5_get_temperature ( thermostat5_t *ctx, float *temperature ) 
{
    uint16_t raw_adc = DUMMY;
    float inv_t0 = THERMOSTAT5_INVERTED_VALUE / THERMOSTAT5_ROOM_TEMP_IN_K;
    float inv_beta = THERMOSTAT5_INVERTED_VALUE / THERMOSTAT5_THERMISOR_BETA;
    err_t err_flag = thermostat5_read_raw_adc( ctx, &raw_adc );
    *temperature = THERMOSTAT5_INVERTED_VALUE;
    *temperature /= ( inv_t0 + inv_beta * ( log( ( ( float ) THERMOSTAT5_ADC_RESOLUTION / 
                                                   ( float ) raw_adc ) - 
                                                   THERMOSTAT5_INVERTED_VALUE ) ) );
    *temperature -= THERMOSTAT5_TEMP_K_TO_C;
    return err_flag;
}

void thermostat5_set_relay ( thermostat5_t *ctx, uint8_t relay ) 
{
   digital_out_write( &ctx->on, relay );
}

// ------------------------------------------------------------------------- END
