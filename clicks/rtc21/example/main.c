/*!
 * @file main.c
 * @brief RTC 21 Click example
 *
 * # Description
 * This example demonstrates the use of RTC 21 click board by reading and displaying
 * the time and date values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and then sets the starting time and date.
 *
 * ## Application Task
 * Reads and displays on the USB UART the current time and date values once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc21.h"

static rtc21_t rtc21;
static log_t logger;
static rtc21_time_t time;
static rtc21_date_t date;

/**
 * @brief RTC 21 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static uint8_t *rtc21_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc21_cfg_t rtc21_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    rtc21_cfg_setup( &rtc21_cfg );
    RTC21_MAP_MIKROBUS( rtc21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc21_init( &rtc21, &rtc21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC21_OK == rtc21_set_time ( &rtc21, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC21_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC21_OK == rtc21_set_date ( &rtc21, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc21_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( RTC21_OK == rtc21_read_time ( &rtc21, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC21_OK == rtc21_read_date ( &rtc21, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc21_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static uint8_t *rtc21_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC21_MONDAY:
        {
            return "Monday";
        }
        case RTC21_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC21_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC21_THURSDAY:
        {
            return "Thursday";
        }
        case RTC21_FRIDAY:
        {
            return "Friday";
        }
        case RTC21_SATURDAY:
        {
            return "Saturday";
        }
        case RTC21_SUNDAY:
        {
            return "Sunday";
        }
        default:
        {
            return "Unknown";
        }
    }
}

// ------------------------------------------------------------------------ END
