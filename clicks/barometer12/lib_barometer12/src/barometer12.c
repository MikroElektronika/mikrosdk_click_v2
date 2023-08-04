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
 * @file barometer12.c
 * @brief Barometer 12 Click Driver.
 */

#include "barometer12.h"

/**
 * @brief Barometer 12 crc constants.
 * @details Specified constants for crc 
 * of Barometer 12 Click driver.
 */
#define BAROMETER12_POLYNOM                0x31
#define BAROMETER12_INIT_VAL               0xFF

/**
 * @brief Barometer 12 transmit temperature or pressure first constants.
 * @details Specified constants for temperature or pressure first 
 * of Barometer 12 Click driver.
 */
#define BAROMETER12_DATA_T_FIRST           0
#define BAROMETER12_DATA_P_FIRST           1

/** 
 * @brief Barometer 12 Dallas/Maxim calculation for CRC8 function.
 * @details This function calculates CRC8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 +1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @li @c  Example CRC(0xBEEF) = 0x92
 * @param[in] data_to_calculate : Word to calculate crc from.
 * @return Calculated CRC.
 */
static uint8_t calculate_crc8 ( uint16_t data_to_calculate );

/**
 * @brief Barometer 12 calculate conversion constants function.
 * @details This function calculates conversion.
 * @param[in] p_pa : List of 3 values corresponding to applied pressure in Pa.
 * @param[in] p_lut : List of 3 values corresponding to the measured p_LUT values at the applied pressures.
 * @param[out] data_out : List of 3 values calculation results.
 * @return Nothing.
 */
static void calculate_conversion_constants ( float *p_pa, float *p_lut, float *data_out );

/**
 * @brief The configuration delay function.
 * @details This function performs a delay of the 10 milliseconds.
 * @return Nothing.
 */
static void delay_cfg ( void );

/**
 * @brief The low power operation mode delay function.
 * @details This function performs a delay of the 2 milliseconds.
 * @return Nothing.
 */
static void delay_op_mode_low_power ( void );

/**
 * @brief The normal operation mode delay function.
 * @details This function performs a delay of the 7 milliseconds.
 * @return Nothing.
 */
static void delay_op_mode_normal ( void );

/**
 * @brief The low noise operation mode delay function.
 * @details This function performs a delay of the 24 milliseconds.
 * @return Nothing.
 */
static void delay_op_mode_low_noise ( void );

/**
 * @brief The ultra-low noise operation mode delay function.
 * @details This function performs a delay of the 95 milliseconds.
 * @return Nothing.
 */
static void delay_op_mode_ultra_low_noise ( void );

void barometer12_cfg_setup ( barometer12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER12_DEVICE_ADDRESS;
}

err_t barometer12_init ( barometer12_t *ctx, barometer12_cfg_t *cfg ) 
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

err_t barometer12_default_cfg ( barometer12_t *ctx ) 
{
    err_t error_flag = BAROMETER12_OK;
    
    error_flag |= barometer12_soft_reset( ctx );
    
    return error_flag;
}

err_t barometer12_generic_write ( barometer12_t *ctx, uint16_t cmd, uint16_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
    data_buf[ 1 ] = ( uint8_t ) cmd;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 2 );
}

err_t barometer12_generic_read ( barometer12_t *ctx, uint16_t cmd, uint16_t *data_out, uint8_t len ) 
{
    err_t error_flag = BAROMETER12_OK;
    uint8_t tx_buf[ 2 ] = { 0 };
    uint8_t data_buf[ 765 ] = { 0 };
    tx_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) cmd;
    
    error_flag |= i2c_master_write( &ctx->i2c, tx_buf, 2 );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, len * 3 );
    
    if ( BAROMETER12_OK == error_flag )
    {
        uint8_t rd_cnt = 0;
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {
            data_out[ cnt ] = data_buf[ rd_cnt++ ];
            data_out[ cnt ] <<= 8;
            data_out[ cnt ] |= data_buf[ rd_cnt++ ];
            
            if ( data_buf[ rd_cnt ]  != calculate_crc8( data_out[ cnt ] ) )
            {
                error_flag = BAROMETER12_ERROR;
                break;
            }
            rd_cnt++;
        }
    }
    
    return error_flag;
}

