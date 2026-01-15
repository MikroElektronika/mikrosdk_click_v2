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
 * @file pir4.c
 * @brief PIR 4 Click Driver.
 */

#include "pir4.h"

void pir4_cfg_setup ( pir4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PIR4_DEVICE_ADDRESS_0;
}

err_t pir4_init ( pir4_t *ctx, pir4_cfg_t *cfg ) 
{
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_100ms ( );

    pir4_enable_device ( ctx );
    Delay_100ms ( );

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

    return I2C_MASTER_SUCCESS;
}

err_t pir4_default_cfg ( pir4_t *ctx ) 
{
    err_t error_flag = PIR4_OK;

    error_flag |= pir4_set_operating_state ( ctx, PIR4_OP_STATE_ACTIVE );
    error_flag |= pir4_set_odr ( ctx, PIR4_ODR_DEFAULT );
    error_flag |= pir4_set_pass_filter ( ctx, PIR4_LPF_DEFAULT, PIR4_HPF_DEFAULT );
    error_flag |= pir4_set_threshold ( ctx, PIR4_THRESHOLD_COUNT_DEFAULT, 
                                            PIR4_THRESHOLD_HIGH_DEFAULT, 
                                            PIR4_THRESHOLD_LOW_DEFAULT );
    error_flag |= pir4_set_timer ( ctx, PIR4_WINDOW_TIME_DEFAULT );
    error_flag |= pir4_set_interrupt ( ctx, PIR4_INT_SEL_DEFAULT );
    error_flag |= pir4_read_overcount ( ctx, NULL, NULL );
    error_flag |= pir4_clear_status ( ctx, PIR4_STATUS_ALL );

    return error_flag;
}

