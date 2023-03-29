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
 * @file barometer4.c
 * @brief Barometer 4 Click Driver.
 */

#include "barometer4.h"

/**
 * @brief Barometer 4 crc constants.
 * @details Specified constants for crc 
 * of Barometer 4 Click driver.
 */
#define BAROMETER4_POLYNOM                0x31
#define BAROMETER4_INIT_VAL               0xFF

/**
 * @brief Barometer 4 transmit temperature or pressure first constants.
 * @details Specified constants for temperature or pressure first 
 * of Barometer 4 Click driver.
 */
#define BAROMETER4_DATA_T_FIRST           0
#define BAROMETER4_DATA_P_FIRST           1

/**
 * @brief Barometer 4 operation mode selection constants.
 * @details Specified constants for operation mode selection
 * of Barometer 4 Click driver.
 */
#define BAROMETER4_OP_MODE_DELAY_LP       0
#define BAROMETER4_OP_MODE_DELAY_N        1
#define BAROMETER4_OP_MODE_DELAY_LN       2
#define BAROMETER4_OP_MODE_DELAY_ULN      3

/** 
 * @brief Barometer 4 Dallas/Maxim calculation for CRC8 function.
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
 * @brief Barometer 4 calculate conversion constants function.
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

/**
 * @brief The delay selection function.
 * @details This function performs a delay depending on the selected  operation mode:
 *         @li @c LP Low Power delay of the 2 milliseconds,
 *         @li @c N  Normal delay of the 7 milliseconds,
 *         @li @c LN Low Noise delay of the 24 milliseconds, 
 *         @li @c LN Ultra-Low Noise delay of the 95 milliseconds.  
 * @return Nothing.
 */
static void ( *delay_ptr[ 4 ] )( void ) = {
    delay_op_mode_low_power,
    delay_op_mode_normal,
    delay_op_mode_low_noise,
    delay_op_mode_ultra_low_noise
};

void barometer4_cfg_setup ( barometer4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BAROMETER4_SET_DEV_ADDR;
}

err_t barometer4_init ( barometer4_t *ctx, barometer4_cfg_t *cfg ) 
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

err_t barometer4_default_cfg ( barometer4_t *ctx ) 
{   
    barometer4_soft_reset( ctx );
    
    return BAROMETER4_OK;
}

err_t barometer4_generic_write ( barometer4_t *ctx, uint16_t cmd, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
    data_buf[ 1 ] = ( uint8_t ) cmd;

    for ( uint8_t cnt = 2; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 2 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 2 );
}

err_t barometer4_generic_read ( barometer4_t *ctx, uint16_t cmd, uint16_t *rx_data, uint8_t rx_len ) 
{
    uint8_t write_reg[ 2 ] = { 0 };
    uint8_t data_buf[ 255 ] = { 0 };
    
    write_reg[ 0 ] = cmd >> 8;
    write_reg[ 1 ] = cmd;

    err_t err_flag = i2c_master_write( &ctx->i2c, write_reg, 2 );
    err_flag |= i2c_master_read( &ctx->i2c, data_buf, rx_len * 2 + rx_len );

    if ( err_flag == BAROMETER4_OK )
    {
        uint8_t rd_cnt = 0;
        for ( uint8_t cnt = 0; cnt < rx_len; cnt++ )
        {
            rx_data[ cnt ] = data_buf[ rd_cnt++ ];
            rx_data[ cnt ] <<= 8;
            rx_data[ cnt ] |= data_buf[ rd_cnt++ ];
            
            if ( data_buf[ rd_cnt ]  != calculate_crc8( rx_data[ cnt ] ) )
            {
                err_flag = BAROMETER4_ERROR;
                break;
            }
            rd_cnt++;
        }
    }
    
    return err_flag;
}

err_t barometer4_set_command ( barometer4_t *ctx, uint16_t cmd ) 
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
    data_buf[ 1 ] = ( uint8_t ) cmd;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t barometer4_soft_reset ( barometer4_t *ctx ) 
{  
    return barometer4_set_command( ctx, BAROMETER4_CMD_SOFT_RESET );
}

err_t barometer4_get_device_id ( barometer4_t *ctx, uint16_t *device_id ) 
{   
    return barometer4_generic_read( ctx, BAROMETER4_CMD_DEVICE_ID, device_id, 1 );
}

