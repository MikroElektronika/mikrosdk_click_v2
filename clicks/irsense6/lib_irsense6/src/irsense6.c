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
 * @file irsense6.c
 * @brief IR Sense 6 Click Driver.
 */

#include "irsense6.h"

void irsense6_cfg_setup ( irsense6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = IRSENSE6_DEVICE_ADDRESS;
}

err_t irsense6_init ( irsense6_t *ctx, irsense6_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t irsense6_i2c_write ( irsense6_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

err_t irsense6_i2c_read ( irsense6_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

void irsense6_enable_device ( irsense6_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void irsense6_disable_device ( irsense6_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

err_t irsense6_read_data ( irsense6_t *ctx, float *obj_temp, float *amb_temp ) 
{
    err_t error_flag = IRSENSE6_OK;
    uint8_t data_buf[ 7 ] = { 0 };
    uint32_t raw_data = 0;
    data_buf[ 0 ] = IRSENSE6_CMD_FULL_MEASUREMENT;
    error_flag |= irsense6_i2c_write( ctx, data_buf, 1 );
    Delay_100ms ( );
    if ( IRSENSE6_OK == error_flag )
    {
        error_flag |= irsense6_i2c_read( ctx, data_buf, 7 );
    }
    if ( IRSENSE6_OK == error_flag )
    {
        ctx->status = data_buf[ 0 ];
        if ( NULL != obj_temp )
        {
            raw_data = ( ( uint32_t ) data_buf[ 1 ] << 16 ) | ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
            *obj_temp = ( ( float ) raw_data / IRSENSE6_RAW_DATA_RESOLUTION ) * IRSENSE6_OBJ_TEMP_RES - IRSENSE6_OBJ_TEMP_OFFSET;
        }
        if ( NULL != amb_temp )
        {
            raw_data = ( ( uint32_t ) data_buf[ 4 ] << 16 ) | ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 6 ];
            *amb_temp = ( ( float ) raw_data / IRSENSE6_RAW_DATA_RESOLUTION ) * IRSENSE6_AMB_TEMP_RES - IRSENSE6_AMB_TEMP_OFFSET;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
