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
 * @file stepdown15.c
 * @brief Step Down 15 Click Driver.
 */

#include "stepdown15.h"
#include "math.h"

static float stepdown15_linear11_to_float ( uint16_t raw_data );

void stepdown15_cfg_setup ( stepdown15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alert = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = STEPDOWN15_DEVICE_ADDRESS_ADDR_GND;
}

err_t stepdown15_init ( stepdown15_t *ctx, stepdown15_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->pwm, cfg->pwm );

    digital_in_init( &ctx->alert, cfg->alert );
    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t stepdown15_default_cfg ( stepdown15_t *ctx ) 
{
    err_t error_flag = STEPDOWN15_OK;

    stepdown15_disable_device ( ctx );
    stepdown15_enable_device ( ctx );

    if ( STEPDOWN15_OK == error_flag )
    {
        error_flag = stepdown15_write_reg( ctx, STEPDOWN15_REG_OPERATION, 
                                           STEPDOWN15_OPERATION_OUTPUT_ON | 
                                           STEPDOWN15_OPERATION_PDOWN_IMMEDIATELY | 
                                           STEPDOWN15_OPERATION_VCMD_COMMAND );
    }

    return error_flag;
}

err_t stepdown15_write_reg ( stepdown15_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return stepdown15_write_regs( ctx, reg, &data_in, 1 );
}

err_t stepdown15_write_regs ( stepdown15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t stepdown15_write_reg_16 ( stepdown15_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return stepdown15_write_regs( ctx, reg, data_buf, 2 );
}

err_t stepdown15_read_reg ( stepdown15_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return stepdown15_read_regs( ctx, reg, data_out, 1 );
}

err_t stepdown15_read_regs ( stepdown15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t stepdown15_read_reg_16 ( stepdown15_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = STEPDOWN15_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag = stepdown15_read_regs( ctx, reg, data_buf, 2 );
    if ( ( STEPDOWN15_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

void stepdown15_enable_device ( stepdown15_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

void stepdown15_disable_device ( stepdown15_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
}

void stepdown15_set_pwm_pin ( stepdown15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->pwm, state );
}

uint8_t stepdown15_get_pg_pin ( stepdown15_t *ctx )
{
    return !!digital_in_read ( &ctx->pg );
}

uint8_t stepdown15_get_alert_pin ( stepdown15_t *ctx )
{
    return !!digital_in_read ( &ctx->alert );
}

err_t stepdown15_set_vout ( stepdown15_t *ctx, float voltage )
{
    float vout = voltage;

    if ( vout < STEPDOWN15_VOUT_MIN )
    {
        vout = STEPDOWN15_VOUT_MIN;
    }

    if ( vout > STEPDOWN15_VOUT_MAX )
    {
        vout = STEPDOWN15_VOUT_MAX;
    }

    return stepdown15_write_reg_16( ctx, STEPDOWN15_REG_VOUT_COMMAND_LOWER, 
                                    ( uint16_t )( vout * STEPDOWN15_VOUT_RES + 
                                                  STEPDOWN15_ROUND_TO_NEAREAST_INT ) );
}

err_t stepdown15_read_pvin ( stepdown15_t *ctx, float *voltage )
{
    err_t error_flag = STEPDOWN15_OK;
    uint16_t raw_data = 0;

    error_flag = stepdown15_read_reg_16 ( ctx, STEPDOWN15_REG_PVIN_REPORT_LOWER, &raw_data );

    if ( ( STEPDOWN15_OK == error_flag ) && ( NULL != voltage ) )
    {
        *voltage = stepdown15_linear11_to_float( raw_data );
    }

    return error_flag;
}

err_t stepdown15_read_vout ( stepdown15_t *ctx, float *voltage )
{
    err_t error_flag = STEPDOWN15_OK;
    uint16_t raw_data = 0;

    error_flag = stepdown15_read_reg_16 ( ctx, STEPDOWN15_REG_VOUT_REPORT_LOWER, &raw_data );

    if ( ( STEPDOWN15_OK == error_flag ) && ( NULL != voltage ) )
    {
        *voltage = ( ( int16_t ) raw_data ) / STEPDOWN15_VOUT_RES;
    }

    return error_flag;
}

err_t stepdown15_read_temperature ( stepdown15_t *ctx, float *temp_c )
{
    err_t error_flag = STEPDOWN15_OK;
    uint16_t raw_data = 0;
    uint8_t read_cnt = 0;
    float temp_avg = 0;

    while ( ( read_cnt < STEPDOWN15_TEMP_NUM_MEASUREMENTS ) && ( STEPDOWN15_OK == error_flag ) )
    {
        error_flag = stepdown15_read_reg_16 ( ctx, STEPDOWN15_REG_TEMP_REPORT_LOWER, &raw_data );
        temp_avg += stepdown15_linear11_to_float( raw_data );
        read_cnt++;
        Delay_1ms ( );
    }
    if ( ( STEPDOWN15_OK == error_flag ) && ( NULL != temp_c ) )
    {
        *temp_c = temp_avg / STEPDOWN15_TEMP_NUM_MEASUREMENTS;
    }

    return error_flag;
}

err_t stepdown15_read_vcc ( stepdown15_t *ctx, float *voltage )
{
    err_t error_flag = STEPDOWN15_OK;
    uint16_t raw_data = 0;

    error_flag = stepdown15_read_reg_16 ( ctx, STEPDOWN15_REG_VCC_REPORT_LOWER, &raw_data );

    if ( STEPDOWN15_OK == error_flag )
    {
        *voltage = stepdown15_linear11_to_float( raw_data );
    }

    return error_flag;
}

static float stepdown15_linear11_to_float ( uint16_t raw_data )
{
    int16_t exponent = 0;
    int16_t mantissa = 0;

    exponent = ( raw_data >> 11 ) & 0x1F;
    if ( exponent & 0x10 )
    {
        exponent |= 0xFFE0;
    }
    
    mantissa = raw_data & 0x07FF;
    if ( mantissa & 0x0400 )
    {
        mantissa |= 0xF800;
    }

    return mantissa * pow ( 2.0, exponent );
}

// ------------------------------------------------------------------------- END
