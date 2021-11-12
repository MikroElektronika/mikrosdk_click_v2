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
 * @file hvac.c
 * @brief HVAC Click Driver.
 */

#include "hvac.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Calc CRC function.
 *
 * @details Function given an array and a number of bytes, 
 * this calculate CRC8 for those bytes.
 *
 * @note CRC is only calc'd on the data portion ( two bytes )
 * of the four bytes being sent.
 */
uint8_t dev_calc_crc ( uint8_t *data_data );

/**
 * @brief Calc Serial CRC function.
 *
 * @details Function given an array and a number of bytes,
 * this calculate CRC8 for those bytes.
 *
 * @note CRC is only calc'd on the data portion ( two bytes )
 * of the four bytes being sent.
 */
uint8_t dev_calc_uart_crc ( uint8_t *data_data, uint8_t len );

/**
 * @brief Calculate concentration function.
 *
 * @details Function calculate concentration.
 */
uint32_t dev_calc_concent ( hvac_t *ctx, uint8_t buf_num, uint8_t *tmp_buf );

/**
 * @brief IEEE754 floating point converter.
 *
 * @details Function convert 32-bit value to float.
 */
float dev_ieee_754_floating_point_convert ( uint32_t fp_data );

// --------------------------------------------------------- PUBLIC FUNCTIONS 


void hvac_cfg_setup ( hvac_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HVAC_SCD40_SLAVE_ADDR;
}


err_t hvac_init ( hvac_t *ctx, hvac_cfg_t *cfg ) 
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

err_t hvac_generic_write ( hvac_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t hvac_generic_read ( hvac_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t hvac_scd40_write_data ( hvac_t *ctx, uint16_t reg, uint16_t tx_data )
{
    uint8_t temp[ 2 ];
    uint8_t tx_buf[ 5 ];
    

    tx_buf[ 0 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) reg;

    tx_buf[ 2 ] = ( uint8_t ) ( tx_data >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) tx_data;

    temp[ 0 ] = tx_buf[ 2 ];
    temp[ 1 ] = tx_buf[ 3 ];

    tx_buf[ 4 ] = dev_calc_crc( &temp[ 0 ] );

    err_t error_flag = i2c_master_write( &ctx->i2c, tx_buf, 5 );

    return error_flag;
}

err_t hvac_scd40_read_data ( hvac_t *ctx, uint16_t reg, uint16_t *rx_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 3 ];
    uint16_t result;

    tx_buf[ 0 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) reg;

    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 3 );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    if ( rx_buf[ 2 ] != dev_calc_crc( &rx_buf[ 0 ] ) )
    {
        error_flag = HVAC_ERROR;
    }

    *rx_data = result;

    return error_flag;
}

void hvac_scd40_send_cmd ( hvac_t *ctx, uint16_t cmd )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) cmd;

    i2c_master_write ( &ctx->i2c, tx_buf, 2 );
}

void hvac_scd40_read_measurement ( hvac_t *ctx, measuremen_data_t *read_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 15 ];
    uint16_t tmp;
    float f_temp;

    tx_buf[ 0 ] = ( uint8_t ) ( HVAC_READ_MEASUREMENT >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) HVAC_READ_MEASUREMENT;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 15 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];

    read_data->co2_concent = tmp;
    
    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];
    
    f_temp = ( ( ( float ) tmp ) * 175.0 ) / 65535.0;
    f_temp -= 45.0;
    
    read_data->temperature = f_temp;
    
    tmp = rx_buf[ 6 ];
    tmp <<= 8;
    tmp |= rx_buf[ 7 ];
    
    f_temp = ( ( ( float ) tmp ) * 100.0 ) / 65535.0;
    
    read_data->r_humidity = f_temp;
    
    tmp = rx_buf[ 9 ];
    tmp <<= 8;
    tmp |= rx_buf[ 10 ];

    read_data->asc_update_count = tmp;
    
    tmp = rx_buf[ 12 ];
    tmp <<= 8;
    tmp |= rx_buf[ 13 ];

    read_data->asc_last_correction = tmp;
}

void hvac_scd40_get_serial_number ( hvac_t *ctx, uint16_t *serial_number )
{
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 9 ];
    uint16_t tmp;

    tx_buf[ 0 ] = ( uint8_t ) ( HVAC_GET_SERIAL_NUMBER >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) HVAC_GET_SERIAL_NUMBER;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 9 );

    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];

    serial_number[ 0 ] = tmp;

    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];

    serial_number[ 1 ] = tmp;

    tmp = rx_buf[ 6 ];
    tmp <<= 8;
    tmp |= rx_buf[ 7 ];

    serial_number[ 2 ] = tmp;
}

