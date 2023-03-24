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
 * @file nvsram3.c
 * @brief nvSRAM 3 Click Driver.
 */

#include "nvsram3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                    0x00

/**
 * @brief LSN data.
 * @details Least significant nibble data.
 */
#define BIT_MASK_LSN             0x0F

/**
 * @brief Last memory address.
 * @details Last memory address value.
 */
#define LAST_MEMORY_ADDRESS      0x0001FFFF

/**
 * @brief MSB of address.
 * @details MSB of address mask.
 */
#define ADDRESS_MSB      0x00010000

/**
 * @brief Max sec value.
 * @details Maximum value of minutes and seconds.
 */
#define MAX_SEC              59

/**
 * @brief Max hour value.
 * @details Maximum hour value.
 */
#define MAX_HOUR                 23

/**
 * @brief Max day value.
 * @details Maximum day value.
 */
#define MAX_DAY                  31

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Decimal to BCD.
 * @details Decimal to BCD converter function.
 */
static uint8_t dev_dec_to_bcd ( uint8_t dec );

/**
 * @brief BCD to decimal.
 * @details BCD to decimal converter function.
 */
static uint8_t dev_bcd_to_dec ( uint8_t bcd );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void nvsram3_cfg_setup ( nvsram3_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->hsb = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NVSRAM3_MEMORY_DEV_ADDR_0;
}

err_t nvsram3_init ( nvsram3_t *ctx, nvsram3_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->hsb, cfg->hsb );
    digital_out_init( &ctx->wp, cfg->wp );
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t nvsram3_default_cfg ( nvsram3_t *ctx ) 
{
    nvsram3_hardware_store( ctx, NVSRAM3_HSB_DISABLE );
    
    nvsram3_hw_write_protection( ctx, NVSRAM3_WP_DISABLE );
    
    return NVSRAM3_SUCCESS;
}

err_t nvsram3_generic_write ( nvsram3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) 
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t nvsram3_generic_read ( nvsram3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t nvsram3_send_cmd ( nvsram3_t *ctx, uint8_t cmd ) 
{
    ctx->slave_address = NVSRAM3_CONTROL_DEV_ADDR_0;
    
    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    return nvsram3_generic_write ( ctx, NVSRAM3_CONTROL_REG_CMD, &cmd, 1 ) ;;
}

err_t nvsram3_memory_write ( nvsram3_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t n_bytes ) 
{
    uint8_t tx_buf[ 258 ];
    uint8_t cnt;
    
    if ( n_bytes == 0 || mem_addr > LAST_MEMORY_ADDRESS ) 
    {
        return NVSRAM3_ERROR;
    }
    
    ctx->slave_address = NVSRAM3_MEMORY_DEV_ADDR_0 | ( ( mem_addr & ADDRESS_MSB ) >> 4 );
    
    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    tx_buf[ 0 ] = ( uint8_t )( mem_addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) mem_addr;

    for ( cnt = 0; cnt < n_bytes; cnt++ ) 
    {
        tx_buf[ cnt + 2 ] = data_in[ cnt ];
    }
        
    return i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 2 );
}

err_t nvsram3_memory_read ( nvsram3_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t n_bytes ) 
{
    uint8_t tx_buf[ 2 ];
    
    if ( n_bytes == 0 || mem_addr > LAST_MEMORY_ADDRESS ) 
    {
        return NVSRAM3_ERROR;
    }
    
    ctx->slave_address = NVSRAM3_MEMORY_DEV_ADDR_0 | ( ( mem_addr & ADDRESS_MSB ) >> 4 );
    
    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    tx_buf[ 0 ] = ( uint8_t )( mem_addr >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) mem_addr;
        
    return i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_out, n_bytes );
}

