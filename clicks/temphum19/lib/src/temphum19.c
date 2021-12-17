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
 * @file temphum19.c
 * @brief TempHum 19 Click Driver.
 */

#include "temphum19.h"

void temphum19_cfg_setup ( temphum19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM19_SET_DEV_ADDR;
}

err_t temphum19_init ( temphum19_t *ctx, temphum19_cfg_t *cfg ) 
{
    digital_out_init( &ctx->en, cfg->en );
    
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

err_t temphum19_default_cfg ( temphum19_t *ctx ) 
{
    err_t error_flag = TEMPHUM19_OK;
    
    temphum19_restart_chip ( ctx );
    error_flag |= temphum19_set_mode_reg ( ctx, TEMPHUM19_NORMAL_OPERATION_MODE | 
                                                TEMPHUM19_HUM_NO_AVG | 
                                                TEMPHUM19_TEMP_AVG_8 | 
                                                TEMPHUM19_STOP_DETECTION );

    return error_flag;
}

err_t temphum19_generic_write ( temphum19_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 48 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t temphum19_generic_read ( temphum19_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void temphum19_enable_chip ( temphum19_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void temphum19_disable_chip ( temphum19_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void temphum19_restart_chip ( temphum19_t *ctx )
{
    temphum19_disable_chip ( ctx );
    Delay_1sec ( );
    temphum19_enable_chip ( ctx );
    Delay_1sec ( );
}

err_t temphum19_set_mode_reg ( temphum19_t *ctx, uint8_t mode )
{
    ctx->detection_mode = mode;
    return temphum19_generic_write ( ctx, TEMPHUM19_REG_MODE, &mode, 1 );
}

err_t temphum19_read_data ( temphum19_t *ctx, float *temperature, float *humidity ) 
{
    uint8_t reg_data[ 4 ] = { 0 };
    err_t error_flag = temphum19_set_mode_reg ( ctx, ctx->detection_mode | TEMPHUM19_START_DETECTION );
    if ( error_flag )
    {
        temphum19_restart_chip ( ctx );
        return error_flag;
    }
    Delay_1ms ( );
    do 
    {
        error_flag |= temphum19_generic_read ( ctx, TEMPHUM19_REG_MODE, reg_data, 1 );
        if ( error_flag )
        {
            temphum19_restart_chip ( ctx );
            return error_flag;
        }
        Delay_1ms ( );
    } while ( reg_data[ 0 ] & TEMPHUM19_START_DETECTION );
    
    error_flag |= temphum19_generic_read ( ctx, TEMPHUM19_REG_HUMIDITY_LSB, reg_data, 4 );

    if ( TEMPHUM19_OK == error_flag )
    {
        int16_t raw_data = ( ( ( int16_t ) reg_data[ 3 ] << 8 ) | reg_data[ 2 ] ) & TEMPHUM19_TEMP_DATA;
        *temperature = ( float ) ( raw_data - ( TEMPHUM19_10BIT_RESOLUTION - TEMPHUM19_TEMP_NOMINAL / 
                                                TEMPHUM19_TEMP_RESOLUTION ) ) * TEMPHUM19_TEMP_RESOLUTION;
        raw_data = ( ( ( int16_t ) reg_data[ 1 ] << 8 ) | reg_data[ 0 ] ) & TEMPHUM19_HUM_DATA;
        *humidity = ( ( float ) raw_data / ( TEMPHUM19_10BIT_RESOLUTION - 1 ) ) * TEMPHUM19_HUM_RESOLUTION;
    }
    else
    {
        temphum19_restart_chip ( ctx );
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
