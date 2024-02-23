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
 * @file magneto6.c
 * @brief Magneto 6 Click Driver.
 */

#include "magneto6.h"

/**
 * @brief Magneto 6 read scl function.
 * @details This function returns the current level of SCL line, 0 or 1.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return Logic level of SCL line.
 * @note None.
 */
static uint8_t magneto6_read_scl ( magneto6_t *ctx );

/**
 * @brief Magneto 6 set scl function.
 * @details This function sets the SCL pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void magneto6_set_scl ( magneto6_t *ctx );

/**
 * @brief Magneto 6 clear scl function.
 * @details This function drives the SCL pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void magneto6_clear_scl ( magneto6_t *ctx );

/**
 * @brief Magneto 6 read sda function.
 * @details This function returns the current level of SDA line, 0 or 1.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return Logic level of SDA line.
 * @note None.
 */
static uint8_t magneto6_read_sda ( magneto6_t *ctx );

/**
 * @brief Magneto 6 set sda function.
 * @details This function sets the SDA pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void magneto6_set_sda ( magneto6_t *ctx );

/**
 * @brief Magneto 6 clear sda function.
 * @details This function drives the SDA pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void magneto6_clear_sda ( magneto6_t *ctx );

/**
 * @brief Magneto 6 i2c stop function.
 * @details This function sends an I2C stop condition signal.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t magneto6_i2c_stop ( magneto6_t *ctx );

/**
 * @brief Magneto 6 i2c start function.
 * @details This function sends an I2C start condition signal.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t magneto6_i2c_start ( magneto6_t *ctx );

/**
 * @brief Magneto 6 i2c write bit function.
 * @details This function writes a LSB bit of data_in to the I2C bus.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[in] data_in : A LSB of this byte is written to the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t magneto6_i2c_write_bit ( magneto6_t *ctx, uint8_t data_in );

/**
 * @brief Magneto 6 i2c read bit function.
 * @details This function reads a bit from the I2C bus and stores it into the LSB of data_out.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[out] data_out : A LSB of this byte is read from the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t magneto6_i2c_read_bit ( magneto6_t *ctx, uint8_t *data_out );

/**
 * @brief Magneto 6 i2c write byte function.
 * @details This function write a data_in byte to the I2C bus. Also sends a start/stop condition
 * if a send_start/send_stop is true.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[in] data_in : Data byte to be written.
 * @param[in] send_start : 0 - exclude sending start signal, != 0 - sends a start signal in the beginning.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - ACKed by the target device,
 *         @li @c -1 - Error - timeout, lost arbitration, busy line, or NACK received.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t magneto6_i2c_write_byte ( magneto6_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop );

/**
 * @brief Magneto 6 i2c read byte function.
 * @details This function reads a byte from I2C bus and stores it into data_out. Sends NACK if nack is true,
 * otherwise responds with ACK. Also sends a stop condition if send_stop is true.
 * @param[in] ctx : Click context object.
 * See #magneto6_t object definition for detailed explanation.
 * @param[out] data_out : Data byte read from the bus.
 * @param[in] nack : 0 - responds with ACK signal, != 0 - responds with a NACK signal.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout, lost arbitration, or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t magneto6_i2c_read_byte ( magneto6_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop );

void magneto6_cfg_setup ( magneto6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ien = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_address = MAGNETO6_DEVICE_ADDRESS_0;
}

err_t magneto6_init ( magneto6_t *ctx, magneto6_cfg_t *cfg ) 
{
    ctx->slave_address = cfg->i2c_address;
    
    ctx->scl = cfg->scl;
    ctx->sda = cfg->sda;
    ctx->i2c_started = false;

    digital_out_init( &ctx->ien, cfg->ien );
    digital_out_low ( &ctx->ien );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    magneto6_set_scl ( ctx );
    magneto6_set_sda ( ctx );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t magneto6_default_cfg ( magneto6_t *ctx ) 
{
    err_t error_flag = MAGNETO6_OK;
    error_flag |= magneto6_write_reg ( ctx, MAGNETO6_REG_CONFIG, MAGNETO6_CONFIG_TRIGGER_MSB );
    error_flag |= magneto6_write_reg ( ctx, MAGNETO6_REG_MOD1, MAGNETO6_MOD1_INT_DISABLE );
    Delay_100ms ( );
    return error_flag;
}

err_t magneto6_write_reg ( magneto6_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = MAGNETO6_OK;
    error_flag |= magneto6_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= magneto6_i2c_write_byte ( ctx, reg, false, false );
    error_flag |= magneto6_i2c_write_byte ( ctx, data_in, false, true );
    return error_flag;
}

err_t magneto6_read_reg ( magneto6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = MAGNETO6_OK;
    error_flag |= magneto6_i2c_write_byte ( ctx, ( ( ctx->slave_address << 1 ) | 1 ), true, false );
    error_flag |= magneto6_i2c_write_byte ( ctx, reg, false, false );
    for ( uint8_t cnt = 1; cnt < len; cnt++ )
    {
        error_flag |= magneto6_i2c_read_byte ( ctx, &data_out[ cnt - 1 ], false, false );
    }
    error_flag |= magneto6_i2c_read_byte ( ctx, &data_out[ len - 1 ], true, true );
    return error_flag;
}

void magneto6_set_ien_pin ( magneto6_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ien, state );
}

uint8_t magneto6_get_int_pin ( magneto6_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t magneto6_read_data ( magneto6_t *ctx, magneto6_data_t *data_out )
{
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    err_t error_flag = magneto6_read_reg ( ctx, MAGNETO6_REG_MAGNETIC_X_MSB, data_buf, 6 );
    if ( ( MAGNETO6_OK == error_flag ) && ( NULL != data_out ) )
    {
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 0 ] );
        raw_data <<= 8;
        raw_data |= ( data_buf[ 4 ] & 0xF0 );
        raw_data >>= 4;
        data_out->x_data = raw_data * MAGNETO6_MAGNETIC_RES_MILLI_T;
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 1 ] );
        raw_data <<= 8;
        raw_data |= ( ( data_buf[ 4 ] & 0x0F ) << 4 );
        raw_data >>= 4;
        data_out->y_data = raw_data * MAGNETO6_MAGNETIC_RES_MILLI_T;
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 2 ] );
        raw_data <<= 8;
        raw_data |= ( ( data_buf[ 5 ] & 0x0F ) << 4 );
        raw_data >>= 4;
        data_out->z_data = raw_data * MAGNETO6_MAGNETIC_RES_MILLI_T;
        raw_data = ( int16_t ) ( ( int8_t ) data_buf[ 3 ] );
        raw_data <<= 8;
        raw_data |= ( data_buf[ 5 ] & 0xC0 );
        raw_data >>= 4;
        data_out->temperature = ( raw_data - MAGNETO6_TEMP_25_DIGIT ) * MAGNETO6_TEMP_RES + MAGNETO6_TEMP_25;
    }
    return error_flag;
}

static uint8_t magneto6_read_scl ( magneto6_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
    return ( uint8_t ) ( 0 != digital_in_read ( &scl ) );
}

static void magneto6_set_scl ( magneto6_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
}

static void magneto6_clear_scl ( magneto6_t *ctx )
{
    digital_out_t scl;
    digital_out_init ( &scl, ctx->scl );
    digital_out_low ( &scl );
}

static uint8_t magneto6_read_sda ( magneto6_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
    return ( uint8_t ) ( 0 != digital_in_read ( &sda ) );
}

static void magneto6_set_sda ( magneto6_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
}

static void magneto6_clear_sda ( magneto6_t *ctx )
{
    digital_out_t sda;
    digital_out_init ( &sda, ctx->sda );
    digital_out_low ( &sda );
}

static err_t magneto6_i2c_start ( magneto6_t *ctx )
{
    uint32_t timeout_cnt = 0;
    if ( ctx->i2c_started ) 
    { 
        // If started, do a restart condition, set SDA
        magneto6_set_sda ( ctx );
        Delay_10us ( );
        magneto6_set_scl ( ctx );
        while ( 0 == magneto6_read_scl ( ctx ) ) 
        {   
            // Clock stretching
            if ( ++timeout_cnt > MAGNETO6_I2C_TIMEOUT )
            {
                return MAGNETO6_ERROR;
            }
        }
        // Repeated start setup time, minimum 4.7us
        Delay_10us ( );
    }

    if ( 0 == magneto6_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return MAGNETO6_ERROR;
    }

    // SCL is high, clear SDA
    magneto6_clear_sda ( ctx );
    Delay_10us ( );
    magneto6_clear_scl ( ctx );
    ctx->i2c_started = true;
    return MAGNETO6_OK;
}

static err_t magneto6_i2c_stop ( magneto6_t *ctx )
{
    uint32_t timeout_cnt = 0;
    // Clear SDA
    magneto6_clear_sda ( ctx );
    Delay_10us ( );

    magneto6_set_scl ( ctx );
    while ( 0 == magneto6_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > MAGNETO6_I2C_TIMEOUT )
        {
            return MAGNETO6_ERROR;
        }
    }

    // Stop bit setup time, minimum 4us
    Delay_10us ( );

    // SCL is high, set SDA
    magneto6_set_sda ( ctx );
    Delay_10us ( );

    if ( 0 == magneto6_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return MAGNETO6_ERROR;
    }
    ctx->i2c_started = false;
    return MAGNETO6_OK;
}

static err_t magneto6_i2c_write_bit ( magneto6_t *ctx, uint8_t data_in )
{
    uint32_t timeout_cnt = 0;
    if ( data_in ) 
    {
        magneto6_set_sda ( ctx );
    } 
    else 
    {
        magneto6_clear_sda ( ctx );
    }

    // SDA change propagation delay
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    magneto6_set_scl ( ctx );

    // Wait for SDA value to be read by target, minimum of 4us for standard mode
    Delay_10us ( );

    while ( 0 == magneto6_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > MAGNETO6_I2C_TIMEOUT )
        {
            return MAGNETO6_ERROR;
        }
    }

    // SCL is high, now data is valid
    // If SDA is high, check that nobody else is driving SDA
    if ( data_in && ( 0 == magneto6_read_sda ( ctx ) ) ) 
    {
        return MAGNETO6_ERROR;
    }

    // Clear the SCL to low in preparation for next change
    magneto6_clear_scl ( ctx );
    return MAGNETO6_OK;
}

static err_t magneto6_i2c_read_bit ( magneto6_t *ctx, uint8_t *data_out ) 
{
    uint32_t timeout_cnt = 0;
    // Let the target drive data
    magneto6_set_sda ( ctx );

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    magneto6_set_scl ( ctx );

    while ( 0 == magneto6_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > MAGNETO6_I2C_TIMEOUT )
        {
            return MAGNETO6_ERROR;
        }
    }

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // SCL is high, read out bit
    *data_out = magneto6_read_sda ( ctx );

    // Set SCL low in preparation for next operation
    magneto6_clear_scl ( ctx );

    return MAGNETO6_OK;
}

static err_t magneto6_i2c_write_byte ( magneto6_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop )
{
    err_t error_flag = MAGNETO6_OK;
    uint8_t nack = 0;

    if ( send_start ) 
    {
        error_flag |= magneto6_i2c_start ( ctx );
    }

    for ( int8_t bit_cnt = 7; bit_cnt >= 0; bit_cnt-- )
    {
        error_flag |= magneto6_i2c_write_bit ( ctx, ( ( data_in >> bit_cnt ) & 1 ) );
    }

    error_flag |= magneto6_i2c_read_bit ( ctx, &nack );

    if ( send_stop ) 
    {
        error_flag |= magneto6_i2c_stop ( ctx );
    }
    
    if ( nack )
    {
        error_flag = MAGNETO6_ERROR;
    }
    
    return error_flag;
}

static err_t magneto6_i2c_read_byte ( magneto6_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop )
{
    err_t error_flag = MAGNETO6_OK;
    uint8_t rd_byte = 0;
    uint8_t rd_bit = 0;
    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
    {
        error_flag |= magneto6_i2c_read_bit ( ctx, &rd_bit );
        rd_byte = ( rd_byte << 1 ) | rd_bit;
    }

    error_flag |= magneto6_i2c_write_bit ( ctx, nack );

    if ( send_stop ) 
    {
        error_flag |= magneto6_i2c_stop ( ctx );
    }
    
    if ( MAGNETO6_OK == error_flag )
    {
        *data_out = rd_byte;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
