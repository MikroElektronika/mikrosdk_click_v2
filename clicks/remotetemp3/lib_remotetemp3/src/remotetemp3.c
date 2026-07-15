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
 * @file remotetemp3.c
 * @brief Remote Temp 3 Click Driver.
 */

#include "remotetemp3.h"

/**
 * @brief Remote Temp 3 set remote limit function.
 * @details This function converts a float temperature value to the
 * 12-bit two's complement register format and writes it to the specified
 * high and low byte limit registers.
 * @param[in] ctx : Click context object.
 * See #remotetemp3_t object definition for detailed explanation.
 * @param[in] reg_high_w : Write address of the high byte limit register.
 * @param[in] reg_low : Address of the low byte limit register (same for read/write).
 * @param[in] temperature : Temperature limit in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t remotetemp3_set_remote_limit ( remotetemp3_t *ctx, uint8_t reg_high_w, uint8_t reg_low, float temperature );

void remotetemp3_cfg_setup ( remotetemp3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->thm = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = REMOTETEMP3_DEVICE_ADDRESS;
}

err_t remotetemp3_init ( remotetemp3_t *ctx, remotetemp3_cfg_t *cfg ) 
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

    digital_in_init( &ctx->thm, cfg->thm );
    digital_in_init( &ctx->alr, cfg->alr );

    return I2C_MASTER_SUCCESS;
}

err_t remotetemp3_default_cfg ( remotetemp3_t *ctx ) 
{    
    err_t error_flag = REMOTETEMP3_OK;
    uint8_t mfr_id = 0;

    /* Verify device identity by reading the Manufacturer Identification Register (0xFE).
     * The expected value is 0x55. */
    error_flag |= remotetemp3_read_reg( ctx, REMOTETEMP3_REG_MANUFACTURER_ID, &mfr_id );
    if ( REMOTETEMP3_MANUFACTURER_ID != mfr_id )
    {
        return REMOTETEMP3_ERROR;
    }

    /* Configuration register (write to 0x09):
     *    bit[7] = 0 -> ALERT enabled
     *    bit[6] = 0 -> Device converts continuously at the rate set in the conversion rate register
     *    bit[5] = 0 -> Pin 7 configured as ALERT output
     *    bit[2] = 0 -> Standard measurement range: -40 degC to +127 degC */
    error_flag |= remotetemp3_write_reg( ctx, REMOTETEMP3_REG_CONFIGURATION_W,
                                              REMOTETEMP3_CFG_CONTINUOUS_MODE |
                                              REMOTETEMP3_CFG_ALERT_MODE      |
                                              REMOTETEMP3_CFG_STANDARD_RANGE );

    /* Conversion rate register (write to 0x0A): bit[3:0] = 0x06 -> 4 conversions per second (250 ms period). */
    error_flag |= remotetemp3_write_reg( ctx, REMOTETEMP3_REG_CONV_RATE_W,
                                              REMOTETEMP3_CONV_RATE_4_CPS );

    /* Channel enable register (0x16): 
     *    bit[1] = 1 ->  Enable the conversion of remote temperature 
     *    bit[0] = 1 ->  Enable the conversion of local temperature */
    error_flag |= remotetemp3_write_reg( ctx, REMOTETEMP3_REG_CHANNEL_ENABLE,
                                              REMOTETEMP3_CHANNEL_ENABLE_BOTH );

    /* Digital filter control register (0x24): 0x00 -> filter disabled, no internal averaging. */
    error_flag |= remotetemp3_write_reg( ctx, REMOTETEMP3_REG_DIGITAL_FILTER,
                                              REMOTETEMP3_FILTER_DISABLE );

    /* THERM hysteresis register (0x21): 0x01 -> hysteresis = 1 degC.
     * Applies to both the local and remote THERM limits. */
    error_flag |= remotetemp3_write_reg( ctx, REMOTETEMP3_REG_THERM_HYSTERESIS,
                                              REMOTETEMP3_HYSTERESIS_1_DEG_C );

    /* Set THERM limits for both channels to 30 degC. */
    error_flag |= remotetemp3_set_therm_local( ctx, REMOTETEMP3_THERM_LIMIT_30_DEG_C );
    error_flag |= remotetemp3_set_therm_remote( ctx, REMOTETEMP3_THERM_LIMIT_30_DEG_C );

    /* Set ALERT high temperature limits for both channels to 30 degC. */
    error_flag |= remotetemp3_set_thigh_local( ctx, REMOTETEMP3_LOCAL_HIGH_LIMIT_30_DEG_C );
    error_flag |= remotetemp3_set_thigh_remote( ctx, REMOTETEMP3_REMOTE_HIGH_LIMIT_30_DEG_C );

    /* Set ALERT low temperature limits for both channels to 0 degC. */
    error_flag |= remotetemp3_set_tlow_local( ctx, REMOTETEMP3_LOCAL_LOW_LIMIT_0_DEG_C );
    error_flag |= remotetemp3_set_tlow_remote( ctx, REMOTETEMP3_REMOTE_LOW_LIMIT_0_DEG_C );

    return error_flag;
}

