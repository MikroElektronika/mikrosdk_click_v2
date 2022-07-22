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
 * @file rtc18.c
 * @brief RTC 18 Click Driver.
 */

#include "rtc18.h"
#include "conversions.h"

void rtc18_cfg_setup ( rtc18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->evi = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC18_DEVICE_ADDRESS;
}

err_t rtc18_init ( rtc18_t *ctx, rtc18_cfg_t *cfg ) 
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

    digital_out_init( &ctx->evi, cfg->evi );
    digital_out_low ( &ctx->evi );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rtc18_default_cfg ( rtc18_t *ctx ) 
{
    err_t error_flag = RTC18_OK;    
    error_flag |= rtc18_write_register ( ctx, RTC18_REG_CONTROL_2, RTC18_CONTROL2_UIE );
    return error_flag;
}

err_t rtc18_generic_write ( rtc18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc18_generic_read ( rtc18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc18_write_register ( rtc18_t *ctx, uint8_t reg, uint8_t data_in )
{
    return rtc18_generic_write ( ctx, reg, &data_in, 1 );
}

err_t rtc18_read_register ( rtc18_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return rtc18_generic_read ( ctx, reg, data_out, 1 );
}

void rtc18_set_evi_pin ( rtc18_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->evi, state );
}

uint8_t rtc18_get_int_pin ( rtc18_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc18_clear_periodic_interrupt ( rtc18_t *ctx )
{
    uint8_t status;
    if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_STATUS, &status ) )
    {
        return RTC18_ERROR;
    }
    status &= ~RTC18_STATUS_UF;
    return rtc18_write_register( ctx, RTC18_REG_STATUS, status );
}

err_t rtc18_set_time ( rtc18_t *ctx, rtc18_time_t *time )
{
    uint8_t data_buf[ 3 ];
    data_buf[ 0 ] = dec_to_bcd ( time->second );
    data_buf[ 1 ] = dec_to_bcd ( time->minute );
    data_buf[ 2 ] = dec_to_bcd ( time->hour );
    if ( RTC18_ERROR == rtc18_generic_write ( ctx, RTC18_REG_SECONDS, data_buf, 3 ) )
    {
        return RTC18_ERROR;
    }
    return RTC18_OK;
}

err_t rtc18_read_time ( rtc18_t *ctx, rtc18_time_t *time )
{
    uint8_t data_buf[ 4 ];
    if ( RTC18_ERROR == rtc18_generic_read ( ctx, RTC18_REG_100TH_SECONDS, data_buf, 4 ) )
    {
        return RTC18_ERROR;
    }
    time->second_100th = bcd_to_dec ( data_buf[ 0 ] );
    time->second = bcd_to_dec ( data_buf[ 1 ] );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    return RTC18_OK;
}

err_t rtc18_set_date ( rtc18_t *ctx, rtc18_date_t *date )
{
    uint8_t data_buf[ 4 ];
    data_buf[ 0 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 1 ] = dec_to_bcd ( date->day );
    data_buf[ 2 ] = dec_to_bcd ( date->month );
    data_buf[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC18_ERROR == rtc18_generic_write ( ctx, RTC18_REG_WEEKDAY, data_buf, 4 ) )
    {
        return RTC18_ERROR;
    }
    return RTC18_OK;
}

err_t rtc18_read_date ( rtc18_t *ctx, rtc18_date_t *date )
{
    uint8_t data_buf[ 4 ];
    if ( RTC18_ERROR == rtc18_generic_read ( ctx, RTC18_REG_WEEKDAY, data_buf, 4 ) )
    {
        return RTC18_ERROR;
    }
    date->day_of_week = data_buf[ 0 ];
    date->day = bcd_to_dec ( data_buf[ 1 ] );
    date->month = bcd_to_dec ( data_buf[ 2 ] );
    date->year = bcd_to_dec ( data_buf[ 3 ] );
    return RTC18_OK;
}