void hvac_scd40_get_feature_set_version ( hvac_t *ctx, feature_data_t *f_data )
{
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 3 ];

    tx_buf[ 0 ] = ( uint8_t ) ( HVAC_GET_SERIAL_NUMBER >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) HVAC_GET_SERIAL_NUMBER;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
    i2c_master_read( &ctx->i2c, rx_buf, 3 );
    
    f_data->product_type          = rx_buf[ 0 ] >> 4;
    f_data->platform_type         = rx_buf[ 0 ] >> 1;
    f_data->product_major_version = rx_buf[ 1 ] >> 5;
    f_data->product_minor_version = rx_buf[ 1 ];
}

void hvac_scd40_set_temperature_offset ( hvac_t *ctx, float temp_offset )
{
    uint16_t temp_val;

    temp_val = ( uint16_t ) ( temp_offset * 374.0 );
    
    hvac_scd40_write_data( ctx, HVAC_SET_TEMPERATURE_OFFSET, temp_val );
}

float hvac_scd40_get_temperature_offset ( hvac_t *ctx )
{
    uint16_t rx_buf[ 1 ];
    float temp_offset;

    hvac_scd40_read_data( ctx, HVAC_GET_TEMPERATURE_OFFSET, rx_buf );
    
    temp_offset = ( float ) rx_buf[ 0 ];
    temp_offset *= 175.0;
    temp_offset /= 65535.0;
    
    return temp_offset;
}

err_t hvac_sps30_i2c_write_data ( hvac_t *ctx, uint16_t reg, uint16_t tx_data )
{
    uint8_t temp[ 2 ];
    uint8_t tx_buf[ 5 ];

    tx_buf[ 0 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) reg;

    tx_buf[ 2 ] = ( uint8_t ) ( tx_data >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) tx_data;

    temp[ 0 ] = tx_buf[ 2 ];
    temp[ 1 ] = tx_buf[ 3 ];

    tx_buf[ 4 ] = dev_calc_crc( &temp[ 0 ] );
    
    i2c_master_set_slave_address( &ctx->i2c, HVAC_SPS30_SLAVE_ADDR );

    err_t error_flag = i2c_master_write( &ctx->i2c, tx_buf, 5 );
    
    i2c_master_set_slave_address( &ctx->i2c, HVAC_SCD40_SLAVE_ADDR );

    return error_flag;
}

err_t hvac_sps30_i2c_read_data ( hvac_t *ctx, uint16_t reg, uint16_t *rx_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 3 ];
    uint16_t result;
    err_t error_flag;
    
    tx_buf[ 0 ] = ( uint8_t ) ( reg >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) reg;

    i2c_master_set_slave_address( &ctx->i2c, HVAC_SPS30_SLAVE_ADDR );

    error_flag = i2c_master_write( &ctx->i2c, tx_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, 3 );
    
    i2c_master_set_slave_address( &ctx->i2c, HVAC_SCD40_SLAVE_ADDR );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    if ( rx_buf[ 2 ] != dev_calc_crc( &rx_buf[ 0 ] ) )
    {
        error_flag = HVAC_ERROR;
    }

    *rx_data = result;

    return error_flag;
}

void hvac_sps30_start_measurement ( hvac_t *ctx )
{
    hvac_sps30_i2c_write_data( ctx, HVAC_SPS30_I2C_START_MEASUREMENT, 
                                    HVAC_SPS30_I2C_READ_MEASURED_VALUE );
}

void hvac_sps30_stop_measurement ( hvac_t *ctx )
{

    hvac_sps30_i2c_write_data( ctx, HVAC_SPS30_I2C_STOP_MEASUREMENT, 
                                    HVAC_SPS30_I2C_STOP_MEASUREMENT_DUMMY );
}

void hvac_sps30_device_reset ( hvac_t *ctx )
{

    hvac_sps30_i2c_write_data( ctx, HVAC_SPS30_I2C_RESET, HVAC_SPS30_I2C_STOP_MEASUREMENT_DUMMY );
}

uint8_t hvac_sps30_get_ready_flag ( hvac_t *ctx )
{
    uint16_t rx_buf;
    uint8_t ready_flag;
    
    hvac_sps30_i2c_read_data( ctx, HVAC_SPS30_I2C_READ_DATA_RDY_FLAG, &rx_buf );
    
    ready_flag = ( uint8_t ) rx_buf;
    ready_flag &= 0x01;
    return ready_flag;
}