err_t pir4_write_regs ( pir4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t pir4_read_regs ( pir4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t pir4_write_reg ( pir4_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return pir4_write_regs( ctx, reg, &data_in, 1 );
}

err_t pir4_read_reg ( pir4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return pir4_read_regs( ctx, reg, data_out, 1 );
}

void pir4_enable_device ( pir4_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void pir4_disable_device ( pir4_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t pir4_get_int_pin ( pir4_t *ctx )
{
    return !!digital_in_read ( &ctx->int_pin );
}

err_t pir4_set_operating_state ( pir4_t *ctx, uint8_t op_state )
{
    if ( op_state > PIR4_OP_STATE_SLEEP )
    {
        return PIR4_ERROR;
    }
    return pir4_write_reg ( ctx, PIR4_REG_OP, op_state );
}

err_t pir4_set_odr ( pir4_t *ctx, uint8_t odr )
{
    if ( odr > PIR4_ODR_100_HZ )
    {
        return PIR4_ERROR;
    }
    return pir4_write_reg ( ctx, PIR4_REG_ODR, odr );
}

err_t pir4_set_pass_filter ( pir4_t *ctx, uint8_t lpf, uint8_t hpf )
{
    if ( ( lpf > PIR4_LPF_7_HZ ) || ( hpf > PIR4_HPF_0_5_HZ ) )
    {
        return PIR4_ERROR;
    }
    return pir4_write_reg ( ctx, PIR4_REG_PASS_FILTER, ( lpf << 1 ) | hpf );
}

err_t pir4_set_interrupt ( pir4_t *ctx, uint8_t int_sel )
{
    if ( int_sel > PIR4_INT_SEL_OR_THRESHOLD_LH )
    {
        return PIR4_ERROR;
    }
    return pir4_write_reg ( ctx, PIR4_REG_INTSEL, ( 1 << int_sel ) );
}

err_t pir4_set_threshold ( pir4_t *ctx, uint8_t count, int16_t thr_high, int16_t thr_low )
{
    err_t error_flag = PIR4_OK;
    uint8_t thr_value = 0;
    if ( ( count > PIR4_THRESHOLD_COUNT_7_TIMES ) || 
         ( thr_high > PIR4_THRESHOLD_HIGH_MAX ) || ( thr_high < PIR4_THRESHOLD_HIGH_MIN ) ||
         ( thr_low > PIR4_THRESHOLD_LOW_MAX ) || ( thr_low < PIR4_THRESHOLD_LOW_MIN ) )
    {
        return PIR4_ERROR;
    }
    error_flag |= pir4_write_reg ( ctx, PIR4_REG_THRESHCOUNT, count );
    if ( PIR4_OK == error_flag )
    {
        thr_value = ( uint8_t ) ( ( thr_high / PIR4_THRESHOLD_RES ) & 0xFF );
        error_flag |= pir4_write_reg ( ctx, PIR4_REG_THRESH_HR, thr_value );
    }
    if ( PIR4_OK == error_flag )
    {
        thr_value = ( uint8_t ) ( ( thr_low / ( -PIR4_THRESHOLD_RES ) ) & 0xFF );
        error_flag |= pir4_write_reg ( ctx, PIR4_REG_THRESH_LR, thr_value );
    }
    return error_flag;
}

err_t pir4_set_timer ( pir4_t *ctx, uint16_t window_time )
{
    err_t error_flag = PIR4_OK;
    if ( window_time > PIR4_WINDOW_TIME_MAX )
    {
        return PIR4_ERROR;
    }
    error_flag |= pir4_write_reg ( ctx, PIR4_REG_TIMER_LR, ( uint8_t ) ( window_time & 0xFF ) );
    if ( PIR4_OK == error_flag )
    {
        error_flag |= pir4_write_reg ( ctx, PIR4_REG_TIMER_HR, ( uint8_t ) ( ( window_time >> 8 ) & 0x03 ) );
    }
    return error_flag;
}

err_t pir4_read_overcount ( pir4_t *ctx, uint8_t *oc_up, uint8_t *oc_lo )
{
    err_t error_flag = PIR4_OK;
    uint8_t overcount = 0;
    error_flag |= pir4_read_reg ( ctx, PIR4_REG_OVERCOUNT, &overcount );
    if ( PIR4_OK == error_flag )
    {
        if ( NULL != oc_up )
        {
            *oc_up = ( ( overcount >> 4 ) & 0x0F );
        }
        if ( NULL != oc_lo )
        {
            *oc_lo = ( overcount & 0x0F );
        }
    }
    return error_flag;
}

err_t pir4_read_status ( pir4_t *ctx, uint8_t *status )
{
    err_t error_flag = PIR4_OK;
    uint8_t stat = 0;
    error_flag |= pir4_read_reg ( ctx, PIR4_REG_STATUS, &stat );
    if ( PIR4_OK == error_flag )
    {
        if ( NULL != status )
        {
            *status = ( stat & 0x0F );
        }
    }
    return error_flag;
}

err_t pir4_clear_status ( pir4_t *ctx, uint8_t status )
{
    return pir4_write_reg ( ctx, PIR4_REG_STATUS, ( status & 0x0F ) );
}

err_t pir4_read_continuous_out ( pir4_t *ctx, int16_t *data_out )
{
    err_t error_flag = PIR4_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t status = 0;
    if ( !pir4_get_int_pin ( ctx ) )
    {
        error_flag = PIR4_ERROR;
    }
    if ( PIR4_OK == error_flag )
    {
        error_flag = pir4_read_status ( ctx, &status );
    }
    if ( PIR4_OK == error_flag )
    {
        if ( PIR4_STATUS_CONTINUOUS_OUT != ( status & PIR4_STATUS_CONTINUOUS_OUT ) )
        {
            error_flag = PIR4_ERROR;
        }
    }
    if ( PIR4_OK == error_flag )
    {
        error_flag = pir4_read_regs ( ctx, PIR4_REG_DATA_BUFL, data_buf, 2 );
    }
    if ( PIR4_OK == error_flag )
    {
        error_flag = pir4_clear_status ( ctx, status );
    }
    if ( PIR4_OK == error_flag )
    {
        if ( NULL != data_out )
        {
            *data_out = data_buf[ 1 ];
            *data_out <<= 8;
            *data_out |= data_buf[ 0 ];
        }
    }
    return error_flag;
}

err_t pir4_read_out ( pir4_t *ctx, uint8_t *oc_up, uint8_t *oc_lo )
{
    err_t error_flag = PIR4_OK;
    uint8_t status = 0;
    if ( !pir4_get_int_pin ( ctx ) )
    {
        error_flag = PIR4_ERROR;
    }
    if ( PIR4_OK == error_flag )
    {
        error_flag = pir4_read_status ( ctx, &status );
    }
    if ( PIR4_OK == error_flag )
    {
        error_flag = pir4_read_overcount ( ctx, oc_up, oc_lo );
    }
    if ( PIR4_OK == error_flag )
    {
        if ( ( PIR4_STATUS_TIMER != ( status & PIR4_STATUS_TIMER ) ) && 
             ( PIR4_STATUS_AND_THRESHOLD_LH != ( status & PIR4_STATUS_AND_THRESHOLD_LH ) ) && 
             ( PIR4_STATUS_OR_THRESHOLD_LH != ( status & PIR4_STATUS_OR_THRESHOLD_LH ) ) )
        {
            error_flag = PIR4_ERROR;
        }
    }
    if ( PIR4_OK == error_flag )
    {
        error_flag = pir4_clear_status ( ctx, status );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
