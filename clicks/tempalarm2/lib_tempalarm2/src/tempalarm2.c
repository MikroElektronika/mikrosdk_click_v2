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
 * @file tempalarm2.c
 * @brief Temp Alarm 2 Click Driver.
 */

#include "tempalarm2.h"

/**
 * @brief Temp Alarm 2 set remote limit function.
 * @details This function converts a float temperature value to the
 * 12-bit unsigned register format and writes it to the specified
 * high and low byte limit registers.
 * @param[in] ctx : Click context object.
 * See #tempalarm2_t object definition for detailed explanation.
 * @param[in] reg_high_w : Write address of the high byte limit register.
 * @param[in] reg_low : Address of the low byte limit register (same for read/write).
 * @param[in] temperature : Temperature limit in degrees Celsius (0.0625 degC resolution).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t tempalarm2_set_remote_limit ( tempalarm2_t *ctx, uint8_t reg_high_w, uint8_t reg_low, float temperature );

void tempalarm2_cfg_setup ( tempalarm2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPALARM2_DEVICE_ADDRESS;
}

err_t tempalarm2_init ( tempalarm2_t *ctx, tempalarm2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alt, cfg->alt );

    return I2C_MASTER_SUCCESS;
}

err_t tempalarm2_default_cfg ( tempalarm2_t *ctx ) 
{
    err_t error_flag = TEMPALARM2_OK;
    uint8_t mfr_id = 0;
    uint8_t dev_id = 0;

    error_flag |= tempalarm2_sw_reset( ctx );

    /* Verify device identity by reading the Manufacturer Identification Register (0xFE)
     * and Device ID Register (0xFF).
     * Expected values: Manufacturer ID = 0x55, Device ID = 0x13 (TMP411DB variant). */
    error_flag |= tempalarm2_read_reg( ctx, TEMPALARM2_REG_MANUFACTURER_ID, &mfr_id );
    error_flag |= tempalarm2_read_reg( ctx, TEMPALARM2_REG_DEVICE_ID, &dev_id );

    if ( ( TEMPALARM2_MANUFACTURER_ID != mfr_id ) || ( TEMPALARM2_DEVICE_ID != dev_id ) )
    {
        return TEMPALARM2_ERROR;
    }

    /* Configuration register (write to 0x09):
     *    bit[7] = 0 -> ALERT enabled
     *    bit[6] = 0 -> Device converts continuously at the rate set in conversion rate register
     *    bit[5] = 0 -> Pin 6 configured as ALERT interrupt output
     *    bit[2] = 0 -> Standard measurement range: 0 degC to 127 degC */
    error_flag |= tempalarm2_write_reg( ctx, TEMPALARM2_REG_CONFIGURATION_W,
                                             TEMPALARM2_CFG_CONTINUOUS_MODE |
                                             TEMPALARM2_CFG_ALERT_MODE      |
                                             TEMPALARM2_CFG_STANDARD_RANGE );

    /* Conversion rate register (write to 0x0A): 0x04 -> 1 conversion per second. */
    error_flag |= tempalarm2_write_reg( ctx, TEMPALARM2_REG_CONV_RATE_W,
                                             TEMPALARM2_CONV_RATE_1_CPS );

    /* Resolution register (0x1A): 0x1F -> 12-bit local channel resolution (0.0625 degC).
     *    bit[7:5] = 000 -> reserved, must be 0
     *    bit[4:2] = 111 -> reserved, must be 1
     *    bit[1:0] = 11 -> 12-bit local channel resolution (0.0625 degC)
     * Remote channel resolution is always 12-bit and is unaffected by this register. */
    error_flag |= tempalarm2_write_reg( ctx, TEMPALARM2_REG_RESOLUTION,
                                             TEMPALARM2_RESOLUTION_12BIT );

    /* THERM hysteresis register (0x21): 0x01 -> hysteresis = 1 degC.
     * Applies to both the local and remote THERM limits. */
    error_flag |= tempalarm2_write_reg( ctx, TEMPALARM2_REG_THERM_HYSTERESIS,
                                             TEMPALARM2_HYSTERESIS_1_DEG_C );

    /* Set THERM limits for both channels to 30 degC. */
    error_flag |= tempalarm2_set_therm_local( ctx, TEMPALARM2_THERM_LIMIT_30_DEG_C );
    error_flag |= tempalarm2_set_therm_remote( ctx, TEMPALARM2_THERM_LIMIT_30_DEG_C );

    /* Set ALERT high temperature limits for both channels to 28 degC. */
    error_flag |= tempalarm2_set_thigh_local( ctx, TEMPALARM2_LOCAL_HIGH_LIMIT_28_DEG_C );
    error_flag |= tempalarm2_set_thigh_remote( ctx, TEMPALARM2_REMOTE_HIGH_LIMIT_28_DEG_C );

    /* Set ALERT low temperature limits for both channels to 5 degC. */
    error_flag |= tempalarm2_set_tlow_local( ctx, TEMPALARM2_LOCAL_LOW_LIMIT_5_DEG_C );
    error_flag |= tempalarm2_set_tlow_remote( ctx, TEMPALARM2_REMOTE_LOW_LIMIT_5_DEG_C );

    Delay_100ms( );

    return error_flag;
}

