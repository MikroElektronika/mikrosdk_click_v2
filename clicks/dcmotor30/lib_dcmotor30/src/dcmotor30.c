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
 * @file dcmotor30.c
 * @brief DC Motor 30 Click Driver.
 */

#include "dcmotor30.h"

void dcmotor30_cfg_setup ( dcmotor30_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ipropi = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR30_DEVICE_ADDRESS_A1A0_00;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = DCMOTOR30_VREF_DEFAULT;
}

err_t dcmotor30_init ( dcmotor30_t *ctx, dcmotor30_cfg_t *cfg ) 
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->ipropi;

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
    digital_out_low ( &ctx->in1 );
    digital_out_low ( &ctx->in2 );

    digital_in_init( &ctx->fault, cfg->fault );

    return I2C_MASTER_SUCCESS;
}

err_t dcmotor30_default_cfg ( dcmotor30_t *ctx ) 
{
    err_t error_flag = DCMOTOR30_OK;
    error_flag |= dcmotor30_calib_offset ( ctx );
    error_flag |= dcmotor30_write_reg ( ctx, DCMOTOR30_REG_CONFIG0, DCMOTOR30_CONFIG0_EN_OUT | 
                                                                    DCMOTOR30_CONFIG0_EN_OVP | 
                                                                    DCMOTOR30_CONFIG0_EN_STALL | 
                                                                    DCMOTOR30_CONFIG0_CLR_FLT );
    return error_flag;
}

err_t dcmotor30_write_reg ( dcmotor30_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t dcmotor30_read_reg ( dcmotor30_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t dcmotor30_read_adc_raw ( dcmotor30_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t dcmotor30_read_adc_volt ( dcmotor30_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t dcmotor30_read_adc_volt_avg ( dcmotor30_t *ctx, uint16_t num_conv, float *volt_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( DCMOTOR30_OK == dcmotor30_read_adc_volt ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            timeout_cnt = 0;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > DCMOTOR30_TIMEOUT_MS )
        {
            return DCMOTOR30_ERROR;
        }
    }
    *volt_avg = ( voltage_sum / num_conv );
    return DCMOTOR30_OK;
}

err_t dcmotor30_set_adc_vref ( dcmotor30_t *ctx, float vref ) 
{
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void dcmotor30_set_in1_pin ( dcmotor30_t *ctx )
{
    digital_out_high( &ctx->in1 );
}

void dcmotor30_clear_in1_pin ( dcmotor30_t *ctx )
{
    digital_out_low( &ctx->in1 );
}

void dcmotor30_set_in2_pin ( dcmotor30_t *ctx )
{
    digital_out_high( &ctx->in2 );
}

void dcmotor30_clear_in2_pin ( dcmotor30_t *ctx )
{
    digital_out_low( &ctx->in2 );
}

uint8_t dcmotor30_get_fault_pin ( dcmotor30_t *ctx )
{
    return digital_in_read ( &ctx->fault );
}

void dcmotor30_drive_motor ( dcmotor30_t *ctx, uint8_t state )
{
    switch ( state )
    {
        case DCMOTOR30_MOTOR_COAST:
        {
            digital_out_low ( &ctx->in1 );
            digital_out_low ( &ctx->in2 );
            break;
        }
        case DCMOTOR30_MOTOR_FORWARD:
        {
            digital_out_high ( &ctx->in1 );
            digital_out_low ( &ctx->in2 );
            break;
        }
        case DCMOTOR30_MOTOR_REVERSE:
        {
            digital_out_low ( &ctx->in1 );
            digital_out_high ( &ctx->in2 );
            break;
        }
        case DCMOTOR30_MOTOR_BRAKE:
        {
            digital_out_high ( &ctx->in1 );
            digital_out_high ( &ctx->in2 );
            break;
        }
        default:
        {
            break;
        }
    }
}

err_t dcmotor30_clear_fault ( dcmotor30_t *ctx )
{
    err_t error_flag = DCMOTOR30_OK;
    uint8_t config0 = 0;
    dcmotor30_read_reg ( ctx, DCMOTOR30_REG_CONFIG0, &config0 );
    config0 |= DCMOTOR30_CONFIG0_CLR_FLT;
    dcmotor30_write_reg ( ctx, DCMOTOR30_REG_CONFIG0, config0 );
    return error_flag;
}

err_t dcmotor30_calib_offset ( dcmotor30_t *ctx )
{
    float voltage = 0;
    dcmotor30_drive_motor ( ctx, DCMOTOR30_MOTOR_COAST );
    Delay_1sec ( );
    Delay_1sec ( );
    err_t error_flag = dcmotor30_read_adc_volt_avg ( ctx, DCMOTOR30_NUM_CONVERSIONS, &voltage );
    ctx->zero_curr_offset = voltage;
    return error_flag;
}

err_t dcmotor30_get_out_current ( dcmotor30_t *ctx, float *current )
{
    float voltage = 0;
    err_t error_flag = dcmotor30_read_adc_volt_avg ( ctx, DCMOTOR30_NUM_CONVERSIONS, &voltage );
    if ( ( DCMOTOR30_OK == error_flag ) && ( NULL != current ) )
    {
        voltage -= ctx->zero_curr_offset;
        if ( voltage < 0 )
        {
            voltage = 0;
        }
        *current = voltage / DCMOTOR30_RIPROPI_V_TO_MA / DCMOTOR30_SCALING_FACTOR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
