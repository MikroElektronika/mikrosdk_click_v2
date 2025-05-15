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
 * @file rng2.c
 * @brief RNG 2 Click Driver.
 */

#include "rng2.h"

/**
 * @brief RNG 2 read scl function.
 * @details This function returns the current level of SCL line, 0 or 1.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return Logic level of SCL line.
 * @note None.
 */
static uint8_t rng2_read_scl ( rng2_t *ctx );

/**
 * @brief RNG 2 set scl function.
 * @details This function sets the SCL pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void rng2_set_scl ( rng2_t *ctx );

/**
 * @brief RNG 2 clear scl function.
 * @details This function drives the SCL pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void rng2_clear_scl ( rng2_t *ctx );

/**
 * @brief RNG 2 read sda function.
 * @details This function returns the current level of SDA line, 0 or 1.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return Logic level of SDA line.
 * @note None.
 */
static uint8_t rng2_read_sda ( rng2_t *ctx );

/**
 * @brief RNG 2 set sda function.
 * @details This function sets the SDA pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void rng2_set_sda ( rng2_t *ctx );

/**
 * @brief RNG 2 clear sda function.
 * @details This function drives the SDA pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void rng2_clear_sda ( rng2_t *ctx );

/**
 * @brief RNG 2 i2c stop function.
 * @details This function sends an I2C stop condition signal.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rng2_i2c_stop ( rng2_t *ctx );

/**
 * @brief RNG 2 i2c start function.
 * @details This function sends an I2C start condition signal.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rng2_i2c_start ( rng2_t *ctx );

/**
 * @brief RNG 2 i2c write bit function.
 * @details This function writes a LSB bit of data_in to the I2C bus.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @param[in] data_in : A LSB of this byte is written to the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rng2_i2c_write_bit ( rng2_t *ctx, uint8_t data_in );

/**
 * @brief RNG 2 i2c read bit function.
 * @details This function reads a bit from the I2C bus and stores it into the LSB of data_out.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @param[out] data_out : A LSB of this byte is read from the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rng2_i2c_read_bit ( rng2_t *ctx, uint8_t *data_out );

/**
 * @brief RNG 2 i2c write byte function.
 * @details This function write a data_in byte to the I2C bus. Also sends a start/stop condition
 * if a send_start/send_stop is true.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @param[in] data_in : Data byte to be written.
 * @param[in] send_start : 0 - exclude sending start signal, != 0 - sends a start signal in the beginning.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - ACKed by the target device,
 *         @li @c -1 - Error - timeout, lost arbitration, busy line, or NACK received.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rng2_i2c_write_byte ( rng2_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop );

/**
 * @brief RNG 2 i2c read byte function.
 * @details This function reads a byte from I2C bus and stores it into data_out. Sends NACK if nack is true,
 * otherwise responds with ACK. Also sends a stop condition if send_stop is true.
 * @param[in] ctx : Click context object.
 * See #rng2_t object definition for detailed explanation.
 * @param[out] data_out : Data byte read from the bus.
 * @param[in] nack : 0 - responds with ACK signal, != 0 - responds with a NACK signal.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout, lost arbitration, or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rng2_i2c_read_byte ( rng2_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop );

/** 
 * @brief RNG 2 Reflect bits function.
 * @details This function reflects a desired number of bits in data word.
 * @return Reflected data.
 * @note None.
 */
static uint16_t rng2_reflect_bits( uint16_t data_in, uint8_t len );