err_t barometer4_set_up_otp_read ( barometer4_t *ctx ) 
{  
    uint8_t data_buf[ 5 ] = { 0xC5, 0x95, 0x00, 0x66, 0x9C };

    return i2c_master_write( &ctx->i2c, data_buf, 5 );
}

err_t barometer4_get_otp ( barometer4_t *ctx, uint16_t *otp_data ) 
{   
    err_t err_flag = BAROMETER4_OK;
    uint8_t rx_buf[ 12 ];
    
    err_flag |= barometer4_set_up_otp_read ( ctx );
    delay_cfg();
    err_flag |= barometer4_set_command( ctx, BAROMETER4_CMD_READ_OTP );
    delay_cfg();
    err_flag |= i2c_master_read( &ctx->i2c, rx_buf, 12 );
    
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        otp_data[ cnt ] = rx_buf[ cnt * 3 ]; 
        otp_data[ cnt ] <<= 8;    
        otp_data[ cnt ] |= rx_buf[ cnt * 3 + 1 ]; 
    }
    
    return err_flag;
}

err_t barometer4_inv_invpres_calibration ( barometer4_t *ctx, barometer4_invpres_t *cfg_data )
{
    uint16_t otp[ 4 ];
    
    err_t err_flag = barometer4_get_otp( ctx, otp );
    delay_cfg( );

    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        cfg_data->sensor_constants[ cnt ] = ( float ) otp[ cnt ]; 
    }

    cfg_data->p_pa_calib[ 0 ] = 45000.0;
    cfg_data->p_pa_calib[ 1 ] = 80000.0;
    cfg_data->p_pa_calib[ 2 ] = 96700.0;
    cfg_data->lut_lower       = 3670016.0;
    cfg_data->lut_upper       = 12058624.0;
    cfg_data->quadr_factor    = 5.960464477539063e-8;
    cfg_data->offst_factor    = 2048.0;
    cfg_data->op_mode         = BAROMETER4_OP_MODE_NORMAL;

    return err_flag;
}

err_t barometer4_get_pressure_and_temperature ( barometer4_t *ctx,  float *pressure, float *temperature )
{
    uint16_t t_lsb, measurement_comd;
    uint32_t p_lsb;
    float t;
    float data_in[ 3 ];
    float data_out[ 3 ];
    float A,B,C;
    barometer4_invpres_t cfg_data;

    err_t err_flag = barometer4_inv_invpres_calibration( ctx, &cfg_data );
    delay_cfg( );
    
    switch ( cfg_data.op_mode ) 
    {
        case BAROMETER4_OP_MODE_LOW_POWER: 
        {
            measurement_comd = BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_POWER;
            break;
        }
        case BAROMETER4_OP_MODE_NORMAL: 
        {
            measurement_comd = BAROMETER4_CMD_OP_MODE_T_FIRST_NORMAL;
            break;
        }
        case BAROMETER4_OP_MODE_LOW_NOISE: 
        {
            measurement_comd = BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_NOISE;
            break;
        }
        case BAROMETER4_OP_MODE_ULTRA_LOW_NOISE: 
        {
            measurement_comd = BAROMETER4_CMD_OP_MODE_T_FIRST_ULTRA_LOW_NOISE;
            break;
        }
        default: 
        {
            measurement_comd = BAROMETER4_CMD_OP_MODE_T_FIRST_NORMAL;
            break;
        }
    }
    
    barometer4_get_raw_data( ctx, measurement_comd, &p_lsb, &t_lsb );
    delay_cfg( );

    t = ( float ) t_lsb - 32768.0;
    
    data_in[ 0 ] = cfg_data.lut_lower + ( ( float ) ( cfg_data.sensor_constants[ 0 ] * t * t) * cfg_data.quadr_factor );
    data_in[ 1 ] = ( cfg_data.offst_factor * cfg_data.sensor_constants[ 3 ] ) + ( ( float ) ( cfg_data.sensor_constants[ 1 ] * t * t ) * cfg_data.quadr_factor );
    data_in[ 2 ] = cfg_data.lut_upper + ( ( float ) ( cfg_data.sensor_constants[ 2 ] * t * t ) * cfg_data.quadr_factor );

    calculate_conversion_constants( cfg_data.p_pa_calib, data_in, data_out );
    
    A = data_out[ 0 ];
    B = data_out[ 1 ];
    C = data_out[ 2 ];
    
    *pressure = A + ( B / ( C + ( float ) ( p_lsb >> 8 ) ) );
    *temperature = -45.0 + 175.0/65536.0 * t_lsb;

    return err_flag;
}

