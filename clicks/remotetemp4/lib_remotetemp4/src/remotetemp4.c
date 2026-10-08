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
 * @file remotetemp4.c
 * @brief Remote Temp 4 Click Driver.
 */

#include "remotetemp4.h"

/**
 * @brief Remote Temp 4 read temperature function.
 * @details This function reads an 11-bit two's complement temperature value from the
 * specified MSB and LSB registers and converts it to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] reg_msb : Address of the temperature MSB register.
 * @param[in] reg_lsb : Address of the temperature LSB register.
 * @param[out] temperature : Pointer to the output temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t remotetemp4_read_temp ( remotetemp4_t *ctx, uint8_t reg_msb, uint8_t reg_lsb, float *temperature );

/**
 * @brief Remote Temp 4 set remote limit function.
 * @details This function converts a float temperature value to the 11-bit two's
 * complement register format and writes it to the specified MSB and LSB limit registers.
 * @param[in] ctx : Click context object.
 * See #remotetemp4_t object definition for detailed explanation.
 * @param[in] reg_msb : Address of the MSB limit register.
 * @param[in] reg_lsb : Address of the LSB limit register.
 * @param[in] temperature : Temperature limit in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t remotetemp4_set_remote_limit ( remotetemp4_t *ctx, uint8_t reg_msb, uint8_t reg_lsb, float temperature );

void remotetemp4_cfg_setup ( remotetemp4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->thm = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = REMOTETEMP4_DEVICE_ADDRESS;
}

err_t remotetemp4_init ( remotetemp4_t *ctx, remotetemp4_cfg_t *cfg ) 
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

err_t remotetemp4_default_cfg ( remotetemp4_t *ctx ) 
{
    err_t error_flag = REMOTETEMP4_OK;
    
    /* Verify device identity by reading the chip, manufacturer and device ID registers. */
    if ( REMOTETEMP4_ERROR == remotetemp4_check_communication( ctx ) )
    {
        return REMOTETEMP4_ERROR;
    }

    /* 
     * Configuration register (0x03):
     *  - bit[7] = 0 -> ALERT interrupt function is not masked
     *  - bit[6] = 0 -> The chip is active and working normally
     *  - bit[5] = 1 -> Reserved bit, POR value must be preserved
     *  - bit[2] = 1 -> Remote sensor temperature monitor enabled
     *  - bit[1] = 1 -> THERM limit registers (0x19, 0x20) write access enabled
     *  - bit[0] = 0 -> Fault queue disabled, the ALERT pin is asserted on the first
     *                  measurement that falls outside of the limit window 
     */
    error_flag |= remotetemp4_write_reg( ctx, REMOTETEMP4_REG_CONFIGURATION,
                                              REMOTETEMP4_CFG_ALERT_MASK_DISABLE       |
                                              REMOTETEMP4_CFG_CONTINUOUS_MODE          |
                                              REMOTETEMP4_CFG_RESERVED_BIT             |
                                              REMOTETEMP4_CFG_REMOTE_MONITOR_ENABLE    |
                                              REMOTETEMP4_CFG_THERM_LIMIT_WRITE_ENABLE |
                                              REMOTETEMP4_CFG_FAULT_QUEUE_DISABLE );

    /* Conversion rate register (0x04): bits[3:0] = 0x06 -> 4 conversions per second (250 ms period). */
    error_flag |= remotetemp4_set_conv_rate( ctx, REMOTETEMP4_CONV_RATE_4_CPS );

    /* 
     * Alert mode register (0xBF): bit[0] = 1 -> Comparator mode, the ALERT pin follows the
     * alert condition and is released once the temperature returns between the limits. 
     */
    error_flag |= remotetemp4_write_reg( ctx, REMOTETEMP4_REG_ALERT_MODE, REMOTETEMP4_ALERT_MODE_COMPARATOR );

    /* 
     * Alert mask register (0x16): (Enable alerts for all sources, mask bits are active high)
     *  - bit[7] = 0 -> Local temperature high alert is not masked
     *  - bit[4] = 0 -> Remote temperature high alert is not masked
     *  - bit[3] = 0 -> Remote temperature low alert is not masked
     *  - bits[1:0] = 11 -> Reserved bits, POR value must be preserved
     */
    error_flag |= remotetemp4_write_reg( ctx, REMOTETEMP4_REG_ALERT_MASK, REMOTETEMP4_ALERT_MASK_NONE );
                                              
    /* 
     * THERM hysteresis register (0x21): bits[4:0] = 0x01 -> hysteresis = 1 degC.
     * Applies to both the local and remote THERM limits. 
     */
    error_flag |= remotetemp4_set_therm_hyst( ctx, REMOTETEMP4_HYSTERESIS_1_DEG_C );

    /* Set THERM limits for both channels to 30 degC. */
    error_flag |= remotetemp4_set_therm_local( ctx, REMOTETEMP4_THERM_LIMIT_30_DEG_C );
    error_flag |= remotetemp4_set_therm_remote( ctx, REMOTETEMP4_THERM_LIMIT_30_DEG_C );

    /* Set the ALERT high temperature limits for both channels to 30 degC. */
    error_flag |= remotetemp4_set_thigh_local( ctx, REMOTETEMP4_LOCAL_HIGH_LIMIT_30_DEG_C );
    error_flag |= remotetemp4_set_thigh_remote( ctx, REMOTETEMP4_REMOTE_HIGH_LIMIT_30_DEG_C );

    /*
     * Set the ALERT low temperature limit for the remote channel to 0 degC.
     * The device provides no low ALERT limit for the local channel.
     */
    error_flag |= remotetemp4_set_tlow_remote( ctx, REMOTETEMP4_REMOTE_LOW_LIMIT_0_DEG_C );

    return error_flag;
}

