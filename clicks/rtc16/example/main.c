/*!
 * @file main.c
 * @brief RTC16 Click example
 *
 * # Description
 * This example demonstrates the use of RTC 16 click board by reading and displaying
 * the time and date values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration
 * which sets 24h time mode and interrupt to be synchronized with second count-up.
 * And after that setting the starting time and date.
 *
 * ## Application Task
 * Waits for the second count-up interrupt and then reads and displays the current
 * time and date values on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc16.h"

static rtc16_t rtc16;
static log_t logger;
static rtc16_time_t time;
static rtc16_date_t date;

/**
 * @brief RTC 16 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc16_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static char *rtc16_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc16_cfg_t rtc16_cfg;  /**< Click config object. */

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
    rtc16_cfg_setup( &rtc16_cfg );
    RTC16_MAP_MIKROBUS( rtc16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc16_init( &rtc16, &rtc16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC16_ERROR == rtc16_default_cfg ( &rtc16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC16_OK == rtc16_set_time ( &rtc16, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC16_SUNDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC16_OK == rtc16_set_date ( &rtc16, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc16_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for interrupt which is synchronized with second count-up
    while ( rtc16_get_int_pin ( &rtc16 ) );
    
    rtc16_clear_interrupts ( &rtc16 );
    if ( RTC16_OK == rtc16_read_time ( &rtc16, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC16_OK == rtc16_read_date ( &rtc16, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc16_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static char *rtc16_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC16_MONDAY:
        {
            return "Monday";
        }
        case RTC16_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC16_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC16_THURSDAY:
        {
            return "Thursday";
        }
        case RTC16_FRIDAY:
        {
            return "Friday";
        }
        case RTC16_SATURDAY:
        {
            return "Saturday";
        }
        case RTC16_SUNDAY:
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