/** 
 * @brief RNG 2 CRC-16 calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x8005 ( x16 + x15 + x2 + x0 )
 * @li @c  Initialization 0x0000
 * @li @c  Reflect input True
 * @li @c  Reflect output False
 * @li @c  Final Xor 0x0000
 * @li @c  Example { 07, 30, 01, 00, 00 } - 0xD700
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t rng2_calculate_crc16 ( uint8_t *data_buf, uint16_t len );

void rng2_cfg_setup ( rng2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_address = RNG2_DEVICE_ADDRESS;
}

err_t rng2_init ( rng2_t *ctx, rng2_cfg_t *cfg ) 
{
    ctx->slave_address = cfg->i2c_address;
    
    ctx->scl = cfg->scl;
    ctx->sda = cfg->sda;
    ctx->i2c_started = false;

    rng2_set_scl ( ctx );
    rng2_set_sda ( ctx );
    Delay_100ms ( );

    return RNG2_OK;
}

err_t rng2_default_cfg ( rng2_t *ctx ) 
{
    err_t error_flag = RNG2_OK;
    rng2_send_wake ( ctx );
    Delay_100ms ( );
    if ( RNG2_ERROR == rng2_read_info ( ctx ) )
    {
        return RNG2_ERROR;
    }
    return error_flag;
}

void rng2_send_wake ( rng2_t *ctx )
{
    rng2_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, true );
}

err_t rng2_reset_counter ( rng2_t *ctx )
{
    err_t error_flag = RNG2_OK;
    error_flag |= rng2_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= rng2_i2c_write_byte ( ctx, RNG2_WORD_RESET, false, true );
    return error_flag;
}

err_t rng2_i2c_sync ( rng2_t *ctx )
{
    err_t error_flag = RNG2_OK;
    uint8_t dummy_data = 0;
    error_flag |= rng2_i2c_start ( ctx );
    for ( int8_t bit_cnt = 8; bit_cnt >= 0; bit_cnt-- )
    {
        error_flag |= rng2_i2c_write_bit ( ctx, 1 );
    }
    error_flag |= rng2_i2c_start ( ctx );
    error_flag |= rng2_i2c_stop ( ctx );
    error_flag |= rng2_i2c_write_byte ( ctx, ( ( ctx->slave_address << 1 ) | 1 ), true, false );
    error_flag |= rng2_i2c_read_byte ( ctx, &dummy_data, true, true );
    if ( RNG2_OK == error_flag )
    {
        error_flag |= rng2_reset_counter ( ctx );
    }
    return error_flag;
}

err_t rng2_low_power_mode ( rng2_t *ctx )
{
    err_t error_flag = RNG2_OK;
    error_flag |= rng2_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= rng2_i2c_write_byte ( ctx, RNG2_WORD_SLEEP, false, true );
    return error_flag;
}

err_t rng2_write_packet ( rng2_t *ctx )
{
    err_t error_flag = RNG2_OK;
    uint8_t group_buf[ RNG2_GROUP_MAX_BYTES ] = { 0 };
    uint16_t crc16 = 0;
    if ( ctx->cmd_pkt.data_len > RNG2_GROUP_MAX_DATA_LEN )
    {
        return RNG2_ERROR;
    }
    group_buf[ 0 ] = ctx->cmd_pkt.data_len + 7;
    group_buf[ 1 ] = ctx->cmd_pkt.opcode;
    group_buf[ 2 ] = ctx->cmd_pkt.param1;
    group_buf[ 3 ] = ( uint8_t ) ( ctx->cmd_pkt.param2 & 0xFF );
    group_buf[ 4 ] = ( uint8_t ) ( ( ctx->cmd_pkt.param2 >> 8 ) & 0xFF );
    if ( ctx->cmd_pkt.data_len )
    {
        memcpy ( &group_buf[ 5 ], ctx->cmd_pkt.data_buf, ctx->cmd_pkt.data_len );
    }
    crc16 = rng2_calculate_crc16 ( group_buf, group_buf[ 0 ] - 2 );
    group_buf[ group_buf[ 0 ] - 2 ] = ( uint8_t ) ( crc16 & 0xFF );
    group_buf[ group_buf[ 0 ] - 1 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
    error_flag |= rng2_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= rng2_i2c_write_byte ( ctx, RNG2_WORD_CMD, false, false );
    for ( uint8_t cnt = 0; cnt < ( group_buf[ 0 ] - 1 ); cnt++ )
    {
        error_flag |= rng2_i2c_write_byte ( ctx, group_buf[ cnt ], false, false );
    }
    error_flag |= rng2_i2c_write_byte ( ctx, group_buf[ group_buf[ 0 ] - 1 ], false, true );
    return error_flag;
}

err_t rng2_read_packet ( rng2_t *ctx )
{
    err_t error_flag = RNG2_OK;
    uint8_t group_buf[ RNG2_GROUP_MAX_BYTES ] = { 0 };
    uint16_t crc16 = 0;
    uint8_t cnt = 0;
    error_flag |= rng2_i2c_write_byte ( ctx, ( ( ctx->slave_address << 1 ) | 1 ), true, false );
    error_flag |= rng2_i2c_read_byte ( ctx, &group_buf[ 0 ], false, false );
    if ( ( group_buf[ 0 ] > RNG2_GROUP_MAX_BYTES ) || ( group_buf[ 0 ] < RNG2_GROUP_MIN_BYTES ) )
    {
        return RNG2_ERROR;
    }
    for ( cnt = 1; cnt < ( group_buf[ 0 ] - 1 ); cnt++ )
    {
        error_flag |= rng2_i2c_read_byte ( ctx, &group_buf[ cnt ], false, false );
    }
    error_flag |= rng2_i2c_read_byte ( ctx, &group_buf[ group_buf[ 0 ] - 1 ], true, true );
    crc16 = ( ( uint16_t ) group_buf[ group_buf[ 0 ] - 1 ] << 8 ) | group_buf[ group_buf[ 0 ] - 2 ];
    if ( crc16 == rng2_calculate_crc16 ( group_buf, group_buf[ 0 ] - 2 ) )
    {
        ctx->rsp_pkt.data_len = group_buf[ 0 ] - 3;
        memcpy( ctx->rsp_pkt.data_buf, &group_buf[ 1 ], ctx->rsp_pkt.data_len );
    }
    return error_flag;
}

err_t rng2_read_info ( rng2_t *ctx )
{
    err_t error_flag = RNG2_OK;
    ctx->cmd_pkt.opcode = RNG2_CMD_INFO;
    ctx->cmd_pkt.param1 = RNG2_PARAM1_INFO;
    ctx->cmd_pkt.param2 = RNG2_PARAM2_INFO;
    ctx->cmd_pkt.data_len = 0;
    error_flag |= rng2_write_packet ( ctx );
    Delay_1ms ( );
    error_flag |= rng2_read_packet ( ctx );
    if ( ( RNG2_INFO_DATA_LEN != ctx->rsp_pkt.data_len ) || 
         ( RNG2_INFO_DEVICE_ID != ctx->rsp_pkt.data_buf[ 1 ] ) || 
         ( RNG2_INFO_SILICON_ID != ctx->rsp_pkt.data_buf[ 2 ] ) )
    {
        error_flag |= RNG2_ERROR;
    }
    return error_flag;
}

err_t rng2_read_random_num ( rng2_t *ctx )
{
    err_t error_flag = RNG2_OK;
    ctx->cmd_pkt.opcode = RNG2_CMD_RANDOM;
    ctx->cmd_pkt.param1 = RNG2_PARAM1_RANDOM;
    ctx->cmd_pkt.param2 = RNG2_PARAM2_RANDOM;
    memset ( ctx->cmd_pkt.data_buf, 0, RNG2_RANDOM_DATA_IN_LEN );
    ctx->cmd_pkt.data_len = RNG2_RANDOM_DATA_IN_LEN;
    error_flag |= rng2_write_packet ( ctx );
    Delay_100ms ( );
    error_flag |= rng2_read_packet ( ctx );
    if ( RNG2_RANDOM_DATA_OUT_LEN != ctx->rsp_pkt.data_len )
    {
        error_flag |= RNG2_ERROR;
    }
    return error_flag;
}

static uint8_t rng2_read_scl ( rng2_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
    return ( uint8_t ) ( 0 != digital_in_read ( &scl ) );
}

static void rng2_set_scl ( rng2_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
}

static void rng2_clear_scl ( rng2_t *ctx )
{
    digital_out_t scl;
    digital_out_init ( &scl, ctx->scl );
    digital_out_low ( &scl );
}

static uint8_t rng2_read_sda ( rng2_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
    return ( uint8_t ) ( 0 != digital_in_read ( &sda ) );
}

static void rng2_set_sda ( rng2_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
}

static void rng2_clear_sda ( rng2_t *ctx )
{
    digital_out_t sda;
    digital_out_init ( &sda, ctx->sda );
    digital_out_low ( &sda );
}

static err_t rng2_i2c_start ( rng2_t *ctx )
{
    uint32_t timeout_cnt = 0;
    if ( ctx->i2c_started ) 
    { 
        // If started, do a restart condition, set SDA
        rng2_set_sda ( ctx );
        Delay_10us ( );
        rng2_set_scl ( ctx );
        while ( 0 == rng2_read_scl ( ctx ) ) 
        {   
            // Clock stretching
            if ( ++timeout_cnt > RNG2_I2C_TIMEOUT )
            {
                return RNG2_ERROR;
            }
        }
        // Repeated start setup time, minimum 4.7us
        Delay_10us ( );
    }

    if ( 0 == rng2_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return RNG2_ERROR;
    }

    // SCL is high, clear SDA
    rng2_clear_sda ( ctx );
    Delay_10us ( );
    rng2_clear_scl ( ctx );
    ctx->i2c_started = true;
    return RNG2_OK;
}

static err_t rng2_i2c_stop ( rng2_t *ctx )
{
    uint32_t timeout_cnt = 0;
    // Clear SDA
    rng2_clear_sda ( ctx );
    Delay_10us ( );

    rng2_set_scl ( ctx );
    while ( 0 == rng2_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > RNG2_I2C_TIMEOUT )
        {
            return RNG2_ERROR;
        }
    }

    // Stop bit setup time, minimum 4us
    Delay_10us ( );

    // SCL is high, set SDA
    rng2_set_sda ( ctx );
    Delay_10us ( );

    if ( 0 == rng2_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return RNG2_ERROR;
    }
    ctx->i2c_started = false;
    return RNG2_OK;
}

static err_t rng2_i2c_write_bit ( rng2_t *ctx, uint8_t data_in )
{
    uint32_t timeout_cnt = 0;
    if ( data_in ) 
    {
        rng2_set_sda ( ctx );
    } 
    else 
    {
        rng2_clear_sda ( ctx );
    }

    // SDA change propagation delay
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    rng2_set_scl ( ctx );

    // Wait for SDA value to be read by target, minimum of 4us for standard mode
    Delay_10us ( );

    while ( 0 == rng2_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > RNG2_I2C_TIMEOUT )
        {
            return RNG2_ERROR;
        }
    }

    // SCL is high, now data is valid
    // If SDA is high, check that nobody else is driving SDA
    if ( data_in && ( 0 == rng2_read_sda ( ctx ) ) ) 
    {
        return RNG2_ERROR;
    }

    // Clear the SCL to low in preparation for next change
    rng2_clear_scl ( ctx );
    return RNG2_OK;
}

static err_t rng2_i2c_read_bit ( rng2_t *ctx, uint8_t *data_out ) 
{
    uint32_t timeout_cnt = 0;
    // Let the target drive data
    rng2_set_sda ( ctx );

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    rng2_set_scl ( ctx );

    while ( 0 == rng2_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > RNG2_I2C_TIMEOUT )
        {
            return RNG2_ERROR;
        }
    }

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // SCL is high, read out bit
    *data_out = rng2_read_sda ( ctx );

    // Set SCL low in preparation for next operation
    rng2_clear_scl ( ctx );

    return RNG2_OK;
}

static err_t rng2_i2c_write_byte ( rng2_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop )
{
    err_t error_flag = RNG2_OK;
    uint8_t nack = 0;

    if ( send_start ) 
    {
        error_flag |= rng2_i2c_start ( ctx );
    }

    for ( int8_t bit_cnt = 7; bit_cnt >= 0; bit_cnt-- )
    {
        error_flag |= rng2_i2c_write_bit ( ctx, ( ( data_in >> bit_cnt ) & 1 ) );
    }

    error_flag |= rng2_i2c_read_bit ( ctx, &nack );

    if ( send_stop ) 
    {
        error_flag |= rng2_i2c_stop ( ctx );
    }
    
    if ( nack )
    {
        error_flag = RNG2_ERROR;
    }
    
    return error_flag;
}

static err_t rng2_i2c_read_byte ( rng2_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop )
{
    err_t error_flag = RNG2_OK;
    uint8_t rd_byte = 0;
    uint8_t rd_bit = 0;
    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
    {
        error_flag |= rng2_i2c_read_bit ( ctx, &rd_bit );
        rd_byte = ( rd_byte << 1 ) | rd_bit;
    }

    error_flag |= rng2_i2c_write_bit ( ctx, nack );

    if ( send_stop ) 
    {
        error_flag |= rng2_i2c_stop ( ctx );
    }
    
    if ( RNG2_OK == error_flag )
    {
        *data_out = rd_byte;
    }

    return error_flag;
}

static uint16_t rng2_reflect_bits( uint16_t data_in, uint8_t len )
{
    uint16_t data_out = 0;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_out |= ( ( data_in >> cnt ) & 1 ) << ( len - cnt - 1 );
    }
    return data_out;
}

static uint16_t rng2_calculate_crc16( uint8_t *data_buf, uint16_t len )
{
    uint16_t crc16 = 0x0000;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( rng2_reflect_bits( data_buf[ cnt ], 8 ) << 8 );
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x8005;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return crc16;
}

// ------------------------------------------------------------------------- END
