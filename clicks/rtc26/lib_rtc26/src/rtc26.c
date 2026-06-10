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
 * @file rtc26.c
 * @brief RTC 26 Click Driver.
 */

#include "rtc26.h"
#include "conversions.h"

/**
 * @brief RTC 26 WEEK register valid bitmask values setting.
 * @details Specified setting for valid bitmask values of WEEK register of RTC 26 Click driver.
 */
static const uint8_t rtc26_week_valid_values[ RTC26_WEEK_DAYS_NUM ] =
{
    RTC26_WEEK_SUNDAY,
    RTC26_WEEK_MONDAY,
    RTC26_WEEK_TUESDAY,
    RTC26_WEEK_WEDNESDAY,
    RTC26_WEEK_THURSDAY,
    RTC26_WEEK_FRIDAY,
    RTC26_WEEK_SATURDAY
};

/**
 * @brief RTC 26 week value validation function.
 * @details This function validates the day_of_week field of the date structure
 * to ensure it contains a valid value.
 * @param[in] week_val : Value to validate.
 * @return @li @c  0 - Invalid week bitmask,
 *         @li @c -1 - Valid week bitmask.
 * @note None.
 */
static uint8_t rtc26_week_is_valid ( uint8_t week_val );

void rtc26_cfg_setup ( rtc26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->out = HAL_PIN_NC;
    cfg->foe = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC26_DEVICE_ADDRESS;
}

err_t rtc26_init ( rtc26_t *ctx, rtc26_cfg_t *cfg ) 
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

    digital_out_init( &ctx->foe, cfg->foe );

    digital_in_init( &ctx->out, cfg->out );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rtc26_default_cfg ( rtc26_t *ctx )
{
    err_t error_flag = RTC26_OK;
    uint8_t reg_value = 0;
    uint8_t dev_id = 0;

    /* -------------------------------------------------------------- 
     * Power-on initialization sequence (Section 9 of the datasheet).
     * These accesses use internal registers not listed in the 
     * register map, but are required for correct RTC operation.
     * -------------------------------------------------------------- */
    reg_value = 0xD1;
    error_flag |= rtc26_generic_write( ctx, 0x30, &reg_value, 1 );

    reg_value = 0x00;
    error_flag |= rtc26_generic_write( ctx, 0x40, &reg_value, 1 );

    reg_value = 0x81;
    error_flag |= rtc26_generic_write( ctx, 0x32, &reg_value, 1 );

    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );

    reg_value = 0x80;
    error_flag |= rtc26_generic_write( ctx, 0x32, &reg_value, 1 );

    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );

    reg_value = 0x04;
    error_flag |= rtc26_generic_write( ctx, 0x32, &reg_value, 1 );

    /* Verify Device ID and apply IC-specific tuning if correct */
    error_flag |= rtc26_generic_read( ctx, RTC26_REG_DEVICE_ID, &dev_id, 1 );
    if ( RTC26_DEVICE_ID == dev_id )
    {
        /* Set internal register 0x5C bits [3:0] = 0b1100 */
        error_flag |= rtc26_generic_read( ctx, 0x5C, &reg_value, 1 );
        reg_value = ( reg_value & 0xF0 ) | 0x0C;
        error_flag |= rtc26_generic_write( ctx, 0x5C, &reg_value, 1 );

        /* Set internal register 0x5A bits [7:5] = 0b111 */
        error_flag |= rtc26_generic_read( ctx, 0x5A, &reg_value, 1 );
        reg_value = ( reg_value & 0x1F ) | 0xE0;
        error_flag |= rtc26_generic_write( ctx, 0x5A, &reg_value, 1 );
    }
    else
    {
        error_flag = RTC26_ERROR;
    }

    reg_value = 0x00;
    error_flag |= rtc26_generic_write( ctx, 0x30, &reg_value, 1 );
 
    /* --------------------------------------------------------------  
     * Standard register initialization
     * -------------------------------------------------------------- */

    /* RSV register must be set to 0x80 (required by datasheet). */
    reg_value = RTC26_RSV_REQUIRED_VAL;
    error_flag |= rtc26_generic_write( ctx, RTC26_REG_RSV, &reg_value, 1 );

    /* write-0-clear all clearable flag bits (UF, TF, AF, VLF, VDET) */
    reg_value = 0x00;
    error_flag |= rtc26_generic_write( ctx, RTC26_REG_FLAG, &reg_value, 1 );

    /* Extension register:
     *    TEST  = 0  -> must always be 0. 
     *    WADA  = 0  -> alarm register 0x0A acts as WEEK alarm.
     *    USEL  = 0  -> update output interrupt once a second.
     *    TE    = 0  -> countdown timer disabled.
     *    FSEL  = 00 -> FOUT frequency = 1Hz.
     *    TSEL  = 00 -> timer source clock = 4096 Hz (default). */
    reg_value = RTC26_EXT_WADA_WEEK |
                RTC26_EXT_USEL_1S |
                RTC26_EXT_TE_DISABLE |
                RTC26_EXT_FSEL_1HZ |
                RTC26_EXT_TSEL_4096HZ;
    error_flag |= rtc26_generic_write( ctx, RTC26_REG_EXTENSION, &reg_value, 1 );

    /* Control register:
     *    CSEL  = 01 -> temperature compensation runs every 2 s (default).
     *    UIE   = 0  -> update interrupt disabled. 
     *    TIE   = 0  -> timer interrupt disabled.
     *    AIE   = 0  -> alarm interrupt disabled. */
    reg_value = RTC26_CTRL_CSEL_2S;
    error_flag |= rtc26_generic_write( ctx, RTC26_REG_CONTROL, &reg_value, 1 );

    /* Enable FOUT output */
    digital_out_high( &ctx->foe );

    return error_flag;
}