err_t barometer12_set_command ( barometer12_t *ctx, uint16_t cmd ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
    data_buf[ 1 ] = ( uint8_t ) cmd;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t barometer12_soft_reset ( barometer12_t *ctx ) 
{  
    return barometer12_set_command( ctx, BAROMETER12_CMD_SOFT_RESET );
}

err_t barometer12_get_device_id ( barometer12_t *ctx, uint16_t *device_id ) 
{   
    return barometer12_generic_read( ctx, BAROMETER12_CMD_DEVICE_ID, device_id, 1 );
}

err_t barometer12_set_up_otp_read ( barometer12_t *ctx ) 
{  
    uint8_t data_buf[ 5 ];
    data_buf[ 0 ] = ( uint8_t ) ( BAROMETER12_CMD_OTP_READ_ADDRESS_REG >> 8 );
    data_buf[ 1 ] = ( uint8_t ) BAROMETER12_CMD_OTP_READ_ADDRESS_REG;
    data_buf[ 2 ] = ( uint8_t ) ( BAROMETER12_CMD_OTP_READ_ADDRESS_PARAM >> 8 );
    data_buf[ 3 ] = ( uint8_t ) BAROMETER12_CMD_OTP_READ_ADDRESS_PARAM;
    data_buf[ 4 ] = calculate_crc8( BAROMETER12_CMD_OTP_READ_ADDRESS_PARAM );
    
    return i2c_master_write( &ctx->i2c, data_buf, 5 );
}

err_t barometer12_get_otp ( barometer12_t *ctx, uint16_t *otp_data ) 
{   
    err_t error_flag = BAROMETER12_OK;
    uint8_t rx_buf[ 12 ];
    
    error_flag |= barometer12_set_up_otp_read ( ctx );
    delay_cfg( );
    error_flag |= barometer12_set_command( ctx, BAROMETER12_CMD_READ_OTP );
    delay_cfg( );
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, 12 );
    
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        otp_data[ cnt ] = rx_buf[ cnt * 3 ]; 
        otp_data[ cnt ] <<= 8;    
        otp_data[ cnt ] |= rx_buf[ cnt * 3 + 1 ]; 
    }
    
    return error_flag;
}

err_t barometer12_inv_invpres_calib ( barometer12_t *ctx, barometer12_invpres_t *cfg_data )
{
    uint16_t otp[ 4 ];
    
    err_t error_flag = barometer12_get_otp( ctx, otp );
    delay_cfg( );

    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        cfg_data->sensor_constants[ cnt ] = ( float ) otp[ cnt ]; 
    }

    cfg_data->p_pa_calib[ 0 ] = BAROMETER12_P_PA_CALIB_0;
    cfg_data->p_pa_calib[ 1 ] = BAROMETER12_P_PA_CALIB_1;
    cfg_data->p_pa_calib[ 2 ] = BAROMETER12_P_PA_CALIB_2;
    cfg_data->lut_lower       = BAROMETER12_LUT_LOWER;
    cfg_data->lut_upper       = BAROMETER12_LUT_UPPER;
    cfg_data->quadr_factor    = BAROMETER12_QUADR_FACTOR;
    cfg_data->offst_factor    = BAROMETER12_OFFSET_FACTOR;
    cfg_data->op_mode         = BAROMETER12_OP_MODE_NORMAL;

    return error_flag;
}