err_t rtc18_read_temperature ( rtc18_t *ctx, float *temperature )
{
    uint8_t data_buf[ 2 ];
    if ( RTC18_ERROR == rtc18_generic_read ( ctx, RTC18_REG_TEMPERATURE_LSB, data_buf, 2 ) )
    {
        return RTC18_ERROR;
    }
    *temperature = ( ( int16_t ) ( ( ( int16_t ) data_buf[ 1 ] << 8 ) | 
                                   ( data_buf[ 0 ] & RTC18_TEMPERATURE_LSB_TEMP_BIT_MASK ) ) >> 4 ) * 
                    RTC18_TEMPERATURE_RESOLUTION;
    return RTC18_OK;
}

err_t rtc18_write_eeprom ( rtc18_t *ctx, uint8_t address, uint8_t data_in )
{
    if ( ( address < RTC18_EEPROM_PMU ) || ( address >= ( RTC18_EEPROM_USER_MEMORY_32B + 32 ) ) )
    {
        return RTC18_ERROR;
    }
    uint8_t control_1, eeprom_busy;
    if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_CONTROL_1, &control_1 ) )
    {
        return RTC18_ERROR;
    }
    control_1 |= RTC18_CONTROL1_EERD;
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_CONTROL_1, control_1 ) )
    {
        return RTC18_ERROR;
    }
    do 
    {
        Delay_1ms ( );
        if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_TEMPERATURE_LSB, &eeprom_busy ) )
        {
            return RTC18_ERROR;
        }
    } while ( eeprom_busy & RTC18_TEMPERATURE_LSB_EEBUSY );
    
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_EEPROM_ADDRESS, address ) )
    {
        return RTC18_ERROR;
    }
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_EEPROM_DATA, data_in ) )
    {
        return RTC18_ERROR;
    }
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_EEPROM_COMMAND, RTC18_EECMD_WRITE_ONE_BYTE ) )
    {
        return RTC18_ERROR;
    }
    Delay_10ms ( );
    do 
    {
        Delay_1ms ( );
        if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_TEMPERATURE_LSB, &eeprom_busy ) )
        {
            return RTC18_ERROR;
        }
    } while ( eeprom_busy & RTC18_TEMPERATURE_LSB_EEBUSY );
    control_1 &= ~RTC18_CONTROL1_EERD;
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_CONTROL_1, control_1 ) )
    {
        return RTC18_ERROR;
    }
    return RTC18_OK;
}

err_t rtc18_read_eeprom ( rtc18_t *ctx, uint8_t address, uint8_t *data_out )
{
    if ( ( address < RTC18_EEPROM_PMU ) || ( address >= ( RTC18_EEPROM_USER_MEMORY_32B + 32 ) ) )
    {
        return RTC18_ERROR;
    }
    uint8_t control_1, eeprom_busy;
    if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_CONTROL_1, &control_1 ) )
    {
        return RTC18_ERROR;
    }
    control_1 |= RTC18_CONTROL1_EERD;
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_CONTROL_1, control_1 ) )
    {
        return RTC18_ERROR;
    }
    do 
    {
        Delay_1ms ( );
        if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_TEMPERATURE_LSB, &eeprom_busy ) )
        {
            return RTC18_ERROR;
        }
    } while ( eeprom_busy & RTC18_TEMPERATURE_LSB_EEBUSY );
    
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_EEPROM_ADDRESS, address ) )
    {
        return RTC18_ERROR;
    }
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_EEPROM_COMMAND, RTC18_EECMD_READ_ONE_BYTE ) )
    {
        return RTC18_ERROR;
    }
    Delay_10ms ( );
    if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_EEPROM_DATA, data_out ) )
    {
        return RTC18_ERROR;
    }
    do 
    {
        Delay_1ms ( );
        if ( RTC18_ERROR == rtc18_read_register ( ctx, RTC18_REG_TEMPERATURE_LSB, &eeprom_busy ) )
        {
            return RTC18_ERROR;
        }
    } while ( eeprom_busy & RTC18_TEMPERATURE_LSB_EEBUSY );
    control_1 &= ~RTC18_CONTROL1_EERD;
    if ( RTC18_ERROR == rtc18_write_register ( ctx, RTC18_REG_CONTROL_1, control_1 ) )
    {
        return RTC18_ERROR;
    }
    return RTC18_OK;
}


// ------------------------------------------------------------------------- END
