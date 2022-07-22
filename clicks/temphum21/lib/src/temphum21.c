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
 * @file temphum21.c
 * @brief TempHum 21 Click Driver.
 */

#include "temphum21.h"

void temphum21_cfg_setup ( temphum21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->all = HAL_PIN_NC;
    cfg->alh = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM21_SET_DEV_ADDR;
}

err_t temphum21_init ( temphum21_t *ctx, temphum21_cfg_t *cfg ) 
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

    digital_in_init( &ctx->all, cfg->all );
    digital_in_init( &ctx->alh, cfg->alh );

    return I2C_MASTER_SUCCESS;
}

err_t temphum21_request_measurement ( temphum21_t *ctx ) 
{
    uint8_t dummy = 0;
    return i2c_master_write( &ctx->i2c, &dummy, 1 );
}

err_t temphum21_read_measurement ( temphum21_t *ctx, float *temperature, float *humidity )
{
    uint8_t data_buf[ 4 ];
    err_t error_flag = temphum21_request_measurement ( ctx );
    // The measurement cycle duration is typically 36.65ms for temperature and humidity readings.
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= i2c_master_read ( &ctx->i2c, data_buf, 4 );
    uint16_t raw_data = ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) & TEMPHUM21_DATA_RES;
    *humidity = ( float ) raw_data / TEMPHUM21_DATA_RES * TEMPHUM21_HUM_RES;
    raw_data = ( ( ( uint16_t ) data_buf[ 2 ] << 6 ) | ( data_buf[ 3 ] >> 2 ) ) & TEMPHUM21_DATA_RES;
    *temperature = ( float ) raw_data / TEMPHUM21_DATA_RES * TEMPHUM21_TEMP_RES - TEMPHUM21_TEMP_OFFSET;
    if ( TEMPHUM21_OK == error_flag )
    {
        error_flag = ( data_buf[ 0 ] >> 6 ) & TEMPHUM21_STATUS_BIT_MASK; // status bits
    }
    return error_flag; 
}

uint8_t temphum21_get_all_pin ( temphum21_t *ctx )
{
    return digital_in_read ( &ctx->all );
}

uint8_t temphum21_get_alh_pin ( temphum21_t *ctx )
{
    return digital_in_read ( &ctx->alh );
}

// ------------------------------------------------------------------------- END