err_t barometer12_get_raw_data ( barometer12_t *ctx, uint16_t measurement_comd, uint32_t *pressure, uint16_t *temperature ) 
{
    uint8_t rx_buf[ 9 ] = { 0 };
    uint8_t tx_first_data;
    err_t error_flag = BAROMETER12_OK;
    
    error_flag |= barometer12_set_command( ctx, measurement_comd );
    switch ( measurement_comd ) 
    {
        case BAROMETER12_CMD_OP_MODE_P_FIRST_LOW_POWER: 
        {
            tx_first_data = BAROMETER12_DATA_T_FIRST;
            delay_op_mode_low_power( );
            break;
        }
        case BAROMETER12_CMD_OP_MODE_P_FIRST_NORMAL: 
        {
            tx_first_data = BAROMETER12_DATA_T_FIRST;
            delay_op_mode_normal( );
            break;
        }
        case BAROMETER12_CMD_OP_MODE_P_FIRST_LOW_NOISE: 
        {
            tx_first_data = BAROMETER12_DATA_T_FIRST;
            delay_op_mode_low_noise( );
            break;
        }
        case BAROMETER12_CMD_OP_MODE_P_FIRST_ULTRA_LOW_NOISE: 
        {
            tx_first_data = BAROMETER12_DATA_T_FIRST;
            delay_op_mode_ultra_low_noise( );
            break;
        }
        case BAROMETER12_CMD_OP_MODE_T_FIRST_LOW_POWER: 
        {
            tx_first_data = BAROMETER12_DATA_P_FIRST;
            delay_op_mode_low_power( );
            break;
        }
        case BAROMETER12_CMD_OP_MODE_T_FIRST_NORMAL: 
        {
            tx_first_data = BAROMETER12_DATA_P_FIRST;
            delay_op_mode_normal( );
            break;
        }
        case BAROMETER12_CMD_OP_MODE_T_FIRST_LOW_NOISE: 
        {
            tx_first_data = BAROMETER12_DATA_P_FIRST;
            delay_op_mode_low_noise( );
            break;
        }
        case BAROMETER12_CMD_OP_MODE_T_FIRST_ULTRA_LOW_NOISE: 
        {
            tx_first_data = BAROMETER12_DATA_P_FIRST;
            delay_op_mode_ultra_low_noise( );
            break;
        }
        default: 
        {
            error_flag = BAROMETER12_ERROR;
            tx_first_data = BAROMETER12_DATA_T_FIRST;
            delay_op_mode_normal( );
        }
    }
    
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, 9 );
    
    if ( BAROMETER12_DATA_T_FIRST == tx_first_data )
    {
        *pressure = rx_buf[ 0 ];
        *pressure <<= 8;
        *pressure |= rx_buf[ 1 ];
        *pressure <<= 8;
        *pressure |= rx_buf[ 3 ];
        *pressure <<= 8;
        *pressure |= rx_buf[ 4 ];
        
        *temperature = rx_buf[ 6 ];
        *temperature <<= 8;
        *temperature |= rx_buf[ 7 ];        
    }
    else if ( BAROMETER12_DATA_P_FIRST == tx_first_data )
    {
        *temperature = rx_buf[ 0 ];
        *temperature <<= 8;
        *temperature |= rx_buf[ 1 ];  
        
        *pressure = rx_buf[ 3 ];
        *pressure <<= 8;
        *pressure |= rx_buf[ 4 ];
        *pressure <<= 8;
        *pressure |= rx_buf[ 6 ];
        *pressure <<= 8;
        *pressure |= rx_buf[ 7 ];
    }
    
    return error_flag;
}