err_t tempalarm2_write_reg ( tempalarm2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return tempalarm2_write_regs( ctx, reg, &data_in, 1 );
}

err_t tempalarm2_write_regs ( tempalarm2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t tempalarm2_read_reg ( tempalarm2_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return tempalarm2_read_regs( ctx, reg, data_out, 1 );
}

err_t tempalarm2_read_regs ( tempalarm2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t tempalarm2_get_alt_pin ( tempalarm2_t *ctx )
{
    return digital_in_read( &ctx->alt );
}

err_t tempalarm2_sw_reset ( tempalarm2_t *ctx )
{
    /* Writing any value to pointer register 0xFC triggers a software reset. */
    if ( TEMPALARM2_OK != tempalarm2_write_reg( ctx, TEMPALARM2_REG_SOFTWARE_RESET_W, TEMPALARM2_SW_RESET_DUMMY ) )
    {
        return TEMPALARM2_ERROR;
    }

    Delay_10ms( );
    
    return TEMPALARM2_OK;
}

err_t tempalarm2_read_local_temp ( tempalarm2_t *ctx, float *temperature )
{
    err_t error_flag = TEMPALARM2_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_u = 0;

    /* Local temperature is a 12-bit unsigned value with 0.0625 degC resolution
     * stored across two registers:
     *    Temp_Local_High (0x00) bits[7:0] -> Temp_data[11:4] -> integer part (1 degC resolution)
     *    Temp_Local_Low  (0x15) bits[7:4] -> Temp_data[3:0]  -> fractional part (0.0625 degC resolution)
     * The high byte must always be read first. This causes the device to lock the
     * low byte until it is read, guaranteeing both bytes are from the same ADC conversion. */
    error_flag |= tempalarm2_read_reg( ctx, TEMPALARM2_REG_TEMP_LOCAL_HIGH, &data_buf[ 0 ] );
    error_flag |= tempalarm2_read_reg( ctx, TEMPALARM2_REG_TEMP_LOCAL_LOW, &data_buf[ 1 ] );

    /* Assemble 12-bit unsigned raw value */
    raw_u = ( ( uint16_t ) data_buf[ 0 ] << 4 ) | ( data_buf[ 1 ] >> 4 );

    *temperature = ( float ) raw_u * TEMPALARM2_TEMP_LSB;

    return error_flag;
}

err_t tempalarm2_read_remote_temp ( tempalarm2_t *ctx, float *temperature )
{
    err_t error_flag = TEMPALARM2_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_u = 0;

    /* Remote temperature is a 12-bit unsigned value with 0.0625 degC resolution
     * stored across two registers:
     *    Temp_Remote_High (0x01) bits[7:0] -> Temp_data[11:4] -> integer part (1 degC resolution)
     *    Temp_Remote_Low  (0x10) bits[7:4] -> Temp_data[3:0]  -> fractional part (0.0625 degC resolution)
     * The high byte must always be read first. This causes the device to lock the
     * low byte until it is read, guaranteeing both bytes are from the same ADC conversion. */
    error_flag |= tempalarm2_read_reg( ctx, TEMPALARM2_REG_TEMP_REMOTE_HIGH, &data_buf[ 0 ] );
    error_flag |= tempalarm2_read_reg( ctx, TEMPALARM2_REG_TEMP_REMOTE_LOW, &data_buf[ 1 ] );

    /* Assemble 12-bit unsigned raw value */
    raw_u = ( ( uint16_t ) data_buf[ 0 ] << 4 ) | ( data_buf[ 1 ] >> 4 );

    *temperature = ( float ) raw_u * TEMPALARM2_TEMP_LSB;

    return error_flag;
}

err_t tempalarm2_set_thigh_local ( tempalarm2_t *ctx, uint8_t max_temperature )
{
    return tempalarm2_write_reg( ctx, TEMPALARM2_REG_THIGH_LIMIT_LOCAL_W, max_temperature );
}

err_t tempalarm2_set_tlow_local ( tempalarm2_t *ctx, uint8_t min_temperature )
{
    return tempalarm2_write_reg( ctx, TEMPALARM2_REG_TLOW_LIMIT_LOCAL_W, min_temperature );
}

err_t tempalarm2_set_thigh_remote ( tempalarm2_t *ctx, float max_temperature )
{
    return tempalarm2_set_remote_limit( ctx, TEMPALARM2_REG_THIGH_LIMIT_REMOTE_HIGH_W,
                                             TEMPALARM2_REG_THIGH_LIMIT_REMOTE_LOW,
                                             max_temperature );
}

err_t tempalarm2_set_tlow_remote ( tempalarm2_t *ctx, float min_temperature )
{
    return tempalarm2_set_remote_limit( ctx, TEMPALARM2_REG_TLOW_LIMIT_REMOTE_HIGH_W,
                                             TEMPALARM2_REG_TLOW_LIMIT_REMOTE_LOW,
                                             min_temperature );
}

err_t tempalarm2_set_therm_local ( tempalarm2_t *ctx, uint8_t max_temperature )
{
    return tempalarm2_write_reg( ctx, TEMPALARM2_REG_THERM_LIMIT_LOCAL, max_temperature );
}

err_t tempalarm2_set_therm_remote ( tempalarm2_t *ctx, uint8_t max_temperature )
{
    return tempalarm2_write_reg( ctx, TEMPALARM2_REG_THERM_LIMIT_REMOTE, max_temperature );
}

err_t tempalarm2_get_status ( tempalarm2_t *ctx, uint8_t *status )
{
    return tempalarm2_read_reg( ctx, TEMPALARM2_REG_STATUS, status );
}

err_t tempalarm2_clear_alert ( tempalarm2_t *ctx )
{
    uint8_t response = 0;
    err_t error_flag = TEMPALARM2_OK;

    /* Switch to SMBus Alert Response Address (0x0C) and perform a read.
     * The sensor whose ALERT is active responds with its own 7-bit address
     * in bits[7:1], and the alert direction in bit[0]:
     *    bit[0] = 1 -> temperature exceeded the high limit
     *    bit[0] = 0 -> temperature fell below the low limit
     * After this transaction, if the alert condition is no longer present
     * and the Status Register has been read, the sensor releases the ALERT pin. */
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, TEMPALARM2_SMBUS_ALERT_RESPONSE_ADDR );
    error_flag |= i2c_master_read( &ctx->i2c, &response, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );

    return error_flag;
}

static err_t tempalarm2_set_remote_limit ( tempalarm2_t *ctx, uint8_t reg_high_w, uint8_t reg_low, float temperature )
{
    /* Convert float temperature to a 12-bit unsigned raw count. */
    uint16_t raw_temp = ( uint16_t ) ( temperature / TEMPALARM2_TEMP_LSB );

    /* High byte reg[7:0] = Temp_data[11:4] (integer part).
     * Low  byte reg[7:4] = Temp_data[3:0]  (fractional part, bits[3:0] are unused). */
    uint8_t high_byte = ( uint8_t ) ( ( raw_temp >> 4 ) & TEMPALARM2_BYTE_MASK );
    uint8_t low_byte  = ( uint8_t ) ( ( raw_temp & TEMPALARM2_BYTE_MASK_4BIT ) << 4 );

    err_t error_flag = tempalarm2_write_reg( ctx, reg_high_w, high_byte );
    error_flag |= tempalarm2_write_reg( ctx, reg_low, low_byte );

    return error_flag;
}

// ------------------------------------------------------------------------- END
