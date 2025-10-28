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
 * @file irgrid5.c
 * @brief IR Grid 5 Click Driver.
 */

#include "irgrid5.h"

void irgrid5_cfg_setup ( irgrid5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = IRGRID5_DEVICE_ADDRESS;
}

err_t irgrid5_init ( irgrid5_t *ctx, irgrid5_cfg_t *cfg ) 
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

err_t irgrid5_default_cfg ( irgrid5_t *ctx ) 
{
    err_t error_flag = IRGRID5_OK;
    irgrid5_disable_device ( ctx );
    Delay_100ms ( );
    irgrid5_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= irgrid5_reset ( ctx );
    Delay_100ms ( );
    error_flag |= irgrid5_set_meas_mode ( ctx, IRGRID5_MEAS_MODE_CONT );
    error_flag |= irgrid5_set_out_format ( ctx, IRGRID5_OUT_FORMAT_TEMPERATURE );
    error_flag |= irgrid5_set_refresh_rate ( ctx, IRGRID5_REFRESH_RATE_2HZ );
    Delay_1sec ( );
    error_flag |= irgrid5_clear_ready ( ctx );
    error_flag |= irgrid5_force_start ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t irgrid5_cmd_write ( irgrid5_t *ctx, uint16_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( IRGRID5_OPCODE_CMD >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( IRGRID5_OPCODE_CMD & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 4 );
}

err_t irgrid5_mem_read ( irgrid5_t *ctx, uint16_t addr, uint16_t *data_out, uint16_t len )
{
    err_t error_flag = IRGRID5_OK;
    uint8_t addr_buf[ 2 ] = { 0 };
    uint16_t cnt = 0;
    addr_buf[ 0 ] = ( uint8_t ) ( ( addr >> 8 ) & 0xFF );
    addr_buf[ 1 ] = ( uint8_t ) ( addr & 0xFF );
    memset ( ctx->mem_buf_8, 0, sizeof ( ctx->mem_buf_8 ) );
    error_flag = i2c_master_write_then_read( &ctx->i2c, addr_buf, 2, ctx->mem_buf_8, len * 2 );
    if ( IRGRID5_OK == error_flag )
    {
        for ( cnt = 0; ( cnt < len ) && ( NULL != data_out ); cnt++ )
        {
            data_out[ cnt ] = ( ( uint16_t ) ctx->mem_buf_8[ cnt * 2 ] << 8 ) | ctx->mem_buf_8[ cnt * 2 + 1 ];
        }
    }
    return error_flag;
}

err_t irgrid5_config_write ( irgrid5_t *ctx, uint16_t addr, uint16_t data_in )
{
    err_t error_flag = IRGRID5_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( IRGRID5_OPCODE_CONFIG >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( IRGRID5_OPCODE_CONFIG & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( addr >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( addr & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( data_in & 0xFF );
    error_flag = i2c_master_write( &ctx->i2c, data_buf, 6 );
    Delay_10ms ( );
    Delay_10ms ( );
    return error_flag;
}

err_t irgrid5_reset ( irgrid5_t *ctx )
{
    return irgrid5_cmd_write( ctx, IRGRID5_CMD_RESET );
}

err_t irgrid5_force_start ( irgrid5_t *ctx )
{
    return irgrid5_cmd_write( ctx, IRGRID5_CMD_FORCE_START );
}

err_t irgrid5_clear_ready ( irgrid5_t *ctx )
{
    uint16_t dummy_read = 0;
    return irgrid5_mem_read( ctx, IRGRID5_ADDR_RAM_TO, &dummy_read, 1 );
}

err_t irgrid5_check_ready ( irgrid5_t *ctx )
{
    uint16_t flags = 0;
    err_t error_flag = irgrid5_mem_read( ctx, IRGRID5_ADDR_RAM_DATA_FLAGS, &flags, 1 );
    if ( IRGRID5_OK == error_flag )
    {
        if ( ( flags & IRGRID5_DATA_FLAGS_READY ) && ( !( flags & IRGRID5_DATA_FLAGS_BUSY ) ) )
        {
            error_flag = IRGRID5_DATA_READY;
        }
    }
    return error_flag;
}

err_t irgrid5_sleep ( irgrid5_t *ctx )
{
    return irgrid5_cmd_write( ctx, IRGRID5_CMD_SLEEP );
}

err_t irgrid5_wake_up ( irgrid5_t *ctx )
{
    uint8_t wake_opcode = IRGRID5_OPCODE_WAKE;
    return i2c_master_write( &ctx->i2c, &wake_opcode, 1 );
}

void irgrid5_enable_device ( irgrid5_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void irgrid5_disable_device ( irgrid5_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t irgrid5_get_device_id ( irgrid5_t *ctx, uint16_t *device_id )
{
    return irgrid5_mem_read( ctx, IRGRID5_ADDR_EE_DEVICE_ID, device_id, 4 );
}

err_t irgrid5_get_fw_version ( irgrid5_t *ctx, uint8_t *fw_ver )
{
    err_t error_flag = irgrid5_mem_read( ctx, IRGRID5_ADDR_FLASH_FW_VERSION, NULL, 2 );
    if ( IRGRID5_OK == error_flag )
    {
        if ( NULL != fw_ver )
        {
            fw_ver[ 0 ] = ctx->mem_buf_8[ 0 ];
            fw_ver[ 1 ] = ctx->mem_buf_8[ 3 ];
            fw_ver[ 2 ] = ctx->mem_buf_8[ 2 ];
        }
    }
    return error_flag;
}

err_t irgrid5_set_meas_mode ( irgrid5_t *ctx, uint8_t mode )
{
    err_t error_flag = IRGRID5_OK;
    uint16_t app_config = 0;
    if ( mode > IRGRID5_MEAS_MODE_STEP )
    {
        return IRGRID5_ERROR;
    }
    error_flag = irgrid5_mem_read( ctx, IRGRID5_ADDR_CONFIG_APP_CONFIG, &app_config, 1 );
    if ( IRGRID5_OK == error_flag )
    {
        app_config &= ( ~IRGRID5_APP_CONFIG_MEAS_MODE_MASK );
        if ( IRGRID5_MEAS_MODE_STEP == mode )
        {
            app_config |= IRGRID5_APP_CONFIG_MEAS_MODE_STEP;
        }
        error_flag |= irgrid5_config_write( ctx, IRGRID5_ADDR_CONFIG_APP_CONFIG, app_config );
    }
    return error_flag;
}

err_t irgrid5_set_out_format ( irgrid5_t *ctx, uint8_t out_format )
{
    err_t error_flag = IRGRID5_OK;
    uint16_t app_config = 0;
    if ( out_format > IRGRID5_OUT_FORMAT_NORMALIZED )
    {
        return IRGRID5_ERROR;
    }
    error_flag = irgrid5_mem_read( ctx, IRGRID5_ADDR_CONFIG_APP_CONFIG, &app_config, 1 );
    if ( IRGRID5_OK == error_flag )
    {
        app_config &= ( ~IRGRID5_APP_CONFIG_OUT_MASK );
        if ( IRGRID5_OUT_FORMAT_NORMALIZED == out_format )
        {
            app_config |= IRGRID5_APP_CONFIG_OUT_RAW_IR;
        }
        error_flag |= irgrid5_config_write( ctx, IRGRID5_ADDR_CONFIG_APP_CONFIG, app_config );
    }
    return error_flag;
}

err_t irgrid5_set_refresh_rate ( irgrid5_t *ctx, uint8_t rate )
{
    err_t error_flag = IRGRID5_OK;
    uint16_t refresh_rate = 0;
    if ( ( rate < IRGRID5_REFRESH_RATE_2HZ ) || ( rate > IRGRID5_REFRESH_RATE_16HZ ) )
    {
        return IRGRID5_ERROR;
    }
    error_flag = irgrid5_mem_read( ctx, IRGRID5_ADDR_CONFIG_REFRESH_RATE, &refresh_rate, 1 );
    if ( IRGRID5_OK == error_flag )
    {
        refresh_rate &= ( ~IRGRID5_REFRESH_RATE_MASK );
        refresh_rate |= ( ( uint16_t ) rate );
        error_flag |= irgrid5_config_write( ctx, IRGRID5_ADDR_CONFIG_REFRESH_RATE, refresh_rate );
    }
    return error_flag;
}

err_t irgrid5_get_measurement ( irgrid5_t *ctx, float *obj_image, float *sensor_temp )
{
    err_t error_flag = IRGRID5_OK;
    uint16_t timeout_cnt = 0;
    uint16_t pixels[ IRGRID5_NUM_PIXELS + 1 ] = { 0 };
    uint16_t pixel_cnt = 0;
    for ( ; ; )
    {
        error_flag = irgrid5_check_ready ( ctx );
        if ( ( IRGRID5_ERROR == error_flag ) || ( IRGRID5_DATA_READY == error_flag ) )
        {
            break;
        }
        if ( ++timeout_cnt > IRGRID5_TIMEOUT_MS )
        {
            error_flag = IRGRID5_ERROR_TIMEOUT;
            break;
        }
        Delay_1ms ( );
    }

    if ( IRGRID5_DATA_READY == error_flag )
    {
        error_flag = irgrid5_mem_read ( ctx, IRGRID5_ADDR_RAM_TO, pixels, IRGRID5_NUM_PIXELS + 1 );
    }

    if ( IRGRID5_OK == error_flag )
    {
        *sensor_temp = ( ( int16_t ) pixels[ IRGRID5_NUM_PIXELS ] ) / IRGRID5_SENSOR_TEMP_RES;
        for ( pixel_cnt = 0; pixel_cnt < IRGRID5_NUM_PIXELS; pixel_cnt++ ) 
        {
            obj_image[ pixel_cnt ] = pixels[ pixel_cnt ] / IRGRID5_OBJ_TEMP_RES;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