err_t barometer12_get_press_and_temp ( barometer12_t *ctx,  float *pressure, float *temperature )
{
    uint16_t t_lsb, measurement_comd;
    uint32_t p_lsb;
    float t_val;
    float data_in[ 3 ];
    float data_out[ 3 ];
    float a_val, b_val, c_val;
    barometer12_invpres_t cfg_data;

    err_t error_flag = barometer12_inv_invpres_calib( ctx, &cfg_data );
    delay_cfg( );
    
    switch ( cfg_data.op_mode ) 
    {
        case BAROMETER12_OP_MODE_LOW_POWER: 
        {
            measurement_comd = BAROMETER12_CMD_OP_MODE_T_FIRST_LOW_POWER;
            break;
        }
        case BAROMETER12_OP_MODE_NORMAL: 
        {
            measurement_comd = BAROMETER12_CMD_OP_MODE_T_FIRST_NORMAL;
            break;
        }
        case BAROMETER12_OP_MODE_LOW_NOISE: 
        {
            measurement_comd = BAROMETER12_CMD_OP_MODE_T_FIRST_LOW_NOISE;
            break;
        }
        case BAROMETER12_OP_MODE_ULTRA_LOW_NOISE: 
        {
            measurement_comd = BAROMETER12_CMD_OP_MODE_T_FIRST_ULTRA_LOW_NOISE;
            break;
        }
        default: 
        {
            measurement_comd = BAROMETER12_CMD_OP_MODE_T_FIRST_NORMAL;
            break;
        }
    }
    
    barometer12_get_raw_data( ctx, measurement_comd, &p_lsb, &t_lsb );
    delay_cfg( );

    t_val = ( float ) t_lsb - 32768.0;
    
    data_in[ 0 ] = cfg_data.lut_lower + ( ( float ) ( cfg_data.sensor_constants[ 0 ] * t_val * t_val ) * cfg_data.quadr_factor );
    data_in[ 1 ] = ( cfg_data.offst_factor * cfg_data.sensor_constants[ 3 ] ) + 
                   ( ( float ) ( cfg_data.sensor_constants[ 1 ] * t_val * t_val ) * cfg_data.quadr_factor );
    data_in[ 2 ] = cfg_data.lut_upper + ( ( float ) ( cfg_data.sensor_constants[ 2 ] * t_val * t_val ) * cfg_data.quadr_factor );

    calculate_conversion_constants( cfg_data.p_pa_calib, data_in, data_out );
    
    a_val = data_out[ 0 ];
    b_val = data_out[ 1 ];
    c_val = data_out[ 2 ];
    
    *pressure = a_val + ( b_val / ( c_val + ( float ) ( p_lsb >> 8 ) ) );
    *temperature = -BAROMETER12_TEMPERATURE_COEF_1 + BAROMETER12_TEMPERATURE_COEF_2 / BAROMETER12_TEMPERATURE_COEF_3 * t_lsb;

    return error_flag;
}

static uint8_t calculate_crc8 ( uint16_t data_to_calculate )
{
    uint8_t crc = BAROMETER12_INIT_VAL;
    uint8_t ptr[ 2 ] = { 0 };
    
    ptr[ 0 ] = data_to_calculate >> 8;
    ptr[ 1 ] = data_to_calculate;
    
    for ( uint8_t i = 0; i < 2; i++ ) 
    {
        crc ^= ptr[ i ];
        for ( uint8_t j = 0; j < 8; j++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ BAROMETER12_POLYNOM );
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

static void calculate_conversion_constants( float *p_pa, float *p_lut, float *data_out )
{
    float a_val, b_val, c_val;

    c_val = ( p_lut[ 0 ] * p_lut[ 1 ] * ( p_pa[ 0 ] - p_pa[ 1 ] ) +
            p_lut[ 1 ] * p_lut[ 2 ] * ( p_pa[ 1 ] - p_pa[ 2 ] ) +
            p_lut[ 2 ] * p_lut[ 0 ] * ( p_pa[ 2 ] - p_pa[ 0 ] ) ) / 
            ( p_lut[ 2 ] * ( p_pa[ 0 ] - p_pa[ 1 ]) +
            p_lut[ 0 ] * ( p_pa[ 1 ] - p_pa[ 2 ]) +
            p_lut[ 1 ] * ( p_pa[ 2 ] - p_pa[ 0 ] ) );
    a_val = ( p_pa[ 0 ] * p_lut[ 0 ] - p_pa[ 1 ] * p_lut[ 1 ] - 
            ( p_pa[ 1 ] - p_pa[ 0 ] ) * c_val ) / ( p_lut[ 0 ] - p_lut[ 1 ] );
    b_val = ( p_pa[ 0 ] - a_val ) * ( p_lut[ 0 ] + c_val );

    data_out[ 0 ] = a_val;
    data_out[ 1 ] = b_val;
    data_out[ 2 ] = c_val;
}

static void delay_cfg ( void )
{
    Delay_10ms( );
}

static void delay_op_mode_low_power ( void )
{
    Delay_1ms( );
    Delay_1ms( );
}

static void delay_op_mode_normal ( void )
{
    Delay_5ms( );
    Delay_1ms( );
    Delay_1ms( );
}

static void delay_op_mode_low_noise ( void )
{
    Delay_10ms( );
    Delay_10ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}

static void delay_op_mode_ultra_low_noise ( void )
{
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_5ms( );
}

// ------------------------------------------------------------------------- END
