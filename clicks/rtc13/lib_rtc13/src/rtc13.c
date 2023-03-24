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
 * @file rtc13.c
 * @brief RTC 13 Click Driver.
 */

#include "rtc13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define BIT_MASK_SUBADDRESS        0x10
#define BIT_MASK_DATA_WRITE        0x00
#define BIT_MASK_DATA_READ         0x80
#define BIT_MASK_REG_ADDR_RANGE    0x0F
#define DUMMY                      0x00
#define BIT_MASK_LSN               0x0F
#define MAX_MIN_SEC                  59
#define MAX_HOUR                     23
#define MAX_DAY                      31
#define BIT_MASK_TIME_REV_BIT      0x7F
#define BIT_MASK_ALARM_ENABLE      0x80

/**
 * @brief Decimal to RTC.
 * @details Decimal to RTC converter function.
 */
static uint8_t dev_dec_to_rtc ( uint8_t dec );

/**
 * @brief RTC to decimal.
 * @details RTC to decimal converter function.
 */
static uint8_t dev_rtc_to_dec ( uint8_t bcd );

void rtc13_cfg_setup ( rtc13_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->cle = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
}

err_t rtc13_init ( rtc13_t *ctx, rtc13_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->cle, cfg->cle );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

err_t rtc13_default_cfg ( rtc13_t *ctx ) 
{
    rtc13_block_clkout( ctx, RTC13_BLOCK_CLKOUT_DISABLE );
    
    return RTC13_OK;
}

uint8_t rtc13_get_interrupt ( rtc13_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

err_t rtc13_block_clkout ( rtc13_t *ctx, uint8_t en_clkout ) 
{
    if ( en_clkout == RTC13_BLOCK_CLKOUT_ENABLE )
    {
        digital_out_high( &ctx->cle );    
    }
    else
    {
        digital_out_low( &ctx->cle );
    }

    return RTC13_OK;
}

err_t rtc13_generic_write ( rtc13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] &= BIT_MASK_REG_ADDR_RANGE;
    tx_buf[ 0 ] |= BIT_MASK_DATA_WRITE;
    tx_buf[ 0 ] |= BIT_MASK_SUBADDRESS;
    
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t rtc13_generic_read ( rtc13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    reg &= BIT_MASK_REG_ADDR_RANGE;
    reg |= BIT_MASK_SUBADDRESS;
    reg |= BIT_MASK_DATA_READ;
       
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t rtc13_soft_reset ( rtc13_t *ctx ) 
{
    uint8_t tx_buf;
    
    tx_buf = RTC13_SOFT_RESET;
    err_t err_flag = rtc13_generic_write( ctx, RTC13_REG_CTRL1_ADDR, &tx_buf, 1 );

    return err_flag;
}

err_t rtc13_get_time ( rtc13_t *ctx, rtc13_time_t *rtc_time ) 
{
    uint8_t rx_data;

    err_t error_flag = rtc13_generic_read( ctx, RTC13_REG_TIME_SECONDS, &rx_data, 1 );
    rtc_time->sec = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc13_generic_read( ctx, RTC13_REG_TIME_MINUTES, &rx_data, 1 );
    rtc_time->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc13_generic_read( ctx, RTC13_REG_TIME_HOUR, &rx_data, 1 );
    rtc_time->hours = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc13_set_time ( rtc13_t *ctx, rtc13_time_t rtc_time ) 
{
    uint8_t tx_buf[ 1 ];
    err_t error_flag;
    
    if ( ( rtc_time.sec > MAX_MIN_SEC ) || 
         ( rtc_time.min > MAX_MIN_SEC ) || 
         ( rtc_time.hours > MAX_HOUR ) ) 
    {
        error_flag = RTC13_ERROR;
    } 
    else 
    {
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.sec );
        error_flag = rtc13_generic_write( ctx, RTC13_REG_TIME_SECONDS, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.min ); 
        error_flag |= rtc13_generic_write( ctx, RTC13_REG_TIME_MINUTES, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.hours ); 
        error_flag |= rtc13_generic_write( ctx, RTC13_REG_TIME_HOUR, tx_buf, 1 );
    }
    
    return error_flag;
}

err_t rtc13_get_date ( rtc13_t *ctx, rtc13_date_t *rtc_date ) 
{
    uint8_t rx_data;

    err_t error_flag = rtc13_generic_read( ctx, RTC13_REG_DATE_WEEKDAYS, &rx_data, 1 );
    rtc_date->weekday = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc13_generic_read( ctx, RTC13_REG_DATE_DAY, &rx_data, 1 );
    rtc_date->day = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc13_generic_read( ctx, RTC13_REG_DATE_MONTHS, &rx_data, 1 );
    rtc_date->month = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc13_generic_read( ctx, RTC13_REG_DATE_YEARS, &rx_data, 1 );
    rtc_date->year = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc13_set_date ( rtc13_t *ctx, rtc13_date_t rtc_date ) 
{
    uint8_t num_day;
    err_t error_flag;
    uint8_t tx_buf[ 1 ];
    
    error_flag = RTC13_ERROR;
    
    switch ( rtc_date.month ) 
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
        {
            num_day = 31;
            break;
        }
        case 4: case 6: case 9: case 11: 
        {
            num_day = 30;
            break;
        }
        case 2: 
        {
            num_day = 28;
            break;
        }
    }
    
    if ( ( rtc_date.year % 4 == 0 ) && ( num_day == 28 ) ) 
    {
        num_day = 29; 
    }
    
    if ( ( rtc_date.day < 1 )       || 
         ( num_day < rtc_date.day ) || 
         ( rtc_date.month < 1 )     || 
         ( rtc_date.month > 12 ) ) {
        error_flag = RTC13_ERROR;    
    } 
    else 
    {
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.weekday ); 
        error_flag = rtc13_generic_write( ctx, RTC13_REG_DATE_WEEKDAYS, tx_buf, 1 );
        
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.day ); 
        error_flag |= rtc13_generic_write( ctx, RTC13_REG_DATE_DAY, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.month );
        error_flag |= rtc13_generic_write( ctx, RTC13_REG_DATE_MONTHS, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.year );
        error_flag |= rtc13_generic_write( ctx, RTC13_REG_DATE_YEARS, tx_buf, 1 );
    }
    
    return error_flag; 
}