err_t remotetemp4_write_reg ( remotetemp4_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return remotetemp4_write_regs( ctx, reg, &data_in, 1 );
}

err_t remotetemp4_write_regs ( remotetemp4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    /* Write frame : S | sl_addr + W | A | reg | A | data0 | A | ... dataN | A | P */
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t remotetemp4_read_reg ( remotetemp4_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return remotetemp4_read_regs( ctx, reg, data_out, 1 );
}

err_t remotetemp4_read_regs ( remotetemp4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    /* Read frame : S | sl_addr + W | A | reg | A | RS | sl_addr + R | A | data0 | A | ... dataN | NA | P */
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t remotetemp4_check_communication ( remotetemp4_t *ctx )
{
    uint8_t chip_id = 0;
    uint8_t manufacturer_id = 0;
    uint8_t device_id = 0;
    err_t error_flag = REMOTETEMP4_OK;

    error_flag |= remotetemp4_read_reg( ctx, REMOTETEMP4_REG_CHIP_ID, &chip_id );
    error_flag |= remotetemp4_read_reg( ctx, REMOTETEMP4_REG_MANUFACTURER_ID, &manufacturer_id );
    error_flag |= remotetemp4_read_reg( ctx, REMOTETEMP4_REG_DEVICE_ID, &device_id );

    if ( ( REMOTETEMP4_CHIP_ID != chip_id ) || 
         ( REMOTETEMP4_MANUFACTURER_ID != manufacturer_id ) || 
         ( REMOTETEMP4_DEVICE_ID != device_id ) )
    {
        return REMOTETEMP4_ERROR;
    }

    return error_flag;
}

uint8_t remotetemp4_get_thm_pin ( remotetemp4_t *ctx )
{
    return digital_in_read( &ctx->thm );
}

uint8_t remotetemp4_get_alr_pin ( remotetemp4_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

err_t remotetemp4_read_local_temp ( remotetemp4_t *ctx, float *temperature )
{
    return remotetemp4_read_temp( ctx, REMOTETEMP4_REG_TEMP_LOCAL_MSB,
                                       REMOTETEMP4_REG_TEMP_LOCAL_LSB,
                                       temperature );
}

err_t remotetemp4_read_remote_temp ( remotetemp4_t *ctx, float *temperature )
{
    return remotetemp4_read_temp( ctx, REMOTETEMP4_REG_TEMP_REMOTE_MSB,
                                       REMOTETEMP4_REG_TEMP_REMOTE_LSB,
                                       temperature );
}

err_t remotetemp4_set_conv_rate ( remotetemp4_t *ctx, uint8_t conv_rate )
{
    return remotetemp4_write_reg( ctx, REMOTETEMP4_REG_CONV_RATE, conv_rate & REMOTETEMP4_CONV_RATE_MASK );
}

err_t remotetemp4_set_thigh_local ( remotetemp4_t *ctx, int8_t max_temperature )
{
    return remotetemp4_write_reg( ctx, REMOTETEMP4_REG_THIGH_LIMIT_LOCAL, ( uint8_t ) max_temperature );
}

err_t remotetemp4_set_thigh_remote ( remotetemp4_t *ctx, float max_temperature )
{
    return remotetemp4_set_remote_limit( ctx, REMOTETEMP4_REG_THIGH_LIMIT_REMOTE_MSB,
                                              REMOTETEMP4_REG_THIGH_LIMIT_REMOTE_LSB,
                                              max_temperature );
}

err_t remotetemp4_set_tlow_remote ( remotetemp4_t *ctx, float min_temperature )
{
    return remotetemp4_set_remote_limit( ctx, REMOTETEMP4_REG_TLOW_LIMIT_REMOTE_MSB,
                                              REMOTETEMP4_REG_TLOW_LIMIT_REMOTE_LSB,
                                              min_temperature );
}

err_t remotetemp4_set_therm_local ( remotetemp4_t *ctx, int8_t max_temperature )
{
    return remotetemp4_write_reg( ctx, REMOTETEMP4_REG_THERM_LIMIT_LOCAL, ( uint8_t ) max_temperature );
}

err_t remotetemp4_set_therm_remote ( remotetemp4_t *ctx, int8_t max_temperature )
{
    return remotetemp4_write_reg( ctx, REMOTETEMP4_REG_THERM_LIMIT_REMOTE, ( uint8_t ) max_temperature );
}

err_t remotetemp4_set_therm_hyst ( remotetemp4_t *ctx, uint8_t hysteresis )
{
    if ( REMOTETEMP4_HYSTERESIS_MAX_DEG_C < hysteresis )
    {
        return REMOTETEMP4_ERROR;
    }
    return remotetemp4_write_reg( ctx, REMOTETEMP4_REG_THERM_HYSTERESIS, hysteresis & REMOTETEMP4_HYSTERESIS_MASK );
}

err_t remotetemp4_get_status ( remotetemp4_t *ctx, uint8_t *status )
{
    return remotetemp4_read_reg( ctx, REMOTETEMP4_REG_ALERT_STATUS, status );
}

static err_t remotetemp4_read_temp ( remotetemp4_t *ctx, uint8_t reg_msb, uint8_t reg_lsb, float *temperature )
{
    err_t error_flag = REMOTETEMP4_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_u = 0;
    int16_t raw_temp = 0;

    /* 
     * Both the local and the remote temperature are 11-bit two's complement values with
     * 0.125 degC resolution, stored across two registers:
     *  - MSB register bits[7:0] -> Temp_data[10:3] -> these bits indicate the integer part of the
     *                                                 temperature value (resolution is 1 degC).
     *  - LSB register bits[7:5] -> Temp_data[2:0]  -> these bits indicate the temperature value
     *                                                 after the decimal point (0.5, 0.25, 0.125 degC).
     * The MSB register is read first so that a conversion completing between the two reads
     * cannot produce a value whose integer part is older than its fractional part.
     */
    error_flag |= remotetemp4_read_reg( ctx, reg_msb, &data_buf[ 0 ] );
    error_flag |= remotetemp4_read_reg( ctx, reg_lsb, &data_buf[ 1 ] );

    /* Assemble the 11-bit unsigned value */
    raw_u = ( ( uint16_t ) data_buf[ 0 ] << 3 ) | ( data_buf[ 1 ] >> 5 );

    /* Sign-extend from 11-bit to 16-bit two's complement */
    if ( raw_u & REMOTETEMP4_SIGN_EXTENSION_11BIT )
    {
        raw_temp = ( int16_t ) ( raw_u | REMOTETEMP4_SIGN_EXTENSION_MASK_11BIT );
    }
    else
    {
        raw_temp = ( int16_t ) raw_u;
    }

    *temperature = ( float ) raw_temp * REMOTETEMP4_TEMP_LSB;

    return error_flag;
}

static err_t remotetemp4_set_remote_limit ( remotetemp4_t *ctx, uint8_t reg_msb, uint8_t reg_lsb, float temperature )
{
    err_t error_flag = REMOTETEMP4_OK;

    /* Convert the float temperature to an 11-bit two's complement raw count */
    int16_t raw_temp = ( int16_t ) ( temperature / REMOTETEMP4_TEMP_LSB );

    /* 
     * Extract the MSB and LSB bytes from the 11-bit value:
     *  - MSB register bits[7:0] = Temp_data[10:3]
     *  - LSB register bits[7:5] = Temp_data[2:0]  (bits[4:0] of the register are reserved)
     */
    uint8_t msb_byte = ( uint8_t ) ( ( raw_temp >> 3 ) & REMOTETEMP4_BYTE_MASK );
    uint8_t lsb_byte = ( uint8_t ) ( ( raw_temp & REMOTETEMP4_BYTE_MASK_3BIT ) << 5 );

    error_flag |= remotetemp4_write_reg( ctx, reg_msb, msb_byte );
    error_flag |= remotetemp4_write_reg( ctx, reg_lsb, lsb_byte );

    return error_flag;
}

// ------------------------------------------------------------------------- END