err_t rtc26_generic_write ( rtc26_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc26_generic_read ( rtc26_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc26_set_time ( rtc26_t *ctx, rtc26_time_t rtc_time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    
    /* Validate all time fields */
    if ( ( rtc_time.second > RTC26_MAX_SEC  ) ||
         ( rtc_time.minute > RTC26_MAX_MIN  ) ||
         ( rtc_time.hour   > RTC26_MAX_HOUR ) )
    {
        return RTC26_ERROR;
    }
    
    /* The RTC stores time in BCD format */
    data_buf[ 0 ] = dec_to_bcd( rtc_time.second );
    data_buf[ 1 ] = dec_to_bcd( rtc_time.minute );
    data_buf[ 2 ] = dec_to_bcd( rtc_time.hour   );
    
    /* Write all three registers in one burst( AB-RTC-TC I2C uses auto-increment for multi byte read/write ) */
    return rtc26_generic_write( ctx, RTC26_REG_SEC, data_buf, 3 );
}

err_t rtc26_get_time ( rtc26_t *ctx, rtc26_time_t *rtc_time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    
    /* Read SEC (0x00), MIN (0x01), HOUR (0x02) in a single burst read. */
    if ( RTC26_OK != rtc26_generic_read( ctx, RTC26_REG_SEC, data_buf, 3 ) )
    {
        return RTC26_ERROR;
    }
    
    /* Mask unused bits before BCD-to-decimal conversion */
    rtc_time->second = bcd_to_dec( data_buf[ 0 ] & RTC26_SEC_BIT_MASK );  
    rtc_time->minute = bcd_to_dec( data_buf[ 1 ] & RTC26_MIN_BIT_MASK );  
    rtc_time->hour   = bcd_to_dec( data_buf[ 2 ] & RTC26_HOUR_BIT_MASK );

    return RTC26_OK;
}

err_t rtc26_set_date ( rtc26_t *ctx, rtc26_date_t rtc_date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t max_num_day = 0;
    
    /* Validate month range */
    if ( ( rtc_date.month < RTC26_MIN_MONTH ) || ( rtc_date.month > RTC26_MAX_MONTH ) )
    {
        return RTC26_ERROR;
    }
     
    /* Validate day_of_week */
    if ( !rtc26_week_is_valid( rtc_date.day_of_week ) )
    {
        return RTC26_ERROR;
    }

    /* Determine maximum day for the given month (leap year aware) */
    switch ( rtc_date.month )
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        {
            max_num_day = 31;
            break;
        }
        case 4: case 6: case 9: case 11:
        {
            max_num_day = 30;
            break;
        }
        case 2:
        {
            /* February: 29 days in a leap year, 28 otherwise.
             * year is 0-99 (relative to 2000), divisible by 4 = leap year. */
            max_num_day = ( rtc_date.year % 4 == 0 ) ? 29 : 28;
            break;
        }
        default:
        {
            return RTC26_ERROR;
        }
    }
    
    /* Validate the day number against the computed monthly maximum. */
    if ( ( rtc_date.day < RTC26_MIN_DAY ) || ( rtc_date.day > max_num_day ) )
    {
        return RTC26_ERROR;
    }
    
    /* Pack the four registers for a single burst write starting at WEEK (0x03). */
    data_buf[ 0 ] = rtc_date.day_of_week & RTC26_WEEK_BIT_MASK;
    data_buf[ 1 ] = dec_to_bcd( rtc_date.day );
    data_buf[ 2 ] = dec_to_bcd( rtc_date.month );
    data_buf[ 3 ] = dec_to_bcd( rtc_date.year  );

    return rtc26_generic_write( ctx, RTC26_REG_WEEK, data_buf, 4 );
}

err_t rtc26_get_date ( rtc26_t *ctx, rtc26_date_t *rtc_date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    
    /* Burst read of WEEK (0x03), DAY (0x04), MONTH (0x05), YEAR (0x06). */
    if ( RTC26_OK != rtc26_generic_read( ctx, RTC26_REG_WEEK, data_buf, 4 ) )
    {
        return RTC26_ERROR;
    }

    /* WEEK register returns the bitmask directly -> no BCD decoding. */
    rtc_date->day_of_week = data_buf[ 0 ] & RTC26_WEEK_BIT_MASK;
    rtc_date->day = bcd_to_dec( data_buf[ 1 ] & RTC26_DAY_BIT_MASK );
    rtc_date->month = bcd_to_dec( data_buf[ 2 ] & RTC26_MONTH_BIT_MASK );
    rtc_date->year = bcd_to_dec( data_buf[ 3 ] );

    return RTC26_OK;
}

err_t rtc26_set_alarm ( rtc26_t *ctx, rtc26_alarm_t rtc_alarm )
{
    uint8_t data_buf[ 3 ] = { 0 };
    
    /* Validate alarm time fields */
    if ( ( rtc_alarm.minute > RTC26_MAX_MIN  ) ||
         ( rtc_alarm.hour   > RTC26_MAX_HOUR ) )
    {
        return RTC26_ERROR;
    }

    /* MIN Alarm register: AE bit (bit7) + BCD minute value */
    data_buf[ 0 ] = ( rtc_alarm.minute_en & RTC26_ALARM_AE_BIT_MASK ) | dec_to_bcd( rtc_alarm.minute );

    /* HOUR Alarm register: AE bit (bit7) + BCD hour value */
    data_buf[ 1 ] = ( rtc_alarm.hour_en & RTC26_ALARM_AE_BIT_MASK ) | dec_to_bcd( rtc_alarm.hour );

    /* WEEK/DAY Alarm register: AE bit (bit7) + week bitmask or BCD day value */
    data_buf[ 2 ] = ( rtc_alarm.day_week_en & RTC26_ALARM_AE_BIT_MASK ) | ( rtc_alarm.day_week & RTC26_ALARM_DAY_WEEK_BIT_MASK );
    
    /* Burst write: MIN_ALARM (0x08), HOUR_ALARM (0x09), WEEK_DAY_ALARM (0x0A) */
    return rtc26_generic_write( ctx, RTC26_REG_MIN_ALARM, data_buf, 3 );
}

err_t rtc26_get_alarm ( rtc26_t *ctx, rtc26_alarm_t *rtc_alarm )
{
    uint8_t data_buf[ 3 ] = { 0 };
    
    /* Burst read of MIN_ALARM (0x08), HOUR_ALARM (0x09), WEEK_DAY_ALARM (0x0A). */
    err_t error_flag = rtc26_generic_read( ctx, RTC26_REG_MIN_ALARM, data_buf, 3 );
    
    /* Separate the AE enable bit (bit 7) from the data bits for each register. */
    rtc_alarm->minute_en = data_buf[ 0 ] & RTC26_ALARM_AE_BIT_MASK;
    rtc_alarm->minute = bcd_to_dec( data_buf[ 0 ] & RTC26_ALARM_MIN_BIT_MASK );

    rtc_alarm->hour_en = data_buf[ 1 ] & RTC26_ALARM_AE_BIT_MASK;
    rtc_alarm->hour = bcd_to_dec( data_buf[ 1 ] & RTC26_ALARM_HOUR_BIT_MASK );
    
    rtc_alarm->day_week_en = data_buf[ 2 ] & RTC26_ALARM_AE_BIT_MASK;
    rtc_alarm->day_week = data_buf[ 2 ] & RTC26_ALARM_DAY_WEEK_BIT_MASK;

    return error_flag;
}

err_t rtc26_get_flag_register ( rtc26_t *ctx, uint8_t *flag )
{
    return rtc26_generic_read( ctx, RTC26_REG_FLAG, flag, 1 );
}

err_t rtc26_clear_flag ( rtc26_t *ctx, uint8_t flag_mask )
{
    uint8_t tmp = 0;
    err_t error_flag = RTC26_OK;
    
    /* Read the current flag register value */
    error_flag = rtc26_generic_read( ctx, RTC26_REG_FLAG, &tmp, 1 );

    /* Clear only the requested flag bits (these are write-0-clear bits) */
    tmp &= ~flag_mask;
    
    /* Write the modified value back */
    error_flag |= rtc26_generic_write( ctx, RTC26_REG_FLAG, &tmp, 1 );

    return error_flag;
}

void rtc26_set_foe_pin ( rtc26_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->foe, state );
}

