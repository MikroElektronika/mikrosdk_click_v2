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
 * @file ldc.c
 * @brief LDC Click Driver.
 */

#include "ldc.h"
#include "math.h"

void ldc_cfg_setup ( ldc_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sd = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LDC_SET_DEV_ADDR;
}

err_t ldc_init ( ldc_t *ctx, ldc_cfg_t *cfg ) 
{
    digital_out_init( &ctx->sd, cfg->sd );
    digital_out_low( &ctx->sd );
    Delay_100ms( );
    
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    Delay_100ms( );

    return I2C_MASTER_SUCCESS;
}

err_t ldc_default_cfg ( ldc_t *ctx ) 
{
    err_t ret_val = LDC_OK;
    // Setting default configuration recommended from DS
    // Ignore error for the first write attempt
    ldc_generic_write( ctx, LDC_REG_RCOUNT_CH0, 0xFFFF );
    ret_val |= ldc_generic_write( ctx, LDC_REG_RCOUNT_CH0, 0xFFFF );
    ret_val |= ldc_generic_write( ctx, LDC_REG_SETTLECOUNT_CH0, 0x0100 );
    ret_val |= ldc_generic_write( ctx, LDC_REG_CLOCK_DIVIDERS_CH0, 0x1001 );
    ret_val |= ldc_generic_write( ctx, LDC_REG_ERROR_CONFIG, 0x0001 );
    ret_val |= ldc_generic_write( ctx, LDC_REG_DRIVE_CURRENT_CH0, 0x9800 );
    ret_val |= ldc_generic_write( ctx, LDC_REG_MUX_CONFIG, 0x020C );
    ret_val |= ldc_generic_write( ctx, LDC_REG_CONFIG, 0x1C01 );
    Delay_100ms ( );
    return ret_val;
}

err_t ldc_generic_write ( ldc_t *ctx, uint8_t reg, uint16_t tx_data )
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data >> 8;
    data_buf[ 2 ] = tx_data;

    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t ldc_generic_read ( ldc_t *ctx, uint8_t reg, uint16_t *rx_data )
{
    uint8_t read_buf[ 2 ] = { 0 };
    err_t ret_val = LDC_OK;
     
    ret_val = i2c_master_write_then_read( &ctx->i2c, &reg, 1, read_buf, 2 );
     
    *rx_data = ( ( uint16_t )read_buf[ 0 ] << 8 ) | read_buf[ 1 ];
    
    return ret_val;
}

uint8_t ldc_get_interrupt ( ldc_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void ldc_set_shut_down ( ldc_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->sd );
    }
    else
    {
        digital_out_low( &ctx->sd );
    }
}

err_t ldc_get_frequency ( ldc_t *ctx, uint8_t channel, uint16_t divider, float *frequency )
{
    uint16_t temp_data = 0;
    uint16_t error_status;
    err_t ret_val = ldc_generic_read( ctx, channel, &temp_data );
    
    error_status = temp_data >> 12;
    temp_data &= 0xFFF;
    /* Convert frequency to Hz and divide it*/
    float freq = ( LDC_INTERNAL_FREQUENCY * 1000000 ) / ( float )divider;
    freq /= LDC_FREQUENCY_RESOLUTION;
    freq *= temp_data;
    freq /= 1000000;/* Return back frequency to MHz*/
    *frequency = freq;
    
    if ( error_status & LDC_OVER_RANGE )
    {
        ret_val |= LDC_ERROR_UNDER_RANGE;
    }
    if ( error_status & LDC_UNDER_RANGE )
    {
        ret_val |= LDC_ERROR_OVER_RANGE;
    }
    if ( error_status & LDC_WATCHDOG )
    {
        ret_val |= LDC_ERROR_WATCHDOG;
    }
    
    return ret_val;
}

float ldc_calculate_inductance ( float frequency )
{
    return 1.0 / ( pow( ( TWO_PI * frequency ), 2 ) * LDC_SENSOR_CAPACITANCE );
}

// ------------------------------------------------------------------------- END
