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
 * @file angle7.c
 * @brief Angle 7 Click Driver.
 */

#include "angle7.h"

void angle7_cfg_setup ( angle7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ANGLE7_DEVICE_ADDRESS;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t angle7_init ( angle7_t *ctx, angle7_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t angle7_default_cfg ( angle7_t *ctx ) 
{
    err_t error_flag = ANGLE7_OK;
    angle7_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= angle7_write_two_bytes ( ctx, ANGLE7_REG_CONF_MSB, ANGLE7_CONF_WATCHDOG_OFF | 
                                                                     ANGLE7_CONF_FTH_SLOW | 
                                                                     ANGLE7_CONF_SF_16X | 
                                                                     ANGLE7_CONF_PWMF_115HZ | 
                                                                     ANGLE7_CONF_OUTS_ANALOG_FULL | 
                                                                     ANGLE7_CONF_HYST_OFF | 
                                                                     ANGLE7_CONF_PM_NOM );
    error_flag |= angle7_set_start_position ( ctx, ANGLE7_ZERO_POSITION );
    error_flag |= angle7_set_stop_position ( ctx, ANGLE7_FULL_CIRCLE );
    return error_flag;
}

err_t angle7_generic_write ( angle7_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t angle7_generic_read ( angle7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t angle7_write_two_bytes ( angle7_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ];
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    return angle7_generic_write( ctx, reg, data_buf, 2 );
}

err_t angle7_read_two_bytes ( angle7_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ];
    err_t error_flag = angle7_generic_read( ctx, reg, data_buf, 2 );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t angle7_read_an_pin_value ( angle7_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t angle7_read_an_pin_voltage ( angle7_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

uint8_t angle7_get_int_pin ( angle7_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void angle7_enable_device ( angle7_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void angle7_disable_device ( angle7_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t angle7_set_start_position ( angle7_t *ctx, float angle )
{
    if ( ( angle < ANGLE7_ZERO_POSITION ) || ( angle > ANGLE7_FULL_CIRCLE ) )
    {
        return ANGLE7_ERROR;
    }
    uint16_t start_position = ( uint16_t ) ( angle * ANGLE7_RESOLUTION / ANGLE7_FULL_CIRCLE ) & ANGLE7_RESOLUTION;
    err_t error_flag = angle7_write_two_bytes( ctx, ANGLE7_REG_ZPOS_MSB, start_position );
    uint16_t check_start_position;
    error_flag |= angle7_read_two_bytes( ctx, ANGLE7_REG_ZPOS_MSB, &check_start_position );
    if ( ( ANGLE7_OK == error_flag ) && ( check_start_position == start_position ) )
    {
        ctx->start_position = angle;
        return ANGLE7_OK;
    }
    return ANGLE7_ERROR;
}

err_t angle7_get_start_position ( angle7_t *ctx, float *angle )
{
    uint16_t start_position;
    if ( ANGLE7_OK == angle7_read_two_bytes( ctx, ANGLE7_REG_ZPOS_MSB, &start_position ) )
    {
        *angle = ( float ) start_position / ANGLE7_RESOLUTION * ANGLE7_FULL_CIRCLE;
        ctx->start_position = *angle;
        return ANGLE7_OK;
    }
    return ANGLE7_ERROR;
}

err_t angle7_set_stop_position ( angle7_t *ctx, float angle )
{
    if ( ( angle < ANGLE7_ZERO_POSITION ) || ( angle > ANGLE7_FULL_CIRCLE ) )
    {
        return ANGLE7_ERROR;
    }
    uint16_t stop_position = ( uint16_t ) ( angle * ANGLE7_RESOLUTION / ANGLE7_FULL_CIRCLE ) & ANGLE7_RESOLUTION;
    err_t error_flag = angle7_write_two_bytes( ctx, ANGLE7_REG_MPOS_MSB, stop_position );
    uint16_t check_stop_position;
    error_flag |= angle7_read_two_bytes( ctx, ANGLE7_REG_MPOS_MSB, &check_stop_position );
    if ( ( ANGLE7_OK == error_flag ) && ( check_stop_position == stop_position ) )
    {
        ctx->stop_position = angle;
        return error_flag;
    }
    return ANGLE7_ERROR;
}

err_t angle7_get_stop_position ( angle7_t *ctx, float *angle )
{
    uint16_t stop_position;
    if ( ANGLE7_OK == angle7_read_two_bytes( ctx, ANGLE7_REG_MPOS_MSB, &stop_position ) )
    {
        *angle = ( float ) stop_position / ANGLE7_RESOLUTION * ANGLE7_FULL_CIRCLE;
        ctx->stop_position = *angle;
        return ANGLE7_OK;
    }
    return ANGLE7_ERROR;
}

err_t angle7_get_raw_angle ( angle7_t *ctx, float *angle )
{
    uint16_t raw_angle;
    err_t error_flag = angle7_read_two_bytes( ctx, ANGLE7_REG_RAW_ANGLE_MSB, &raw_angle );
    *angle = ( float ) raw_angle / ANGLE7_RESOLUTION * ANGLE7_FULL_CIRCLE;
    return error_flag;
}

err_t angle7_get_angle ( angle7_t *ctx, float *angle )
{
    uint16_t cal_angle;
    err_t error_flag = angle7_read_two_bytes( ctx, ANGLE7_REG_ANGLE_MSB, &cal_angle );
    *angle = ( float ) cal_angle * ( ctx->stop_position - ctx->start_position ) / ANGLE7_RESOLUTION;
    return error_flag;
}

err_t angle7_get_status ( angle7_t *ctx, uint8_t *status )
{
    return angle7_generic_read ( ctx, ANGLE7_REG_STATUS, status, 1 );
}

err_t angle7_get_agc ( angle7_t *ctx, uint8_t *agc )
{
    return angle7_generic_read ( ctx, ANGLE7_REG_AGC, agc, 1 );
}

err_t angle7_get_magnitude ( angle7_t *ctx, uint16_t *magnitude )
{
    return angle7_read_two_bytes ( ctx, ANGLE7_REG_MAGNITUDE_MSB, magnitude );
}

// ------------------------------------------------------------------------- END
