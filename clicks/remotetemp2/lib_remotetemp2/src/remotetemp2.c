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
 * @file remotetemp2.c
 * @brief Remote Temp 2 Click Driver.
 */

#include "remotetemp2.h"

/**
 * @brief Remote Temp 2 set remote temperature limit function.
 * @details This function converts a float temperature value to the
 * 12-bit two's complement register format and writes it to the specified
 * high and low byte registers.
 * @param[in] ctx : Click context object.
 * See #remotetemp2_t object definition for detailed explanation.
 * @param[in] reg_high : Address of the high byte limit register.
 * @param[in] reg_low : Address of the low byte limit register.
 * @param[in] temperature : Temperature limit in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t remotetemp2_set_remote_limit ( remotetemp2_t *ctx, uint8_t reg_high, uint8_t reg_low, float temperature );

void remotetemp2_cfg_setup ( remotetemp2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alr = HAL_PIN_NC;
    cfg->tcr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = REMOTETEMP2_DEVICE_ADDRESS;
}

err_t remotetemp2_init ( remotetemp2_t *ctx, remotetemp2_cfg_t *cfg ) 
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
    
    digital_in_init( &ctx->alr, cfg->alr );
    digital_in_init( &ctx->tcr, cfg->tcr );

    return I2C_MASTER_SUCCESS;
}

err_t remotetemp2_default_cfg ( remotetemp2_t *ctx ) 
{
    err_t error_flag = REMOTETEMP2_OK;
    
    /* Configuration register(03h):
     *    bit[7] = 0 -> Alert pin assertion is enabled
     *    bit[6] = 0 -> Continuous mode enabled
     *    bit[5] = 1 -> Comparator mode enabled for ALERT pin(status register clears automatically) */
    error_flag |= remotetemp2_write_reg( ctx, REMOTETEMP2_REG_CONFIGURATION, 
                                              REMOTETEMP2_CFG_CONTINUOUS_MODE | 
                                              REMOTETEMP2_CFG_ALERT_COMPARATOR_MODE );
    
    /* Conv_Period register(04h): bits[3:0] = 0110 -> Conversion period = 0.25s / 4Hz */
    error_flag |= remotetemp2_write_reg( ctx, REMOTETEMP2_REG_CONV_PERIOD, 
                                              REMOTETEMP2_CONV_PERIOD_250MS );
    
    /* Alert_Mask Register(1Fh): (Enable alerts for all channels)
     *    bit[2] = 0 -> ALERT pin is allowed to be asserted low when remote channel 2
                        is out of temperature limit or encounters a diode fault condition.
     *    bit[1] = 0 -> ALERT pin is allowed to be asserted low when remote channel 1
                        is out of temperature limit or encounters a diode fault condition.
     *    bit[0] = 0 -> ALERT pin is allowed to be asserted low when the local channel
                        is out of the temperature limit. */
    error_flag |= remotetemp2_write_reg( ctx, REMOTETEMP2_REG_ALERT_MASK, REMOTETEMP2_ALERT_MASK_ALL );
    
    /* Filter_Control register(40h): bit[1:0] = 00 -> Filter disabled, no internal averaging. */
    error_flag |= remotetemp2_write_reg( ctx, REMOTETEMP2_REG_FILTER_CONTROL, 
                                              REMOTETEMP2_FILTER_DISABLE );
    
    /* Hysteresis register(21h): bit[4:0] = 0001 -> Hysteresis = 1 degC. */
    error_flag |= remotetemp2_write_reg( ctx, REMOTETEMP2_REG_HYSTERESIS, REMOTETEMP2_HYSTERESIS_1_DEG_C );
    
    /* Set critical temperature limits for all channels to 30 degC */
    error_flag |= remotetemp2_set_tcrit_local( ctx, REMOTETEMP2_TCRIT_LIMIT_30_DEG_C );
    error_flag |= remotetemp2_set_tcrit_ch1( ctx, REMOTETEMP2_TCRIT_LIMIT_30_DEG_C );
    error_flag |= remotetemp2_set_tcrit_ch2( ctx, REMOTETEMP2_TCRIT_LIMIT_30_DEG_C );
    
    /* Set high temperature limits for all channels at 30 degC */
    error_flag |= remotetemp2_set_thigh_local( ctx, REMOTETEMP2_LOCAL_HIGH_LIMIT_30_DEG_C );
    error_flag |= remotetemp2_set_thigh_ch1( ctx, REMOTETEMP2_HIGH_LIMIT_30_DEG_C );
    error_flag |= remotetemp2_set_thigh_ch2( ctx, REMOTETEMP2_HIGH_LIMIT_30_DEG_C );
    
    /* Set low temperature limits for all channels at 0 degC */
    error_flag |= remotetemp2_set_tlow_local( ctx, REMOTETEMP2_LOCAL_LOW_LIMIT_0_DEG_C );
    error_flag |= remotetemp2_set_tlow_ch1( ctx, REMOTETEMP2_LOW_LIMIT_0_DEG_C );
    error_flag |= remotetemp2_set_tlow_ch2( ctx, REMOTETEMP2_LOW_LIMIT_0_DEG_C );

    return error_flag;
}

