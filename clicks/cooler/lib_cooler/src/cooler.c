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
 * @file cooler.c
 * @brief Cooler Click Driver.
 */

#include "cooler.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void cooler_cfg_setup ( cooler_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COOLER_SET_DEV_ADDR_0;
    cfg->vref        = COOLER_VREF_3V3;
}


err_t cooler_init ( cooler_t *ctx, cooler_cfg_t *cfg ) 
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

    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->in1, cfg->in1 );

    digital_in_init( &ctx->alr, cfg->alr );

    return COOLER_OK;
}

err_t cooler_default_cfg ( cooler_t *ctx ) 
{
    uint16_t device_id = DUMMY;
    err_t err_flag = cooler_get_device_id( ctx, &device_id );
    if ( COOLER_DEVICE_ID == device_id )
    {
        err_flag |= cooler_data_write( ctx, COOLER_REG_CONFIGURATION, 
                                            COOLER_CFG_MODEON | 
                                            COOLER_CFG_ALERTEN | 
                                            COOLER_CFG_TRANSC );
        Delay_10ms( );
        err_flag |= cooler_data_write( ctx, COOLER_REG_STATUS_MASK_AND_ENABLE, 
                                            COOLER_STAT_ALERTEN | 
                                            COOLER_STAT_CRTEN );
        Delay_10ms( );                                                                            
    }
    else
    {
        err_flag = COOLER_ERROR;
    }
    return err_flag;
}

err_t cooler_generic_write ( cooler_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t cooler_generic_read ( cooler_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t cooler_data_write ( cooler_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ] = ( uint8_t )   data_in;
    return cooler_generic_write( ctx, reg, data_buf, 2 );
}

err_t cooler_data_read ( cooler_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = cooler_generic_read ( ctx, reg, data_buf, 2 );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    return err_flag;
}

err_t cooler_get_device_id ( cooler_t *ctx, uint16_t *device_id )
{
    return cooler_data_read( ctx, COOLER_REG_DEVICE_ID, device_id );
}

err_t cooler_sensor_voltage ( cooler_t *ctx, float *voltage )
{
    uint16_t data_buf = 0;
    int16_t vtg_raw_data = 0;
    err_t err_flag = cooler_data_read( ctx, COOLER_REG_SENSOR_VOLTAGE, &data_buf );
    vtg_raw_data = ( int16_t ) data_buf;
    *voltage = ( float ) vtg_raw_data;
    *voltage *= COOLER_SENSOR_VTG_SENS;
    return err_flag;
}

err_t cooler_get_object_temperature ( cooler_t *ctx, float *temperature )
{
    uint16_t data_buf = DUMMY;
    int16_t temp_obj = DUMMY;
    err_t err_flag = cooler_data_read( ctx, COOLER_REG_OBJECT_TEMPERATURE, &data_buf );
    temp_obj = ( int16_t ) data_buf;
    temp_obj >>= 2;
    *temperature = ( float ) temp_obj;
    *temperature *= COOLER_TEMPERATURE_SENS;
    return err_flag;
}

uint8_t cooler_get_alert ( cooler_t *ctx )
{
    return  digital_in_read( &ctx->alr );
}

err_t cooler_read_raw_adc ( cooler_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t cooler_read_voltage ( cooler_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t cooler_set_vref ( cooler_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void cooler_set_in1_pin ( cooler_t *ctx ) 
{
    digital_out_high( &ctx->in1 );
}

void cooler_clear_in1_pin ( cooler_t *ctx ) 
{
    digital_out_low( &ctx->in1 );
}

void cooler_set_in2_pin ( cooler_t *ctx ) 
{
    digital_out_high( &ctx->in2 );
}

void cooler_clear_in2_pin ( cooler_t *ctx ) 
{
    digital_out_low( &ctx->in2 );
}

err_t cooler_set_out_state ( cooler_t *ctx, cooler_out_state_t out_state )
{
    err_t err_flag = COOLER_OK;
    switch ( out_state )
    {
        case ( COOLER_ENABLE ):
        {
            cooler_set_in1_pin( ctx );
            cooler_clear_in2_pin( ctx );
            break;
        }
        case ( COOLER_DISABLE ):
        {
            cooler_set_in1_pin( ctx );
            cooler_set_in2_pin( ctx );
            break;
        }
        default:
        {
           err_flag = COOLER_ERROR;
           break;
        }
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END