err_t remotetemp3_write_reg ( remotetemp3_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return remotetemp3_write_regs( ctx, reg, &data_in, 1 );
}

err_t remotetemp3_write_regs ( remotetemp3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t remotetemp3_read_reg ( remotetemp3_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return remotetemp3_read_regs( ctx, reg, data_out, 1 );
}

err_t remotetemp3_read_regs ( remotetemp3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t remotetemp3_get_thm_pin ( remotetemp3_t *ctx )
{
    return digital_in_read( &ctx->thm );
}

uint8_t remotetemp3_get_alr_pin ( remotetemp3_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

err_t remotetemp3_read_local_temp ( remotetemp3_t *ctx, float *temperature )
{
    err_t error_flag = REMOTETEMP3_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_u = 0;
    int16_t raw_temp = 0;

    /* Local temperature is a 12-bit two's complement value with 0.0625 degC resolution,
     * stored across two registers:
     *    Temp_Local_High (0x00) bits[7:0] -> Temp_data[11:4] -> these bits indicate the integer part of the
     *                                                           temperature value (resolution is 1 degC).
     *    Temp_Local_Low  (0x15) bits[7:4] -> Temp_data[3:0]  -> these bits indicate temperature value 
     *                                                           after the decimal point (resolution is 0.0625 degC).
     * The high byte must always be read first. This causes the device to lock the
     * low byte until it is read, guaranteeing both bytes are from the same ADC conversion. */
    error_flag |= remotetemp3_read_reg( ctx, REMOTETEMP3_REG_TEMP_LOCAL_HIGH, &data_buf[ 0 ] );
    error_flag |= remotetemp3_read_reg( ctx, REMOTETEMP3_REG_TEMP_LOCAL_LOW, &data_buf[ 1 ] );

    /* Assemble 12-bit unsigned value */
    raw_u = ( ( uint16_t ) data_buf[ 0 ] << 4 ) | ( data_buf[ 1 ] >> 4 );

    /* Sign-extend from 12-bit to 16-bit two's complement */
    if ( raw_u & REMOTETEMP3_SIGN_EXTENSION_12BIT )
    {
        raw_temp = ( int16_t ) ( raw_u | REMOTETEMP3_SIGN_EXTENSION_MASK_12BIT );
    }
    else
    {
        raw_temp = ( int16_t ) raw_u;
    }

    *temperature = ( float ) raw_temp * REMOTETEMP3_TEMP_LSB;

    return error_flag;
}

err_t remotetemp3_read_remote_temp ( remotetemp3_t *ctx, float *temperature )
{
    err_t error_flag = REMOTETEMP3_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_u = 0;
    int16_t raw_temp = 0;

    /* Remote temperature is a 12-bit two's complement value with 0.0625 degC resolution,
     * stored across two registers:
     *    Temp_Remote_High (0x01) bits[7:0] -> Temp_data[11:4] -> these bits indicate the integer part of the
     *                                                            temperature value (resolution is 1 degC).
     *    Temp_Remote_Low  (0x10) bits[7:4] -> Temp_data[3:0]  -> these bits indicate temperature value
     *                                                            after the decimal point (resolution is 0.0625 degC).
     * The high byte must always be read first. This causes the device to lock the
     * low byte until it is read, guaranteeing both bytes are from the same ADC conversion. */
    error_flag |= remotetemp3_read_reg( ctx, REMOTETEMP3_REG_TEMP_REMOTE_HIGH, &data_buf[ 0 ] );
    error_flag |= remotetemp3_read_reg( ctx, REMOTETEMP3_REG_TEMP_REMOTE_LOW, &data_buf[ 1 ] );

    /* Assemble 12-bit unsigned value */
    raw_u = ( ( uint16_t ) data_buf[ 0 ] << 4 ) | ( data_buf[ 1 ] >> 4 );

    /* Sign-extend from 12-bit to 16-bit two's complement */
    if ( raw_u & REMOTETEMP3_SIGN_EXTENSION_12BIT )
    {
        raw_temp = ( int16_t ) ( raw_u | REMOTETEMP3_SIGN_EXTENSION_MASK_12BIT );
    }
    else
    {
        raw_temp = ( int16_t ) raw_u;
    }

    *temperature = ( float ) raw_temp * REMOTETEMP3_TEMP_LSB;

    return error_flag;
}

err_t remotetemp3_set_thigh_local ( remotetemp3_t *ctx, int8_t max_temperature )
{
    return remotetemp3_write_reg( ctx, REMOTETEMP3_REG_THIGH_LIMIT_LOCAL_W, ( uint8_t ) max_temperature );
}

err_t remotetemp3_set_tlow_local ( remotetemp3_t *ctx, int8_t min_temperature )
{
    return remotetemp3_write_reg( ctx, REMOTETEMP3_REG_TLOW_LIMIT_LOCAL_W, ( uint8_t ) min_temperature );
}

err_t remotetemp3_set_thigh_remote ( remotetemp3_t *ctx, float max_temperature )
{
    return remotetemp3_set_remote_limit( ctx, REMOTETEMP3_REG_THIGH_LIMIT_REMOTE_HIGH_W,
                                              REMOTETEMP3_REG_THIGH_LIMIT_REMOTE_LOW,
                                              max_temperature );
}

err_t remotetemp3_set_tlow_remote ( remotetemp3_t *ctx, float min_temperature )
{
    return remotetemp3_set_remote_limit( ctx, REMOTETEMP3_REG_TLOW_LIMIT_REMOTE_HIGH_W,
                                              REMOTETEMP3_REG_TLOW_LIMIT_REMOTE_LOW,
                                              min_temperature );
}

err_t remotetemp3_set_therm_local ( remotetemp3_t *ctx, int8_t max_temperature )
{
    return remotetemp3_write_reg( ctx, REMOTETEMP3_REG_THERM_LIMIT_LOCAL, ( uint8_t ) max_temperature );
}

err_t remotetemp3_set_therm_remote ( remotetemp3_t *ctx, int8_t max_temperature )
{
    return remotetemp3_write_reg( ctx, REMOTETEMP3_REG_THERM_LIMIT_REMOTE, ( uint8_t ) max_temperature );
}

err_t remotetemp3_get_status ( remotetemp3_t *ctx, uint8_t *status )
{
    return remotetemp3_read_reg( ctx, REMOTETEMP3_REG_STATUS, status );
}

static err_t remotetemp3_set_remote_limit ( remotetemp3_t *ctx, uint8_t reg_high_w, uint8_t reg_low, float temperature )
{
    /* Convert float temperature to a 12-bit two's complement raw count */
    int16_t raw_temp = ( int16_t ) ( temperature / REMOTETEMP3_TEMP_LSB );

    /* Extract the high and low bytes from the 12-bit value:
     *    High byte reg[7:0] = Temp_data[11:4]
     *    Low  byte reg[7:4] = Temp_data[3:0]  (bits[3:0] of the register are unused) */
    uint8_t high_byte = ( uint8_t ) ( ( raw_temp >> 4 ) & REMOTETEMP3_BYTE_MASK );
    uint8_t low_byte  = ( uint8_t ) ( ( raw_temp & REMOTETEMP3_BYTE_MASK_4BIT ) << 4 );

    err_t error_flag = remotetemp3_write_reg( ctx, reg_high_w, high_byte );
    error_flag |= remotetemp3_write_reg( ctx, reg_low, low_byte );

    return error_flag;
}

// ------------------------------------------------------------------------- END
