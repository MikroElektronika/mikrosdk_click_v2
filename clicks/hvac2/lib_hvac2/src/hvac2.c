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
 * @file hvac2.c
 * @brief HVAC 2 Click Driver.
 */

#include "hvac2.h"

/**
 * @brief HVAC 2 crc constants.
 * @details Specified constants for crc of HVAC 2 Click driver.
 */
#define HVAC2_POLYNOM            0x31
#define HVAC2_INIT_VALUE         0xFF

/** 
 * @brief HVAC 2 Dallas/Maxim calculation for CRC8 function.
 * @details This function calculates CRC8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 +1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @li @c  Example CRC(0xBEEF) = 0x92
 * @param[in] crc_source : 2 bytes array to calculate crc from.
 * @return Calculated CRC8 output.
 * @note None.
 */
static uint8_t hvac2_calculate_crc ( uint8_t *crc_source );

/** 
 * @brief HVAC 2 wait for execution time function.
 * @details This function waits for a desired execution time in milliseconds.
 * @param[in] exec_time_ms : Execution time in milliseconds.
 * @return None.
 * @note None.
 */
static void hvac2_wait_for_execution_time ( uint16_t exec_time_ms );

void hvac2_cfg_setup ( hvac2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HVAC2_DEVICE_ADDRESS_SCD43;
}

err_t hvac2_init ( hvac2_t *ctx, hvac2_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t hvac2_send_command ( hvac2_t *ctx, uint16_t cmd, uint16_t exec_time_ms )
{
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return HVAC2_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    hvac2_wait_for_execution_time ( exec_time_ms );
    return error_flag;
}

err_t hvac2_write_register ( hvac2_t *ctx, uint16_t reg, uint16_t data_in, uint16_t exec_time_ms )
{
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return HVAC2_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 4 ] = hvac2_calculate_crc ( &data_buf[ 2 ] );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 5 );
    hvac2_wait_for_execution_time ( exec_time_ms );
    return error_flag;
}

err_t hvac2_read_register ( hvac2_t *ctx, uint16_t reg, uint16_t *data_out, uint8_t len, uint16_t exec_time_ms )
{
    if ( len > 16 )
    {
        return HVAC2_ERROR;
    }
    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return HVAC2_ERROR;
    }
    uint8_t data_buf[ 48 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    hvac2_wait_for_execution_time ( exec_time_ms );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, len * 3 );
    if ( HVAC2_ERROR == error_flag )
    {
        return HVAC2_ERROR;
    }
    for ( uint8_t data_cnt = 0; data_cnt < len; data_cnt++ ) 
    {
        if ( data_buf[ data_cnt * 3 + 2 ] != hvac2_calculate_crc ( &data_buf[ data_cnt * 3 ] ) )
        {
            return HVAC2_ERROR;
        }
        data_out[ data_cnt ] = ( ( uint16_t ) data_buf[ data_cnt * 3 ] << 8 ) | data_buf[ data_cnt * 3 + 1 ];
    }
    return HVAC2_OK;
}

err_t hvac2_scd43_start_measurement ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SCD43;
    return hvac2_send_command ( ctx, HVAC2_SCD43_CMD_START_PERIODIC_MEASUREMENT, 1 );
}

err_t hvac2_scd43_stop_measurement ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SCD43;
    return hvac2_send_command ( ctx, HVAC2_SCD43_CMD_STOP_PERIODIC_MEASUREMENT, 500 );
}

err_t hvac2_scd43_read_measurement ( hvac2_t *ctx, hvac2_scd43_data_t *scd43_data )
{
    uint16_t data_buf[ 3 ];
    uint8_t data_ready = 0;
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SCD43;
    if ( HVAC2_ERROR == hvac2_scd43_get_data_ready ( ctx, &data_ready ) )
    {
        return HVAC2_ERROR;
    }
    if ( !data_ready )
    {
        return HVAC2_ERROR;
    }
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SCD43_CMD_READ_MEASUREMENT, data_buf, 3, 1 ) )
    {
        return HVAC2_ERROR;
    }
    scd43_data->co2 = data_buf[ 0 ];
    scd43_data->temperature = HVAC2_SCD43_ABS_MIN_TEMP + ( HVAC2_SCD43_ABS_MAX_TEMP - HVAC2_SCD43_ABS_MIN_TEMP ) * 
                                                           data_buf[ 1 ] / HVAC2_SCD43_DATA_RESOLUTION;
    scd43_data->humidity = HVAC2_SCD43_MAX_RH * data_buf[ 2 ] / HVAC2_SCD43_DATA_RESOLUTION;
    return HVAC2_OK;
}