uint32_t nvsram3_get_device_id ( nvsram3_t *ctx ) 
{
    uint8_t temp[ 4 ];
    uint32_t device_id;
    
    ctx->slave_address = NVSRAM3_CONTROL_DEV_ADDR_0;
    
    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    nvsram3_generic_read( ctx, NVSRAM3_CONTROL_REG_DEVICE_ID, &temp[ 0 ], 1 );
    nvsram3_generic_read( ctx, NVSRAM3_CONTROL_REG_DEVICE_ID + 1, &temp[ 1 ], 1 );
    nvsram3_generic_read( ctx, NVSRAM3_CONTROL_REG_DEVICE_ID + 2, &temp[ 2 ], 1 );
    nvsram3_generic_read( ctx, NVSRAM3_CONTROL_REG_DEVICE_ID + 3, &temp[ 3 ], 1 );
    
    device_id = temp[ 0 ];
    device_id <<= 8;
    device_id |= temp[ 1 ];
    device_id <<= 8;
    device_id |= temp[ 2 ];
    device_id <<= 8;
    device_id |= temp[ 3 ];
    
    return device_id;
}

err_t nvsram3_rtc_read_reg ( nvsram3_t *ctx, uint8_t rtc_reg, uint8_t *data_out ) 
{
    uint8_t rx_data;
    
    if ( rtc_reg > BIT_MASK_LSN )
    {
        return NVSRAM3_ERROR;
    }
    
    ctx->slave_address = NVSRAM3_RTC_DEV_ADDR_0;
    
    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
        
    return i2c_master_write_then_read( &ctx->i2c, &rtc_reg, 1, data_out, 1 );
}

err_t nvsram3_rtc_write_reg ( nvsram3_t *ctx, uint8_t rtc_reg, uint8_t data_in ) 
{
    uint8_t tx_buf[ 2 ];
    
    if ( rtc_reg > BIT_MASK_LSN )
    {
        return NVSRAM3_ERROR;
    }
    
    ctx->slave_address = NVSRAM3_RTC_DEV_ADDR_0;
    
    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
     
    tx_buf[ 0 ] = rtc_reg;
    tx_buf[ 1 ] = data_in;
        
    return i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

void nvsram3_get_rtc_time ( nvsram3_t *ctx, nvsram3_rtc_time_t *rtc_time ) 
{
    uint8_t rx_data;

    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_READ_ENABLE );
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_SECONDS, &rx_data );
    rtc_time->sec = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_MINUTES, &rx_data );
    rtc_time->min = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_HOURS, &rx_data );
    rtc_time->hours = dev_bcd_to_dec( rx_data );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_READ_DISABLE );
}

err_t nvsram3_set_rtc_time ( nvsram3_t *ctx, nvsram3_rtc_time_t rtc_time ) 
{
    if ( ( rtc_time.sec > MAX_SEC ) || ( rtc_time.min > MAX_SEC ) || ( rtc_time.hours > MAX_HOUR ) ) 
    {
        return NVSRAM3_ERROR;
    } 
    
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_WRITE_ENABLE );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_SECONDS, dev_dec_to_bcd( rtc_time.sec ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_MINUTES, dev_dec_to_bcd( rtc_time.min ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_HOURS, dev_dec_to_bcd( rtc_time.hours ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_WRITE_DISABLE );
    
    return NVSRAM3_SUCCESS;
}

void nvsram3_get_rtc_date ( nvsram3_t *ctx, nvsram3_rtc_date_t *rtc_date ) 
{
    uint8_t rx_data;

    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_READ_ENABLE );
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_DAY, &rx_data );
    rtc_date->day_of_week = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_DATE, &rx_data );
    rtc_date->day = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_MONTHS, &rx_data );
    rtc_date->month = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_CENTURIES, &rx_data );
    rtc_date->year = dev_bcd_to_dec( rx_data ) * 100;
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_YEARS, &rx_data );
    rtc_date->year += dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_READ_DISABLE );
}

