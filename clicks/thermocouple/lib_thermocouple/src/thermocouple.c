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
 * @file thermocouple.c
 * @brief Thermocouple Click Driver.
 */

#include "thermocouple.h"

/**
 * @brief Thermocouple read scl function.
 * @details This function returns the current level of SCL line, 0 or 1.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return Logic level of SCL line.
 * @note None.
 */
static uint8_t thermocouple_read_scl ( thermocouple_t *ctx );

/**
 * @brief Thermocouple set scl function.
 * @details This function sets the SCL pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void thermocouple_set_scl ( thermocouple_t *ctx );

/**
 * @brief Thermocouple clear scl function.
 * @details This function drives the SCL pin to low logic state.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void thermocouple_clear_scl ( thermocouple_t *ctx );

/**
 * @brief Thermocouple read sda function.
 * @details This function returns the current level of SDA line, 0 or 1.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return Logic level of SDA line.
 * @note None.
 */
static uint8_t thermocouple_read_sda ( thermocouple_t *ctx );

/**
 * @brief Thermocouple set sda function.
 * @details This function sets the SDA pin high by setting it as input (high-impedance),
 * pull-up resistor will do the rest.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void thermocouple_set_sda ( thermocouple_t *ctx );

/**
 * @brief Thermocouple clear sda function.
 * @details This function drives the SDA pin to low logic state.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void thermocouple_clear_sda ( thermocouple_t *ctx );

/**
 * @brief Thermocouple i2c stop function.
 * @details This function sends an I2C stop condition signal.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t thermocouple_i2c_stop ( thermocouple_t *ctx );

/**
 * @brief Thermocouple i2c start function.
 * @details This function sends an I2C start condition signal.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or lost arbitration.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t thermocouple_i2c_start ( thermocouple_t *ctx );

/**
 * @brief Thermocouple i2c write bit function.
 * @details This function writes a LSB bit of data_in to the I2C bus.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] data_in : A LSB of this byte is written to the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t thermocouple_i2c_write_bit ( thermocouple_t *ctx, uint8_t data_in );

/**
 * @brief Thermocouple i2c read bit function.
 * @details This function reads a bit from the I2C bus and stores it into the LSB of data_out.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[out] data_out : A LSB of this byte is read from the bus.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t thermocouple_i2c_read_bit ( thermocouple_t *ctx, uint8_t *data_out );

/**
 * @brief Thermocouple i2c write byte function.
 * @details This function write a data_in byte to the I2C bus. Also sends a start/stop condition
 * if a send_start/send_stop is true.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[in] data_in : Data byte to be written.
 * @param[in] send_start : 0 - exclude sending start signal, != 0 - sends a start signal in the beginning.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - ACKed by the target device,
 *         @li @c -1 - Error - timeout, lost arbitration, busy line, or NACK received.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t thermocouple_i2c_write_byte ( thermocouple_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop );

/**
 * @brief Thermocouple i2c read byte function.
 * @details This function reads a byte from I2C bus and stores it into data_out. Sends NACK if nack is true,
 * otherwise responds with ACK. Also sends a stop condition if send_stop is true.
 * @param[in] ctx : Context object.
 * See #thermocouple_t object definition for detailed explanation.
 * @param[out] data_out : Data byte read from the bus.
 * @param[in] nack : 0 - responds with ACK signal, != 0 - responds with a NACK signal.
 * @param[in] send_stop : 0 - exclude sending stop signal, != 0 - sends a stop signal in the end.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - timeout, lost arbitration, or busy line.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t thermocouple_i2c_read_byte ( thermocouple_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop );

void thermocouple_cfg_setup ( thermocouple_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->oca = HAL_PIN_NC;
    cfg->sca = HAL_PIN_NC;

    cfg->i2c_address = THERMOCOUPLE_DEVICE_ADDRESS_0;
}

err_t thermocouple_init ( thermocouple_t *ctx, thermocouple_cfg_t *cfg ) 
{
    err_t error_flag = THERMOCOUPLE_OK;
    ctx->slave_address = cfg->i2c_address;
    
    ctx->scl = cfg->scl;
    ctx->sda = cfg->sda;
    ctx->i2c_started = false;

    error_flag |= digital_in_init( &ctx->oca, cfg->oca );
    error_flag |= digital_in_init( &ctx->sca, cfg->sca );

    thermocouple_set_scl ( ctx );
    thermocouple_set_sda ( ctx );
    Delay_10ms ( );

    uint32_t timeout = 0;
    while ( !thermocouple_read_sda ( ctx ) )
    {
        thermocouple_clear_scl ( ctx );
        Delay_50us ( );
        thermocouple_set_scl ( ctx );
        Delay_50us ( );
        if ( ++timeout > THERMOCOUPLE_I2C_RELEASE_TIMEOUT )
        {
            error_flag = THERMOCOUPLE_ERROR;
            break;
        }
    }
    Delay_10ms ( );

    return error_flag;
}

err_t thermocouple_default_cfg ( thermocouple_t *ctx ) 
{
    err_t error_flag = THERMOCOUPLE_OK;

    if ( THERMOCOUPLE_OK != thermocouple_check_com ( ctx ) )
    {
        return THERMOCOUPLE_ERROR;
    }

    error_flag = thermocouple_set_device_cfg( ctx, THERMOCOUPLE_DEVICE_CONFIG_ADC_RES_18BIT, 
                                                   THERMOCOUPLE_DEVICE_CONFIG_BURST_1_SAMPLE, 
                                                   THERMOCOUPLE_DEVICE_CONFIG_MODE_NORMAL );
    Delay_10ms ( );

    return error_flag;
}

err_t thermocouple_write_reg ( thermocouple_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return thermocouple_write_regs( ctx, reg, &data_in, 1 );
}

err_t thermocouple_write_regs ( thermocouple_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = THERMOCOUPLE_OK;
    error_flag |= thermocouple_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= thermocouple_i2c_write_byte ( ctx, reg, false, false );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        if ( len == ( cnt + 1 ) )
        {
            error_flag |= thermocouple_i2c_write_byte ( ctx, data_in[ cnt ], false, true );
        }
        else
        {
            error_flag |= thermocouple_i2c_write_byte ( ctx, data_in[ cnt ], false, false );
        }
    }
    return error_flag;
}

err_t thermocouple_read_reg ( thermocouple_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return thermocouple_read_regs( ctx, reg, data_out, 1 );
}

err_t thermocouple_read_reg_word ( thermocouple_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    err_t error_flag = THERMOCOUPLE_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag = thermocouple_read_regs( ctx, reg, data_buf, 2 );
    if ( ( THERMOCOUPLE_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t thermocouple_read_regs ( thermocouple_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = THERMOCOUPLE_OK;
    error_flag |= thermocouple_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ), true, false );
    error_flag |= thermocouple_i2c_write_byte ( ctx, reg, false, true );
    error_flag |= thermocouple_i2c_write_byte ( ctx, ( ctx->slave_address << 1 ) | 0x01, true, false );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        if ( len == ( cnt + 1 ) )
        {
            error_flag |= thermocouple_i2c_read_byte ( ctx, &data_out[ cnt ], true, true );
        }
        else
        {
            error_flag |= thermocouple_i2c_read_byte ( ctx, &data_out[ cnt ], false, false );
        }
    }
    return error_flag;
}

uint8_t thermocouple_get_oca_pin ( thermocouple_t *ctx )
{
    return digital_in_read ( &ctx->oca );
}

uint8_t thermocouple_get_sca_pin ( thermocouple_t *ctx )
{
    return digital_in_read ( &ctx->sca );
}

err_t thermocouple_check_com ( thermocouple_t *ctx )
{
    uint16_t device_id = 0;
    if ( THERMOCOUPLE_OK == thermocouple_read_reg_word ( ctx, THERMOCOUPLE_REG_DEVICE_ID_REVISION, &device_id ) )
    {
        if ( THERMOCOUPLE_DEVICE_ID_MCP9604 == ( device_id & THERMOCOUPLE_DEVICE_ID_MASK ) )
        {
            return THERMOCOUPLE_OK;
        }
    }
    return THERMOCOUPLE_ERROR;
}

err_t thermocouple_set_sensor_cfg ( thermocouple_t *ctx, uint8_t channel, uint8_t type, uint8_t filter )
{
    err_t error_flag = THERMOCOUPLE_OK;
    uint8_t cfg_data = 0;

    cfg_data = ( ( type << 4 ) & THERMOCOUPLE_SENSOR_CONFIG_TYPE_MASK ) |
               ( filter & THERMOCOUPLE_SENSOR_CONFIG_FILTER_MASK );

    switch ( channel )
    {
        case THERMOCOUPLE_CHANNEL_1:
        {
            cfg_data |= THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_0;
            break;
        }
        case THERMOCOUPLE_CHANNEL_2:
        {
            cfg_data |= THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_1;
            break;
        }
        case THERMOCOUPLE_CHANNEL_3:
        {
            cfg_data |= THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_2;
            break;
        }
        case THERMOCOUPLE_CHANNEL_4:
        {
            cfg_data |= THERMOCOUPLE_SENSOR_CONFIG_CHANNEL_3;
            break;
        }
        default:
        {
            error_flag = THERMOCOUPLE_ERROR;
            break;
        }
    }

    if ( THERMOCOUPLE_OK == error_flag )
    {
        error_flag = thermocouple_write_reg( ctx, THERMOCOUPLE_REG_SENSOR_CONFIG, cfg_data );
    }

    return error_flag;
}

err_t thermocouple_set_device_cfg ( thermocouple_t *ctx, uint8_t adc_res, uint8_t burst, uint8_t mode )
{
    uint8_t cfg_data = 0;

    cfg_data = ( adc_res & THERMOCOUPLE_DEVICE_CONFIG_ADC_RES_MASK ) |
               ( burst & THERMOCOUPLE_DEVICE_CONFIG_BURST_SAMPLES_MASK ) |
               ( mode & THERMOCOUPLE_DEVICE_CONFIG_MODE_MASK );

    return thermocouple_write_reg( ctx, THERMOCOUPLE_REG_DEVICE_CONFIG, cfg_data );
}

err_t thermocouple_get_status ( thermocouple_t *ctx, uint8_t *status )
{
    return thermocouple_read_reg( ctx, THERMOCOUPLE_REG_STATUS, status );
}

err_t thermocouple_clear_status ( thermocouple_t *ctx )
{
    return thermocouple_write_reg( ctx, THERMOCOUPLE_REG_STATUS, 0 );
}

err_t thermocouple_get_hot_junction ( thermocouple_t *ctx, float *temp )
{
    err_t error_flag = THERMOCOUPLE_OK;
    uint16_t raw_data = 0;

    if ( THERMOCOUPLE_OK == error_flag )
    {
        error_flag = thermocouple_read_reg_word( ctx, THERMOCOUPLE_REG_HOT_JUNCTION_TEMP, &raw_data );
    }

    if ( THERMOCOUPLE_OK == error_flag )
    {
        *temp = ( ( int16_t ) raw_data ) / 16.0;
    }

    return error_flag;
}

err_t thermocouple_get_cold_junction ( thermocouple_t *ctx, float *temp )
{
    err_t error_flag = THERMOCOUPLE_OK;
    uint16_t raw_data = 0;

    if ( THERMOCOUPLE_OK == error_flag )
    {
        error_flag = thermocouple_read_reg_word( ctx, THERMOCOUPLE_REG_COLD_JUNCTION_TEMP, &raw_data );
    }

    if ( THERMOCOUPLE_OK == error_flag )
    {
        *temp = ( ( int16_t ) raw_data ) / 16.0;
    }

    return error_flag;
}

err_t thermocouple_get_delta_temp ( thermocouple_t *ctx, float *temp )
{
    err_t error_flag = THERMOCOUPLE_OK;
    uint16_t raw_data = 0;

    if ( THERMOCOUPLE_OK == error_flag )
    {
        error_flag = thermocouple_read_reg_word( ctx, THERMOCOUPLE_REG_JUNCTION_TEMP_DELTA, &raw_data );
    }

    if ( THERMOCOUPLE_OK == error_flag )
    {
        *temp = ( ( int16_t ) raw_data ) / 16.0;
    }

    return error_flag;
}

static uint8_t thermocouple_read_scl ( thermocouple_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
    return ( uint8_t ) ( 0 != digital_in_read ( &scl ) );
}

static void thermocouple_set_scl ( thermocouple_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
}

static void thermocouple_clear_scl ( thermocouple_t *ctx )
{
    digital_out_t scl;
    digital_out_init ( &scl, ctx->scl );
    digital_out_low ( &scl );
}

static uint8_t thermocouple_read_sda ( thermocouple_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
    return ( uint8_t ) ( 0 != digital_in_read ( &sda ) );
}

static void thermocouple_set_sda ( thermocouple_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
}

static void thermocouple_clear_sda ( thermocouple_t *ctx )
{
    digital_out_t sda;
    digital_out_init ( &sda, ctx->sda );
    digital_out_low ( &sda );
}

static err_t thermocouple_i2c_start ( thermocouple_t *ctx )
{
    uint32_t timeout_cnt = 0;
    if ( ctx->i2c_started ) 
    { 
        // If started, do a restart condition, set SDA
        thermocouple_set_sda ( ctx );
        Delay_10us ( );
        thermocouple_set_scl ( ctx );
        while ( 0 == thermocouple_read_scl ( ctx ) ) 
        {   
            // Clock stretching
            if ( ++timeout_cnt > THERMOCOUPLE_I2C_TIMEOUT )
            {
                return THERMOCOUPLE_ERROR;
            }
        }
        // Repeated start setup time, minimum 4.7us
        Delay_10us ( );
    }

    if ( 0 == thermocouple_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return THERMOCOUPLE_ERROR;
    }

    // SCL is high, clear SDA
    thermocouple_clear_sda ( ctx );
    Delay_10us ( );
    thermocouple_clear_scl ( ctx );
    ctx->i2c_started = true;
    return THERMOCOUPLE_OK;
}

static err_t thermocouple_i2c_stop ( thermocouple_t *ctx )
{
    uint32_t timeout_cnt = 0;
    // Clear SDA
    thermocouple_clear_sda ( ctx );
    Delay_10us ( );

    thermocouple_set_scl ( ctx );
    while ( 0 == thermocouple_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > THERMOCOUPLE_I2C_TIMEOUT )
        {
            return THERMOCOUPLE_ERROR;
        }
    }

    // Stop bit setup time, minimum 4us
    Delay_10us ( );

    // SCL is high, set SDA
    thermocouple_set_sda ( ctx );
    Delay_10us ( );

    if ( 0 == thermocouple_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return THERMOCOUPLE_ERROR;
    }
    ctx->i2c_started = false;
    return THERMOCOUPLE_OK;
}

static err_t thermocouple_i2c_write_bit ( thermocouple_t *ctx, uint8_t data_in )
{
    uint32_t timeout_cnt = 0;
    if ( data_in ) 
    {
        thermocouple_set_sda ( ctx );
    } 
    else 
    {
        thermocouple_clear_sda ( ctx );
    }

    // SDA change propagation delay
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    thermocouple_set_scl ( ctx );

    // Wait for SDA value to be read by target, minimum of 4us for standard mode
    Delay_10us ( );

    while ( 0 == thermocouple_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > THERMOCOUPLE_I2C_TIMEOUT )
        {
            return THERMOCOUPLE_ERROR;
        }
    }

    // SCL is high, now data is valid
    // If SDA is high, check that nobody else is driving SDA
    if ( data_in && ( 0 == thermocouple_read_sda ( ctx ) ) ) 
    {
        return THERMOCOUPLE_ERROR;
    }

    // Clear the SCL to low in preparation for next change
    thermocouple_clear_scl ( ctx );
    return THERMOCOUPLE_OK;
}

static err_t thermocouple_i2c_read_bit ( thermocouple_t *ctx, uint8_t *data_out ) 
{
    uint32_t timeout_cnt = 0;
    // Let the target drive data
    thermocouple_set_sda ( ctx );

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    thermocouple_set_scl ( ctx );

    while ( 0 == thermocouple_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > THERMOCOUPLE_I2C_TIMEOUT )
        {
            return THERMOCOUPLE_ERROR;
        }
    }

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // SCL is high, read out bit
    *data_out = thermocouple_read_sda ( ctx );

    // Set SCL low in preparation for next operation
    thermocouple_clear_scl ( ctx );

    return THERMOCOUPLE_OK;
}

static err_t thermocouple_i2c_write_byte ( thermocouple_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop )
{
    err_t error_flag = THERMOCOUPLE_OK;
    uint8_t nack = 0;

    if ( send_start ) 
    {
        error_flag |= thermocouple_i2c_start ( ctx );
    }

    for ( int8_t bit_cnt = 7; bit_cnt >= 0; bit_cnt-- )
    {
        error_flag |= thermocouple_i2c_write_bit ( ctx, ( ( data_in >> bit_cnt ) & 1 ) );
    }

    error_flag |= thermocouple_i2c_read_bit ( ctx, &nack );

    if ( send_stop ) 
    {
        error_flag |= thermocouple_i2c_stop ( ctx );
    }
    
    if ( nack )
    {
        error_flag = THERMOCOUPLE_ERROR;
    }
    
    return error_flag;
}

static err_t thermocouple_i2c_read_byte ( thermocouple_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop )
{
    err_t error_flag = THERMOCOUPLE_OK;
    uint8_t rd_byte = 0;
    uint8_t rd_bit = 0;
    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
    {
        error_flag |= thermocouple_i2c_read_bit ( ctx, &rd_bit );
        rd_byte = ( rd_byte << 1 ) | rd_bit;
    }

    error_flag |= thermocouple_i2c_write_bit ( ctx, nack );

    if ( send_stop ) 
    {
        error_flag |= thermocouple_i2c_stop ( ctx );
    }
    
    if ( THERMOCOUPLE_OK == error_flag )
    {
        *data_out = rd_byte;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