err_t hvac2_scd43_get_data_ready ( hvac2_t *ctx, uint8_t *data_ready )
{
    uint16_t data_ready_status = 0;
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SCD43;
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SCD43_CMD_GET_DATA_READY_STATUS, &data_ready_status, 1, 1 ) )
    {
        return HVAC2_ERROR;
    }
    *data_ready = ( uint8_t ) ( 0 != ( data_ready_status & 0x7FF ) );
    return HVAC2_OK;
}

err_t hvac2_scd43_get_serial_num ( hvac2_t *ctx, uint16_t *serial_num )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SCD43;
    return hvac2_read_register ( ctx, HVAC2_SCD43_CMD_GET_SERIAL_NUMBER, serial_num, 3, 1 );
}

err_t hvac2_sen5x_start_measurement ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN5X;
    return hvac2_send_command ( ctx, HVAC2_SEN5X_CMD_START_MEASUREMENT, 50 );
}

err_t hvac2_sen5x_stop_measurement ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN5X;
    return hvac2_send_command ( ctx, HVAC2_SEN5X_CMD_STOP_MEASUREMENT, 200 );
}

err_t hvac2_sen5x_read_measurement ( hvac2_t *ctx, hvac2_sen5x_data_t *sen5x_data )
{
    uint16_t data_buf[ 8 ];
    uint8_t data_ready = 0;
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN5X;
    if ( HVAC2_ERROR == hvac2_sen5x_get_data_ready ( ctx, &data_ready ) )
    {
        return HVAC2_ERROR;
    }
    if ( !data_ready )
    {
        return HVAC2_ERROR;
    }
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN5X_CMD_READ_MEASURED_VALUES, data_buf, 8, 20 ) )
    {
        return HVAC2_ERROR;
    }
    sen5x_data->pm1_0 = ( float ) data_buf[ 0 ] / HVAC2_SEN5X_PM_SCALE_FACTOR;
    sen5x_data->pm2_5 = ( float ) data_buf[ 1 ] / HVAC2_SEN5X_PM_SCALE_FACTOR;
    sen5x_data->pm4_0 = ( float ) data_buf[ 2 ] / HVAC2_SEN5X_PM_SCALE_FACTOR;
    sen5x_data->pm10 = ( float ) data_buf[ 3 ] / HVAC2_SEN5X_PM_SCALE_FACTOR;
    sen5x_data->humidity = ( float ) ( ( int16_t ) data_buf[ 4 ] ) / HVAC2_SEN5X_HUM_SCALE_FACTOR;
    sen5x_data->temperature = ( float ) ( ( int16_t ) data_buf[ 5 ] ) / HVAC2_SEN5X_TEMP_SCALE_FACTOR;
    sen5x_data->voc = ( float ) ( ( int16_t ) data_buf[ 6 ] ) / HVAC2_SEN5X_VOC_SCALE_FACTOR;
    sen5x_data->nox = ( float ) ( ( int16_t ) data_buf[ 7 ] ) / HVAC2_SEN5X_NOX_SCALE_FACTOR;
    return HVAC2_OK;
}

err_t hvac2_sen5x_get_data_ready ( hvac2_t *ctx, uint8_t *data_ready )
{
    uint16_t data_ready_flag = 0;
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN5X;
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN5X_CMD_READ_DATA_READY_FLAG, &data_ready_flag, 1, 20 ) )
    {
        return HVAC2_ERROR;
    }
    *data_ready = ( uint8_t ) ( 0 != ( data_ready_flag & 0x01 ) );
    return HVAC2_OK;
}

err_t hvac2_sen5x_get_serial_num ( hvac2_t *ctx, uint8_t *serial_num )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN5X;
    uint16_t serial_num_int[ 16 ] = { 0 };
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN5X_CMD_READ_SERIAL_NUM, serial_num_int, 16, 20 ) )
    {
        return HVAC2_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        serial_num[ cnt * 2 ] = ( uint8_t ) ( ( serial_num_int[ cnt ] >> 8 ) & 0xFF );
        serial_num[ cnt * 2 + 1 ] = ( uint8_t ) ( serial_num_int[ cnt ] & 0xFF );
    }
    return HVAC2_OK;
}

err_t hvac2_sen5x_get_product_name ( hvac2_t *ctx, uint8_t *product_name )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN5X;
    uint16_t product_name_int[ 16 ] = { 0 };
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN5X_CMD_READ_PRODUCT_NAME, product_name_int, 16, 20 ) )
    {
        return HVAC2_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        product_name[ cnt * 2 ] = ( uint8_t ) ( ( product_name_int[ cnt ] >> 8 ) & 0xFF );
        product_name[ cnt * 2 + 1 ] = ( uint8_t ) ( product_name_int[ cnt ] & 0xFF );
    }
    return HVAC2_OK;
}

err_t hvac2_sen5x_start_fan_cleaning ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN5X;
    return hvac2_send_command ( ctx, HVAC2_SEN5X_CMD_START_FAN_CLEANING, 20 );
}