err_t nvsram3_set_rtc_date ( nvsram3_t *ctx, nvsram3_rtc_date_t rtc_date ) 
{
    uint8_t num_day;
    
    switch ( rtc_date.month ) 
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
        {
            num_day = 31;
            break;
        }
        case 3: case 6: case 9: case 11: 
        {
            num_day = 30;
            break;
        }
        case 2: 
        {
            if ( rtc_date.year % 4 == 0 ) 
            {
                num_day = 29; 
            }
            else
            {
                num_day = 28;
            }
            break;
        }
        default: break;
    }
    
    if ( ( rtc_date.day < 1 ) || 
         ( rtc_date.day > num_day ) || 
         ( rtc_date.month < 1 ) || 
         ( rtc_date.month > 12 ) ||
         ( rtc_date.year > 9999 ) )
    {
        return NVSRAM3_ERROR;    
    } 
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_WRITE_ENABLE );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_DAY, dev_dec_to_bcd( rtc_date.day_of_week ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_DATE, dev_dec_to_bcd( rtc_date.day ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_MONTHS, dev_dec_to_bcd( rtc_date.month ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_YEARS, dev_dec_to_bcd( ( uint8_t ) ( rtc_date.year % 100 ) ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_TIME_KEEPING_CENTURIES, dev_dec_to_bcd( ( uint8_t ) ( rtc_date.year / 100 ) ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_WRITE_DISABLE );
    
    return NVSRAM3_SUCCESS; 
}

void nvsram3_get_rtc_alarm ( nvsram3_t *ctx, nvsram3_rtc_alarm_t *rtc_alarm ) 
{
    uint8_t rx_data;

    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_READ_ENABLE );
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_ALARM_SECONDS, &rx_data );
    rtc_alarm->sec = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_ALARM_MINUTES, &rx_data );
    rtc_alarm->min = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_ALARM_HOURS, &rx_data );
    rtc_alarm->hours = dev_bcd_to_dec( rx_data );
    
    nvsram3_rtc_read_reg( ctx, NVSRAM3_RTC_REG_ALARM_DAY, &rx_data );
    rtc_alarm->day = dev_bcd_to_dec( rx_data );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_READ_DISABLE );
}

err_t nvsram3_set_rtc_alarm ( nvsram3_t *ctx, nvsram3_rtc_alarm_t rtc_alarm ) 
{
    if ( ( rtc_alarm.sec > MAX_SEC ) || 
         ( rtc_alarm.min > MAX_SEC ) || 
         ( rtc_alarm.hours > MAX_HOUR ) ||
         ( rtc_alarm.day > MAX_DAY ) ) 
    {
        return NVSRAM3_ERROR;
    } 
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_WRITE_ENABLE );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_ALARM_SECONDS, dev_dec_to_bcd( rtc_alarm.sec ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_ALARM_MINUTES, dev_dec_to_bcd( rtc_alarm.min ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_ALARM_HOURS, dev_dec_to_bcd( rtc_alarm.hours ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_ALARM_DAY, dev_dec_to_bcd( rtc_alarm.day ) );
    nvsram3_rtc_write_reg( ctx, NVSRAM3_RTC_REG_FLAGS, NVSRAM3_RTC_WRITE_DISABLE );
    
    return NVSRAM3_SUCCESS;
}

err_t nvsram3_hardware_store ( nvsram3_t *ctx, uint8_t state ) 
{
    if ( state == NVSRAM3_HSB_ENABLE ) 
    {
        digital_out_low( &ctx->hsb );
    } 
    else if ( state == NVSRAM3_HSB_DISABLE) 
    {
        digital_out_high( &ctx->hsb );
    } 
    else 
    {
        return NVSRAM3_ERROR;    
    }
    
    return NVSRAM3_SUCCESS;
}

err_t nvsram3_hw_write_protection ( nvsram3_t *ctx, uint8_t state ) 
{
    if ( state == NVSRAM3_WP_ENABLE ) 
    {
        digital_out_high( &ctx->wp );
    } 
    else if ( state == NVSRAM3_WP_DISABLE) 
    {
        digital_out_low( &ctx->wp );
    } 
    else 
    {
        return NVSRAM3_ERROR;    
    }
    
    return NVSRAM3_SUCCESS;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_dec_to_bcd ( uint8_t dec ) 
{
    return ( ( dec / 10 ) << 4 ) + ( dec % 10 );
}

static uint8_t dev_bcd_to_dec ( uint8_t bcd ) 
{
    return ( bcd & BIT_MASK_LSN ) + ( ( bcd >> 4 ) * 10 );
}

// ------------------------------------------------------------------------- END
