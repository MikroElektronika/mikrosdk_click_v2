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
 * @file temphum27.c
 * @brief TempHum 27 Click Driver.
 */

#include "temphum27.h"

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x1D (x4 + x3 + x2 + 1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @li @c  Example CRC(0x05,0x80,0x05,0x80) = 0xF2
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t temphum27_calculate_crc ( uint8_t *data_buf, uint8_t len );

void temphum27_cfg_setup ( temphum27_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM27_DEVICE_ADDRESS;
}

err_t temphum27_init ( temphum27_t *ctx, temphum27_cfg_t *cfg ) 
{
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->alr, cfg->alr );

    temphum27_reset_device ( ctx );
 
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

err_t temphum27_write_reg ( temphum27_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = TEMPHUM27_CMD_WRITE_REG;
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t temphum27_read_reg ( temphum27_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = TEMPHUM27_CMD_READ_REG;
    data_buf[ 1 ] = reg;
    return i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, 1 );
}

err_t temphum27_read_data_hold ( temphum27_t *ctx, float *temp, float *hum )
{
    err_t error_flag = TEMPHUM27_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    uint8_t crc = 0;
    if ( NULL == hum )
    {
        if ( NULL == temp )
        {
            return TEMPHUM27_ERROR;
        }
        data_buf[ 0 ] = TEMPHUM27_CMD_HOLD_TEMP_MEAS;
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 3 ], 3 );
        crc = temphum27_calculate_crc ( &data_buf[ 1 ], 4 );
        if ( ( crc == data_buf[ 5 ] ) && ( TEMPHUM27_OK == error_flag ) )
        {
            *temp = ( float ) ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ] ) / 
                    TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_TEMP_DATA_RES - TEMPHUM27_TEMP_DATA_OFFSET;
        }
        else
        {
            error_flag |= TEMPHUM27_ERROR;
        }
    }
    else
    {
        data_buf[ 0 ] = TEMPHUM27_CMD_HOLD_TEMP_HUM_MEAS;
        error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 5 );
        crc = temphum27_calculate_crc ( &data_buf[ 1 ], 4 );
        if ( ( crc == data_buf[ 5 ] ) && ( TEMPHUM27_OK == error_flag ) )
        {
            if ( NULL != temp )
            {
                *temp = ( float ) ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ] ) / 
                        TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_TEMP_DATA_RES - TEMPHUM27_TEMP_DATA_OFFSET;
            }
            *hum = ( float ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ] ) / 
                   TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_HUM_DATA_RES;
        }
        else
        {
            error_flag |= TEMPHUM27_ERROR;
        }
    }
    return error_flag;
}

err_t temphum27_read_data_no_hold ( temphum27_t *ctx, float *temp, float *hum )
{
    err_t error_flag = TEMPHUM27_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    uint8_t crc = 0;
    if ( NULL == hum )
    {
        if ( NULL == temp )
        {
            return TEMPHUM27_ERROR;
        }
        data_buf[ 0 ] = TEMPHUM27_CMD_NO_HOLD_TEMP_MEAS;
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 0 ], 1 );
        Delay_10ms ( );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 3 ], 3 );
        crc = temphum27_calculate_crc ( &data_buf[ 1 ], 4 );
        if ( ( crc == data_buf[ 5 ] ) && ( TEMPHUM27_OK == error_flag ) )
        {
            *temp = ( float ) ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ] ) / 
                    TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_TEMP_DATA_RES - TEMPHUM27_TEMP_DATA_OFFSET;
        }
        else
        {
            error_flag |= TEMPHUM27_ERROR;
        }
    }
    else
    {
        data_buf[ 0 ] = TEMPHUM27_CMD_NO_HOLD_TEMP_HUM_MEAS;
        error_flag |= i2c_master_write( &ctx->i2c, &data_buf[ 0 ], 1 );
        Delay_10ms ( );
        error_flag |= i2c_master_read( &ctx->i2c, &data_buf[ 1 ], 5 );
        crc = temphum27_calculate_crc ( &data_buf[ 1 ], 4 );
        if ( ( crc == data_buf[ 5 ] ) && ( TEMPHUM27_OK == error_flag ) )
        {
            if ( NULL != temp )
            {
                *temp = ( float ) ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ] ) / 
                        TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_TEMP_DATA_RES - TEMPHUM27_TEMP_DATA_OFFSET;
            }
            *hum = ( float ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ] ) / 
                   TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_HUM_DATA_RES;
        }
        else
        {
            error_flag |= TEMPHUM27_ERROR;
        }
    }
    return error_flag;
}

