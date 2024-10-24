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
 * @file captouch4.c
 * @brief Cap Touch 4 Click Driver.
 */

#include "captouch4.h"

/**
 * @brief Cap Touch 4 read scl function.
 * @details This function returns the current level of SCL line, 0 or 1.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return Logic level of SCL line.
 * @note None.
 */
static uint8_t captouch4_read_scl ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 set scl function.
 * @details This function sets the SCL pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void captouch4_set_scl ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 clear scl function.
 * @details This function drives the SCL pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void captouch4_clear_scl ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 read sda function.
 * @details This function returns the current level of SDA line, 0 or 1.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return Logic level of SDA line.
 * @note None.
 */
static uint8_t captouch4_read_sda ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 set sda function.
 * @details This function sets the SDA pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void captouch4_set_sda ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 clear sda function.
 * @details This function drives the SDA pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void captouch4_clear_sda ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 i2c stop function.
 * @details This function sends an I2C stop condition signal.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t captouch4_i2c_stop ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 i2c start function.
 * @details This function sends an I2C start condition signal.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t captouch4_i2c_start ( captouch4_t *ctx );

/**
 * @brief Cap Touch 4 i2c write bit function.
 * @details This function writes a LSB bit of data_in to the I2C bus.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[in] data_in : A LSB of this byte is written to the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t captouch4_i2c_write_bit ( captouch4_t *ctx, uint8_t data_in );

/**
 * @brief Cap Touch 4 i2c read bit function.
 * @details This function reads a bit from the I2C bus and stores it into the LSB of data_out.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[out] data_out : A LSB of this byte is read from the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t captouch4_i2c_read_bit ( captouch4_t *ctx, uint8_t *data_out );

/**
 * @brief Cap Touch 4 i2c write byte function.
 * @details This function write a data_in byte to the I2C bus. Also sends a start/stop condition
 * if a send_start/send_stop is true.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[in] data_in : Data byte to be written.
 * @param[in] send_start : 0 - exclude sending start signal, != 0 - sends a start signal in the beginning.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - ACKed by the target device,
 *         @li @c -1 - Error - timeout, lost arbitration, busy line, or NACK received.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t captouch4_i2c_write_byte ( captouch4_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop );

/**
 * @brief Cap Touch 4 i2c read byte function.
 * @details This function reads a byte from I2C bus and stores it into data_out. Sends NACK if nack is true,
 * otherwise responds with ACK. Also sends a stop condition if send_stop is true.
 * @param[in] ctx : Click context object.
 * See #captouch4_t object definition for detailed explanation.
 * @param[out] data_out : Data byte read from the bus.
 * @param[in] nack : 0 - responds with ACK signal, != 0 - responds with a NACK signal.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout, lost arbitration, or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t captouch4_i2c_read_byte ( captouch4_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop );

void captouch4_cfg_setup ( captouch4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->i2c_address = CAPTOUCH4_DEVICE_ADDRESS;
}

err_t captouch4_init ( captouch4_t *ctx, captouch4_cfg_t *cfg ) 
{
    digital_out_init ( &ctx->en, cfg->en );
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
    
    ctx->slave_address = cfg->i2c_address;
    
    ctx->scl = cfg->scl;
    ctx->sda = cfg->sda;
    ctx->i2c_started = false;

    captouch4_set_scl ( ctx );
    captouch4_set_sda ( ctx );
    Delay_100ms ( );
    digital_out_low ( &ctx->en );
    Delay_1sec ( );

    return I2C_MASTER_SUCCESS;
}

err_t captouch4_default_cfg ( captouch4_t *ctx ) 
{
    err_t error_flag = CAPTOUCH4_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t cnt = 0;
    
    captouch4_enable_device ( ctx );
    Delay_5ms ( );
    for ( cnt = 0; cnt < 10; cnt++ )
    {
        // Check if device has entered test mode, up to 10 times
        // Needs to be done in 2-17 ms window after power up
        error_flag = CAPTOUCH4_OK;
        error_flag |= captouch4_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
        error_flag |= captouch4_i2c_write_byte ( ctx, CAPTOUCH4_REG_TEST_MODE, false, false );
        error_flag |= captouch4_i2c_write_byte ( ctx, ( ( ctx->slave_address << 1 ) | 1 ), true, false );
        error_flag |= captouch4_i2c_read_byte ( ctx, &data_buf[ 0 ], true, false );
        if ( CAPTOUCH4_OK == error_flag )
        {
            if ( CAPTOUCH4_TEST_MODE_OK == data_buf[ 0 ] )
            {
                // Enable I2C interface in test mode
                error_flag = captouch4_write_reg ( ctx, CAPTOUCH4_REG_OTP_BANK_2, CAPTOUCH4_OTP_BANK_2_OUT_I2C_NO_WKP );
                break;
            }
            else
            {
                error_flag = CAPTOUCH4_ERROR;
            }
        }
        Delay_1ms ( );
    }
    Delay_1sec ( );
    if ( CAPTOUCH4_OK == error_flag )
    {
        error_flag |= captouch4_check_communication ( ctx );
    }
    if ( CAPTOUCH4_OK == error_flag )
    {
        error_flag |= captouch4_write_reg ( ctx, CAPTOUCH4_REG_SYSFLAGS0, CAPTOUCH4_SYSFLAGS0_CLEAR );
    }
    return error_flag;
}

err_t captouch4_write_reg ( captouch4_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = CAPTOUCH4_OK;
    error_flag |= captouch4_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= captouch4_i2c_write_byte ( ctx, reg, false, false );
    error_flag |= captouch4_i2c_write_byte ( ctx, data_in, false, true );
    Delay_10ms ( );
    return error_flag;
}

err_t captouch4_read_reg ( captouch4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = CAPTOUCH4_OK;
    error_flag |= captouch4_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= captouch4_i2c_write_byte ( ctx, reg, false, false );
    error_flag |= captouch4_i2c_write_byte ( ctx, ( ( ctx->slave_address << 1 ) | 1 ), true, false );
    for ( uint8_t cnt = 1; cnt < len; cnt++ )
    {
        error_flag |= captouch4_i2c_read_byte ( ctx, &data_out[ cnt - 1 ], false, false );
    }
    error_flag |= captouch4_i2c_read_byte ( ctx, &data_out[ len - 1 ], true, true );
    Delay_10ms ( );
    return error_flag;
}

err_t captouch4_check_communication ( captouch4_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( CAPTOUCH4_OK == captouch4_read_reg ( ctx, CAPTOUCH4_REG_PRODUCT_NUM, data_buf, 2 ) )
    {
        if ( ( CAPTOUCH4_PRODUCT_NUMBER == data_buf[ 0 ] ) && 
             ( CAPTOUCH4_VERSION_NUMBER == data_buf[ 1 ] ) )
        {
            return CAPTOUCH4_OK;
        }
    }
    return CAPTOUCH4_ERROR;
}

void captouch4_enable_device ( captouch4_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void captouch4_disable_device ( captouch4_t *ctx )
{
    digital_out_low ( &ctx->en );
}

err_t captouch4_read_system_flags ( captouch4_t *ctx, uint8_t *sysflags )
{
    return captouch4_read_reg ( ctx, CAPTOUCH4_REG_SYSFLAGS0, sysflags, 1 );
}

err_t captouch4_read_movement ( captouch4_t *ctx, uint8_t *movement )
{
    return captouch4_read_reg ( ctx, CAPTOUCH4_REG_MOVEMENT_VALUE, movement, 1 );
}

err_t captouch4_read_cap_counts ( captouch4_t *ctx, uint16_t *cap_counts )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( CAPTOUCH4_OK == captouch4_read_reg ( ctx, CAPTOUCH4_REG_CS_H, data_buf, 2 ) ) && 
         ( NULL != cap_counts ) )
    {
        *cap_counts = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return CAPTOUCH4_OK;
    }
    return CAPTOUCH4_ERROR;
}

err_t captouch4_read_lta ( captouch4_t *ctx, uint16_t *lta )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( CAPTOUCH4_OK == captouch4_read_reg ( ctx, CAPTOUCH4_REG_LTA_H, data_buf, 2 ) ) && 
         ( NULL != lta ) )
    {
        *lta = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return CAPTOUCH4_OK;
    }
    return CAPTOUCH4_ERROR;
}

static uint8_t captouch4_read_scl ( captouch4_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
    return ( uint8_t ) ( 0 != digital_in_read ( &scl ) );
}

static void captouch4_set_scl ( captouch4_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
}

static void captouch4_clear_scl ( captouch4_t *ctx )
{
    digital_out_t scl;
    digital_out_init ( &scl, ctx->scl );
    digital_out_low ( &scl );
}

static uint8_t captouch4_read_sda ( captouch4_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
    return ( uint8_t ) ( 0 != digital_in_read ( &sda ) );
}

static void captouch4_set_sda ( captouch4_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
}

static void captouch4_clear_sda ( captouch4_t *ctx )
{
    digital_out_t sda;
    digital_out_init ( &sda, ctx->sda );
    digital_out_low ( &sda );
}

static err_t captouch4_i2c_start ( captouch4_t *ctx )
{
    uint32_t timeout_cnt = 0;
    if ( ctx->i2c_started ) 
    { 
        // If started, do a restart condition, set SDA
        captouch4_set_sda ( ctx );
        Delay_10us ( );
        captouch4_set_scl ( ctx );
        while ( 0 == captouch4_read_scl ( ctx ) ) 
        {   
            // Clock stretching
            if ( ++timeout_cnt > CAPTOUCH4_I2C_TIMEOUT )
            {
                return CAPTOUCH4_ERROR;
            }
        }
        // Repeated start setup time, minimum 4.7us
        Delay_10us ( );
    }

    if ( 0 == captouch4_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return CAPTOUCH4_ERROR;
    }

    // SCL is high, clear SDA
    captouch4_clear_sda ( ctx );
    Delay_10us ( );
    captouch4_clear_scl ( ctx );
    ctx->i2c_started = true;
    return CAPTOUCH4_OK;
}

static err_t captouch4_i2c_stop ( captouch4_t *ctx )
{
    uint32_t timeout_cnt = 0;
    // Clear SDA
    captouch4_clear_sda ( ctx );
    Delay_10us ( );

    captouch4_set_scl ( ctx );
    while ( 0 == captouch4_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > CAPTOUCH4_I2C_TIMEOUT )
        {
            return CAPTOUCH4_ERROR;
        }
    }

    // Stop bit setup time, minimum 4us
    Delay_10us ( );

    // SCL is high, set SDA
    captouch4_set_sda ( ctx );
    Delay_10us ( );

    if ( 0 == captouch4_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return CAPTOUCH4_ERROR;
    }
    ctx->i2c_started = false;
    return CAPTOUCH4_OK;
}

static err_t captouch4_i2c_write_bit ( captouch4_t *ctx, uint8_t data_in )
{
    uint32_t timeout_cnt = 0;
    if ( data_in ) 
    {
        captouch4_set_sda ( ctx );
    } 
    else 
    {
        captouch4_clear_sda ( ctx );
    }

    // SDA change propagation delay
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    captouch4_set_scl ( ctx );

    // Wait for SDA value to be read by target, minimum of 4us for standard mode
    Delay_10us ( );

    while ( 0 == captouch4_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > CAPTOUCH4_I2C_TIMEOUT )
        {
            return CAPTOUCH4_ERROR;
        }
    }

    // SCL is high, now data is valid
    // If SDA is high, check that nobody else is driving SDA
    if ( data_in && ( 0 == captouch4_read_sda ( ctx ) ) ) 
    {
        return CAPTOUCH4_ERROR;
    }

    // Clear the SCL to low in preparation for next change
    captouch4_clear_scl ( ctx );
    return CAPTOUCH4_OK;
}

static err_t captouch4_i2c_read_bit ( captouch4_t *ctx, uint8_t *data_out ) 
{
    uint32_t timeout_cnt = 0;
    // Let the target drive data
    captouch4_set_sda ( ctx );

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    captouch4_set_scl ( ctx );

    while ( 0 == captouch4_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > CAPTOUCH4_I2C_TIMEOUT )
        {
            return CAPTOUCH4_ERROR;
        }
    }

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // SCL is high, read out bit
    *data_out = captouch4_read_sda ( ctx );

    // Set SCL low in preparation for next operation
    captouch4_clear_scl ( ctx );

    return CAPTOUCH4_OK;
}

static err_t captouch4_i2c_write_byte ( captouch4_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop )
{
    err_t error_flag = CAPTOUCH4_OK;
    uint8_t nack = 0;

    if ( send_start ) 
    {
        error_flag |= captouch4_i2c_start ( ctx );
    }

    for ( int8_t bit_cnt = 7; bit_cnt >= 0; bit_cnt-- )
    {
        error_flag |= captouch4_i2c_write_bit ( ctx, ( ( data_in >> bit_cnt ) & 1 ) );
    }

    error_flag |= captouch4_i2c_read_bit ( ctx, &nack );

    if ( send_stop ) 
    {
        error_flag |= captouch4_i2c_stop ( ctx );
    }
    
    if ( nack )
    {
        error_flag = CAPTOUCH4_ERROR;
    }
    
    return error_flag;
}

static err_t captouch4_i2c_read_byte ( captouch4_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop )
{
    err_t error_flag = CAPTOUCH4_OK;
    uint8_t rd_byte = 0;
    uint8_t rd_bit = 0;
    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
    {
        error_flag |= captouch4_i2c_read_bit ( ctx, &rd_bit );
        rd_byte = ( rd_byte << 1 ) | rd_bit;
    }

    error_flag |= captouch4_i2c_write_bit ( ctx, nack );

    if ( send_stop ) 
    {
        error_flag |= captouch4_i2c_stop ( ctx );
    }
    
    if ( CAPTOUCH4_OK == error_flag )
    {
        *data_out = rd_byte;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