err_t barometer4_get_raw_data ( barometer4_t *ctx, uint16_t measurement_comd, uint32_t *pressure, uint16_t *temperature ) 
{
    uint8_t rx_buf[ 9 ] = { 0 };
    uint8_t tx_first_data;
    uint8_t op_mode_delay;
    err_t err_flag = BAROMETER4_OK;
    
    switch ( measurement_comd ) 
    {
        case BAROMETER4_CMD_OP_MODE_P_FIRST_LOW_POWER: 
        {
            tx_first_data = BAROMETER4_DATA_T_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_LP;
            break;
        }
        case BAROMETER4_CMD_OP_MODE_P_FIRST_NORMAL: 
        {
            tx_first_data = BAROMETER4_DATA_T_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_N;
            break;
        }
        case BAROMETER4_CMD_OP_MODE_P_FIRST_LOW_NOISE: 
        {
            tx_first_data = BAROMETER4_DATA_T_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_LN;
            break;
        }
        case BAROMETER4_CMD_OP_MODE_P_FIRST_ULTRA_LOW_NOISE: 
        {
            tx_first_data = BAROMETER4_DATA_T_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_ULN;
            break;
        }
        case BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_POWER: 
        {
            tx_first_data = BAROMETER4_DATA_P_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_LP;
            break;
        }
        case BAROMETER4_CMD_OP_MODE_T_FIRST_NORMAL: 
        {
            tx_first_data = BAROMETER4_DATA_P_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_N;
            break;
        }
        case BAROMETER4_CMD_OP_MODE_T_FIRST_LOW_NOISE: 
        {
            tx_first_data = BAROMETER4_DATA_P_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_LN;
            break;
        }
        case BAROMETER4_CMD_OP_MODE_T_FIRST_ULTRA_LOW_NOISE: 
        {
            tx_first_data = BAROMETER4_DATA_P_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_ULN;
            break;
        }
        default: 
        {
            err_flag = BAROMETER4_ERROR;
            tx_first_data = BAROMETER4_DATA_T_FIRST;
            op_mode_delay = BAROMETER4_OP_MODE_DELAY_N;
        }
    }
    
    err_flag |= barometer4_set_command( ctx, measurement_comd );
    ( *delay_ptr[ op_mode_delay ] )( );
    err_flag |= i2c_master_read( &ctx->i2c, rx_buf, 9 );
    
    if ( tx_first_data == 0 )
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
    else if ( tx_first_data == 1 )
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
    
    return err_flag;
}

static uint8_t calculate_crc8 ( uint16_t data_to_calculate )
{
    uint8_t crc = BAROMETER4_INIT_VAL;
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
                crc = ( uint8_t ) ( ( crc << 1 ) ^ BAROMETER4_POLYNOM );
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
    float A,B,C;

    C = ( p_lut[ 0 ] * p_lut[ 1 ] * ( p_pa[ 0 ] - p_pa[ 1 ] ) +
          p_lut[ 1 ] * p_lut[ 2 ] * ( p_pa[ 1 ] - p_pa[ 2 ] ) +
          p_lut[ 2 ] * p_lut[ 0 ] * ( p_pa[ 2 ] - p_pa[ 0 ] ) ) / 
        ( p_lut[ 2 ] * ( p_pa[ 0 ] - p_pa[ 1 ]) +
          p_lut[ 0 ] * ( p_pa[ 1 ] - p_pa[ 2 ]) +
          p_lut[ 1 ] * ( p_pa[ 2 ] - p_pa[ 0 ] ) );
    A = ( p_pa[ 0 ] * p_lut[ 0 ] - p_pa[ 1 ] * p_lut[ 1 ] - ( p_pa[ 1 ] - p_pa[ 0 ] ) * C ) / ( p_lut[ 0 ] - p_lut[ 1 ] );
    B = ( p_pa[ 0 ] - A ) * ( p_lut[ 0 ] + C );

    data_out[ 0 ] = A;
    data_out[ 1 ] = B;
    data_out[ 2 ] = C;
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