err_t hvac2_sen6x_start_measurement ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN6X;
    return hvac2_send_command ( ctx, HVAC2_SEN6X_CMD_START_MEASUREMENT, 50 );
}

err_t hvac2_sen6x_stop_measurement ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN6X;
    return hvac2_send_command ( ctx, HVAC2_SEN6X_CMD_STOP_MEASUREMENT, 200 );
}

err_t hvac2_sen65_read_measurement ( hvac2_t *ctx, hvac2_sen65_data_t *sen65_data )
{
    uint16_t data_buf[ 8 ];
    uint8_t data_ready = 0;
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN6X;
    if ( HVAC2_ERROR == hvac2_sen6x_get_data_ready ( ctx, &data_ready ) )
    {
        return HVAC2_ERROR;
    }
    if ( !data_ready )
    {
        return HVAC2_ERROR;
    }
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN6X_CMD_READ_MEASURED_VALUES_SEN65, data_buf, 8, 20 ) )
    {
        return HVAC2_ERROR;
    }
    sen65_data->pm1_0 = ( float ) data_buf[ 0 ] / HVAC2_SEN65_PM_SCALE_FACTOR;
    sen65_data->pm2_5 = ( float ) data_buf[ 1 ] / HVAC2_SEN65_PM_SCALE_FACTOR;
    sen65_data->pm4_0 = ( float ) data_buf[ 2 ] / HVAC2_SEN65_PM_SCALE_FACTOR;
    sen65_data->pm10 = ( float ) data_buf[ 3 ] / HVAC2_SEN65_PM_SCALE_FACTOR;
    sen65_data->humidity = ( float ) ( ( int16_t ) data_buf[ 4 ] ) / HVAC2_SEN65_HUM_SCALE_FACTOR;
    sen65_data->temperature = ( float ) ( ( int16_t ) data_buf[ 5 ] ) / HVAC2_SEN65_TEMP_SCALE_FACTOR;
    sen65_data->voc = ( float ) ( ( int16_t ) data_buf[ 6 ] ) / HVAC2_SEN65_VOC_SCALE_FACTOR;
    sen65_data->nox = ( float ) ( ( int16_t ) data_buf[ 7 ] ) / HVAC2_SEN65_NOX_SCALE_FACTOR;
    return HVAC2_OK;
}

err_t hvac2_sen6x_get_data_ready ( hvac2_t *ctx, uint8_t *data_ready )
{
    uint16_t data_ready_flag = 0;
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN6X;
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN6X_CMD_GET_DATA_READY, &data_ready_flag, 1, 20 ) )
    {
        return HVAC2_ERROR;
    }
    *data_ready = ( uint8_t ) ( 0 != ( data_ready_flag & 0x01 ) );
    return HVAC2_OK;
}

err_t hvac2_sen6x_get_serial_num ( hvac2_t *ctx, uint8_t *serial_num )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN6X;
    uint16_t serial_num_int[ 16 ] = { 0 };
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN6X_CMD_GET_SERIAL_NUM, serial_num_int, 16, 20 ) )
    {
        return HVAC2_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        serial_num[ cnt * 2 ] = ( uint8_t ) ( ( serial_num_int[ cnt ] >> 8 ) & 0xFF );
        serial_num[ cnt * 2 + 1 ] = ( uint8_t ) ( serial_num_int[ cnt ] & 0xFF );
    }
    return HVAC2_OK;
}

err_t hvac2_sen6x_get_product_name ( hvac2_t *ctx, uint8_t *product_name )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN6X;
    uint16_t product_name_int[ 16 ] = { 0 };
    if ( HVAC2_ERROR == hvac2_read_register ( ctx, HVAC2_SEN6X_CMD_GET_PRODUCT_NAME, product_name_int, 16, 20 ) )
    {
        return HVAC2_ERROR;
    }
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        product_name[ cnt * 2 ] = ( uint8_t ) ( ( product_name_int[ cnt ] >> 8 ) & 0xFF );
        product_name[ cnt * 2 + 1 ] = ( uint8_t ) ( product_name_int[ cnt ] & 0xFF );
    }
    return HVAC2_OK;
}

err_t hvac2_sen6x_start_fan_cleaning ( hvac2_t *ctx )
{
    ctx->slave_address = HVAC2_DEVICE_ADDRESS_SEN6X;
    return hvac2_send_command ( ctx, HVAC2_SEN6X_CMD_START_FAN_CLEANING, 20 );
}

static uint8_t hvac2_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = HVAC2_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ HVAC2_POLYNOM );
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

static void hvac2_wait_for_execution_time ( uint16_t exec_time_ms )
{
    for ( uint16_t exec_time_cnt = 0; exec_time_cnt < exec_time_ms; exec_time_cnt++ )
    {
        Delay_1ms ( );
    }
}

// ------------------------------------------------------------------------- END