err_t rtc13_get_alarm ( rtc13_t *ctx, rtc13_alarm_t *rtc_alarm ) 
{
    uint8_t rx_data;
    
    err_t error_flag = rtc13_generic_read( ctx, RTC13_REG_ALARM_MINUTE, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc13_generic_read( ctx, RTC13_REG_ALARM_HOUR, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->hours = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc13_generic_read( ctx, RTC13_REG_ALARM_DAY, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->day = dev_rtc_to_dec( rx_data );
    
    error_flag = rtc13_generic_read( ctx, RTC13_REG_ALARM_WEEKDAY, &rx_data, 1 );
    rtc_alarm->weekday = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc13_set_alarm ( rtc13_t *ctx, rtc13_alarm_t rtc_alarm ) 
{
    uint8_t tx_buf[ 1 ];
    err_t error_flag;
    
    error_flag = RTC13_OK;
    
    if ( ( rtc_alarm.min > MAX_MIN_SEC ) || 
         ( rtc_alarm.hours > MAX_HOUR )  ||
         ( rtc_alarm.day > MAX_DAY ) ) 
    {
        error_flag = RTC13_ERROR;
    } 
    else 
    {
        if ( rtc_alarm.min > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.min );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc13_generic_write( ctx, RTC13_REG_ALARM_MINUTE, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.hours > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.hours );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc13_generic_write( ctx, RTC13_REG_ALARM_HOUR, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.day > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.day );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc13_generic_write( ctx, RTC13_REG_ALARM_DAY, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.weekday > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.weekday );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc13_generic_write( ctx, RTC13_REG_ALARM_WEEKDAY, tx_buf, 1 );    
        }
    }
    
    return error_flag;
}

static uint8_t dev_dec_to_rtc ( uint8_t dec ) 
{
    return ( ( dec / 10 ) << 4 ) + ( dec % 10 );
}

static uint8_t dev_rtc_to_dec ( uint8_t bcd ) 
{
    return ( bcd & BIT_MASK_LSN ) + ( ( bcd >> 4 ) * 10 );
}


// ------------------------------------------------------------------------- END