void hvac_sps30_read_measured_data ( hvac_t *ctx, mass_and_num_cnt_data_t *m_n_c_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 60 ];
    uint32_t temp;

    tx_buf[ 0 ] = ( uint8_t ) ( HVAC_SPS30_I2C_READ_MEASURED_VALUE >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) HVAC_SPS30_I2C_READ_MEASURED_VALUE;
    i2c_master_set_slave_address( &ctx->i2c, HVAC_SPS30_SLAVE_ADDR );
    i2c_master_write( &ctx->i2c, tx_buf, 2 );
    i2c_master_read( &ctx->i2c, rx_buf, 60 );
    i2c_master_set_slave_address( &ctx->i2c, HVAC_SCD40_SLAVE_ADDR );
    
    temp = dev_calc_concent( ctx, 1, rx_buf );
    m_n_c_data->mass_pm_1_0 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 2, rx_buf );
    m_n_c_data->mass_pm_2_5 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 3, rx_buf );
    m_n_c_data->mass_pm_4_0 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 4, rx_buf );
    m_n_c_data->mass_pm_10 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 5, rx_buf );
    m_n_c_data->num_pm_0_5 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 6, rx_buf );
    m_n_c_data->num_pm_1_0 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 7, rx_buf );
    m_n_c_data->num_pm_2_5 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 8, rx_buf );
    m_n_c_data->num_pm_4_0 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 9, rx_buf );
    m_n_c_data->num_pm_10 = dev_ieee_754_floating_point_convert( temp );

    temp = dev_calc_concent( ctx, 10, rx_buf );
    m_n_c_data->typ_ptcl_size = dev_ieee_754_floating_point_convert( temp );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

uint8_t dev_calc_crc ( uint8_t *data_data )
{
    uint8_t crc = 0xFF;
    uint8_t bit_bit;
    uint8_t n_cnt;
 
    for ( n_cnt = 0; n_cnt < 2; n_cnt++ )
    {
        crc ^= data_data[ n_cnt ];
         
        for ( bit_bit = 8; bit_bit > 0; --bit_bit )
        {
             if ( crc & 0x80 )
             {
                 crc = ( crc << 1 ) ^ 0x31u;
             }
             else
             {
                 crc = ( crc << 1 );
             }
        }
    }
 
    return crc;
}

uint8_t dev_calc_uart_crc ( uint8_t *data_data, uint8_t len )
{
    uint8_t crc = 0xFF;
    uint8_t bit_bit;
    uint8_t n_cnt;

    for ( n_cnt = 0; n_cnt < len; n_cnt++ )
    {
        crc ^= data_data[ n_cnt ];

        for ( bit_bit = 8; bit_bit > 0; --bit_bit )
        {
             if ( crc & 0x80 )
             {
                 crc = ( crc << 1 ) ^ 0x31u;
             }
             else
             {
                 crc = ( crc << 1 );
             }
        }
    }

    return crc;
}

uint32_t dev_calc_concent ( hvac_t *ctx, uint8_t buf_num, uint8_t *tmp_buf )
{
    uint32_t result;
    uint8_t n_cnt;

    if ( buf_num < 1 )
    {
        buf_num = 1;
    }

    if ( buf_num > 10 )
    {
        buf_num = 10;
    }

    buf_num--;
    
    n_cnt = buf_num * 6;

    result = tmp_buf[ n_cnt ];
    result <<= 8;
    result |= tmp_buf[ n_cnt + 1 ];
    result <<= 8;
    result |= tmp_buf[ n_cnt + 3 ];
    result <<= 8;
    result |= tmp_buf[ n_cnt + 4 ];
    
    return result;
}

float dev_ieee_754_floating_point_convert ( uint32_t fp_data )
{
    uint8_t n_cnt_j;
    uint8_t n_cnt_i;
    float tmp;
    uint8_t bit_bit;
    float result;
    int8_t exp_tmp;
    uint8_t sign_bit;
    uint8_t exponent;
    float mantissa;

    sign_bit = fp_data >> 31;
    sign_bit &= 0x01;

    exponent = ( uint8_t ) ( ( fp_data >> 23 ) & 0xFF );

    if ( exponent > 127 )
    {
        exponent -= 127;
    }

    mantissa = 1.0;

    for ( n_cnt_i = 1; n_cnt_i < 23; n_cnt_i++ )
    {

        bit_bit = fp_data >> ( 23 - n_cnt_i );
        bit_bit &= 0x01;

        if ( bit_bit == 1 )
        {
            tmp = 1.0;

            for ( n_cnt_j = 0; n_cnt_j < n_cnt_i; n_cnt_j++ )
            {
                tmp *= 0.5;
            }

            mantissa += tmp;
        }
    }

    result = 1.0;

    while ( exponent > 0 )
    {
        result *= 2.0;
        exponent--;
    }

    result *= mantissa;

    return result;
}

// ------------------------------------------------------------------------- END