err_t temphum27_start_periodic_meas ( temphum27_t *ctx, uint8_t freq )
{
    err_t error_flag = TEMPHUM27_OK;
    uint8_t reg_data = 0;
    if ( freq > TEMPHUM27_PERIODIC_FREQ_2_5S )
    {
        return TEMPHUM27_ERROR;
    }
    error_flag |= temphum27_read_reg ( ctx, TEMPHUM27_REG_PERIODIC_CONFIG, &reg_data );
    if ( TEMPHUM27_OK == error_flag )
    {
        reg_data &= ~( TEMPHUM27_PERIODIC_CONFIG_FREQ_MASK | TEMPHUM27_PERIODIC_CONFIG_ALR_POL_MASK );
        reg_data |= ( TEMPHUM27_PERIODIC_CONFIG_ACTIVATE | TEMPHUM27_PERIODIC_CONFIG_ALR_POL_HIGH );
        reg_data |= ( ( freq << 4 ) & TEMPHUM27_PERIODIC_CONFIG_FREQ_MASK );
        error_flag |= temphum27_write_reg ( ctx, TEMPHUM27_REG_PERIODIC_CONFIG, reg_data );
    }
    return error_flag;
}

err_t temphum27_stop_periodic_meas ( temphum27_t *ctx )
{
    uint8_t command = TEMPHUM27_CMD_STOP_PERIODIC_MEAS;
    return i2c_master_write( &ctx->i2c, &command, 1 );
}

err_t temphum27_read_data_periodic ( temphum27_t *ctx, float *temp, float *hum )
{
    err_t error_flag = TEMPHUM27_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    uint8_t crc = 0;
    if ( ( NULL == hum ) && ( NULL == temp ) )
    {
        return TEMPHUM27_ERROR;
    }
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 5 );
    crc = temphum27_calculate_crc ( data_buf, 4 );
    if ( ( crc == data_buf[ 4 ] ) && ( TEMPHUM27_OK == error_flag ) )
    {
        if ( NULL != temp )
        {
            *temp = ( float ) ( ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ] ) / 
                    TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_TEMP_DATA_RES - TEMPHUM27_TEMP_DATA_OFFSET;
        }
        if ( NULL != hum )
        {
            *hum = ( float ) ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) / 
                   TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_HUM_DATA_RES;
        }
    }
    else
    {
        error_flag |= TEMPHUM27_ERROR;
    }
    return error_flag;
}

err_t temphum27_read_data_periodic_al ( temphum27_t *ctx, float *temp, float *hum, uint8_t *alert )
{
    err_t error_flag = TEMPHUM27_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    uint8_t crc = 0;
    if ( ( NULL == alert ) && ( NULL == hum ) && ( NULL == temp ) )
    {
        return TEMPHUM27_ERROR;
    }
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 6 );
    crc = temphum27_calculate_crc ( &data_buf[ 1 ], 4 );
    if ( ( crc == data_buf[ 5 ] ) && ( TEMPHUM27_OK == error_flag ) )
    {
        if ( NULL != temp )
        {
            *temp = ( float ) ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ] ) / 
                    TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_TEMP_DATA_RES - TEMPHUM27_TEMP_DATA_OFFSET;
        }
        if ( NULL != hum )
        {
            *hum = ( float ) ( ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ] ) / 
                   TEMPHUM27_DATA_RESOLUTION * TEMPHUM27_HUM_DATA_RES;
        }
        if ( NULL != alert )
        {
            *alert = data_buf[ 0 ];
        }
    }
    else
    {
        error_flag |= TEMPHUM27_ERROR;
    }
    return error_flag;
}

err_t temphum27_read_sensor_id ( temphum27_t *ctx, uint32_t *sensor_id )
{
    err_t error_flag = TEMPHUM27_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    if ( NULL == sensor_id )
    {
        return TEMPHUM27_ERROR;
    }
    data_buf[ 0 ] = TEMPHUM27_CMD_READ_SENSOR_ID;
    error_flag |= i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 4 );
    if ( TEMPHUM27_OK == error_flag )
    {
        *sensor_id = ( ( uint32_t ) data_buf[ 1 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                     ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    }
    return error_flag;
}

void temphum27_enable_device ( temphum27_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void temphum27_disable_device ( temphum27_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void temphum27_reset_device ( temphum27_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_1sec ( );
    digital_out_high ( &ctx->en );
    Delay_1sec ( );
}

uint8_t temphum27_get_alert_pin ( temphum27_t *ctx )
{
    return digital_in_read ( &ctx->alr );
}

static uint8_t temphum27_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0xFF;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ ) 
    {
        crc ^= data_buf[ byte_cnt ];
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {    
                crc = ( uint8_t ) ( ( crc << 1 ) ^ 0x1D );
            }
            else
            {
                crc <<= 1;
            }    
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