uint8_t rtc26_get_int_pin ( rtc26_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t rtc26_get_out_pin ( rtc26_t *ctx )
{
    return digital_in_read( &ctx->out );
}

err_t rtc26_get_temperature ( rtc26_t *ctx, float *temperature )
{
    uint8_t tmp = 0;

    /* Read the 8-bit raw temperature value from register 0x17 (TEMP) */
    err_t error_flag = rtc26_generic_read( ctx, RTC26_REG_TEMP, &tmp, 1 );
    
    /* Convert the raw 8-bit value to degrees Celsius using the formula
     * provided in datasheet section 6.2.7:
     *
     *   Temp [degC] = ( TEMP[7:0] * 2 - 147.5 ) / 3.0448 */
    *temperature = ( ( float ) tmp * RTC26_TEMP_MULTIPLIER - RTC26_TEMP_OFFSET ) / RTC26_TEMP_DIVISOR;

    return error_flag;
}

static uint8_t rtc26_week_is_valid ( uint8_t week_val )
{
    uint8_t cnt;
    for ( cnt = 0; cnt < RTC26_WEEK_DAYS_NUM; cnt++ )
    {
        if ( rtc26_week_valid_values[ cnt ] == week_val )
        {
            return 1;
        }
    }
    return 0;
}

// ------------------------------------------------------------------------- END