err_t remotetemp2_write_reg ( remotetemp2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return remotetemp2_write_regs( ctx, reg, &data_in, 1 );
}

err_t remotetemp2_write_regs ( remotetemp2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t remotetemp2_read_reg ( remotetemp2_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return remotetemp2_read_regs( ctx, reg, data_out, 1 );
}

err_t remotetemp2_read_regs ( remotetemp2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t remotetemp2_get_alr_pin ( remotetemp2_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

uint8_t remotetemp2_get_tcr_pin ( remotetemp2_t *ctx )
{
    return digital_in_read( &ctx->tcr );
}

err_t remotetemp2_read_local_temp ( remotetemp2_t *ctx, int8_t *temperature )
{
    err_t error_flag = REMOTETEMP2_OK;
    uint8_t data_buf = 0;
    
    /* Local temperature is a 2nd complement 8-bit data with 1 degC resolution stored in Temp_Local Register(0x00) */
    error_flag |= remotetemp2_read_reg( ctx, REMOTETEMP2_REG_TEMP_LOCAL, &data_buf );

    *temperature = ( int8_t ) data_buf;
    
    return error_flag;
}

err_t remotetemp2_read_temp_ch1 ( remotetemp2_t *ctx, float *temperature )
{
    err_t error_flag = REMOTETEMP2_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_u = 0;
    int16_t raw_temp = 0;
    
    /* Remote 1 temperature is a 2nd complement 12-bit data with 0.0625 degC resolution, stored in 2 registers:
     *    Temp_Remote_Ch1_High(01h) bits[7:0] -> Temp_data[11:4]
     *    Temp_Remote_Ch1_Low(10h)  bits[7:4] -> Temp_data[3:0] */
    error_flag |= remotetemp2_read_reg( ctx, REMOTETEMP2_REG_TEMP_REMOTE_CH1_HIGH, &data_buf[ 0 ] );
    error_flag |= remotetemp2_read_reg( ctx, REMOTETEMP2_REG_TEMP_REMOTE_CH1_LOW, &data_buf[ 1 ] );
    
    /* Assemble 12-bit value */
    raw_u = ( ( uint16_t ) data_buf[ 0 ] << 4 ) | ( data_buf[ 1 ] >> 4 );

    /* Sign-extend from 12-bit to 16-bit two's complement */
    if ( raw_u & REMOTETEMP2_SIGN_EXTENSION_12BIT )
    {
        raw_temp = ( int16_t ) ( raw_u | REMOTETEMP2_SIGN_EXTENSION_MASK_12BIT );
    }
    else
    {
        raw_temp = ( int16_t ) raw_u;
    }       

    *temperature = ( float ) raw_temp * REMOTETEMP2_TEMP_REMOTE_LSB;
    
    return error_flag;
}

err_t remotetemp2_read_temp_ch2 ( remotetemp2_t *ctx, float *temperature )
{
    err_t error_flag = REMOTETEMP2_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t raw_u = 0;
    int16_t raw_temp = 0;
    
    /* Remote 2 temperature is a 2nd complement 12-bit data with 0.0625 degC resolution, stored in 2 registers:
     *    Temp_Remote_Ch2_High(23h) bits[7:0] -> Temp_data[11:4]
     *    Temp_Remote_Ch2_Low(24h)  bits[7:4] -> Temp_data[3:0] */
    error_flag |= remotetemp2_read_reg( ctx, REMOTETEMP2_REG_TEMP_REMOTE_CH2_HIGH, &data_buf[ 0 ] );
    error_flag |= remotetemp2_read_reg( ctx, REMOTETEMP2_REG_TEMP_REMOTE_CH2_LOW, &data_buf[ 1 ] );
    
    /* Assemble 12-bit value */
    raw_u = ( ( uint16_t ) data_buf[ 0 ] << 4 ) | ( data_buf[ 1 ] >> 4 );

    /* Sign-extend from 12-bit to 16-bit two's complement */
    if ( raw_u & REMOTETEMP2_SIGN_EXTENSION_12BIT )
    {
        raw_temp = ( int16_t ) ( raw_u | REMOTETEMP2_SIGN_EXTENSION_MASK_12BIT );
    }
    else
    {
        raw_temp = ( int16_t ) raw_u;
    }

    *temperature = ( float ) raw_temp * REMOTETEMP2_TEMP_REMOTE_LSB;
    
    return error_flag;
}

err_t remotetemp2_set_thigh_local ( remotetemp2_t *ctx, int8_t max_temperature )
{
    return remotetemp2_write_reg( ctx, REMOTETEMP2_REG_THIGH_LIMIT_LOCAL, ( uint8_t ) max_temperature );
}

err_t remotetemp2_set_tlow_local ( remotetemp2_t *ctx, int8_t min_temperature )
{
    return remotetemp2_write_reg( ctx, REMOTETEMP2_REG_TLOW_LIMIT_LOCAL, ( uint8_t ) min_temperature );
}

err_t remotetemp2_set_thigh_ch1 ( remotetemp2_t *ctx, float max_temperature )
{
    return remotetemp2_set_remote_limit( ctx, REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH1_HIGH,
                                              REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH1_LOW,
                                              max_temperature );
}

err_t remotetemp2_set_tlow_ch1 ( remotetemp2_t *ctx, float min_temperature )
{
    return remotetemp2_set_remote_limit( ctx, REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH1_HIGH,
                                              REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH1_LOW,
                                              min_temperature );
}

err_t remotetemp2_set_thigh_ch2 ( remotetemp2_t *ctx, float max_temperature )
{
    return remotetemp2_set_remote_limit( ctx, REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH2_HIGH,
                                              REMOTETEMP2_REG_THIGH_LIMIT_REMOTE_CH2_LOW,
                                              max_temperature );
}

err_t remotetemp2_set_tlow_ch2 ( remotetemp2_t *ctx, float min_temperature )
{
    return remotetemp2_set_remote_limit( ctx, REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH2_HIGH,
                                              REMOTETEMP2_REG_TLOW_LIMIT_REMOTE_CH2_LOW,
                                              min_temperature );
}

err_t remotetemp2_set_tcrit_local ( remotetemp2_t *ctx, int8_t max_temperature )
{
    return remotetemp2_write_reg( ctx, REMOTETEMP2_REG_THIGH_CRIT_LOCAL, ( uint8_t ) max_temperature );
}

err_t remotetemp2_set_tcrit_ch1 ( remotetemp2_t *ctx, int8_t max_temperature )
{
    return remotetemp2_write_reg( ctx, REMOTETEMP2_REG_THIGH_CRIT_REMOTE_CH1, ( uint8_t ) max_temperature );
}

err_t remotetemp2_set_tcrit_ch2 ( remotetemp2_t *ctx, int8_t max_temperature )
{
    return remotetemp2_write_reg( ctx, REMOTETEMP2_REG_THIGH_CRIT_REMOTE_CH2, ( uint8_t ) max_temperature );
}

err_t remotetemp2_get_status ( remotetemp2_t *ctx, uint8_t *status )
{
    return remotetemp2_read_reg( ctx, REMOTETEMP2_REG_STATUS, status );
}

err_t remotetemp2_get_diode_fault ( remotetemp2_t *ctx, uint8_t *fault )
{
    return remotetemp2_read_reg( ctx, REMOTETEMP2_REG_DIODE_FAULT, fault );
}

static err_t remotetemp2_set_remote_limit ( remotetemp2_t *ctx, uint8_t reg_high, uint8_t reg_low, float temperature )
{
    /* Convert float temperature to a 12-bit two's complement integer */
    int16_t raw_temp = ( int16_t ) ( temperature / REMOTETEMP2_TEMP_REMOTE_LSB );

    /* Extract the high and low bytes
     * MSB_reg[7:0] = Temp_data[11:4]
     * LSB_reg[7:4] = Temp_data[3:0] */
    uint8_t high_byte = ( uint8_t ) ( ( raw_temp >> 4 ) & REMOTETEMP2_BYTE_MASK );
    uint8_t low_byte  = ( uint8_t ) ( ( raw_temp & REMOTETEMP2_BYTE_MASK_4BIT ) << 4 );

    err_t error_flag = remotetemp2_write_reg( ctx, reg_high, high_byte );
    error_flag |= remotetemp2_write_reg( ctx, reg_low, low_byte );

    return error_flag;
}

// ------------------------------------------------------------------------- END
