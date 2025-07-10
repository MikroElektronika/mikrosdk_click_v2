/*!
 * @file main.c
 * @brief RTC 24 Click example
 *
 * # Description
 * This example demonstrates the use of the RTC 24 Click board by initializing
 * the device and setting up the current time and date. It continuously
 * reads and displays the updated time and date every second using the square wave pin.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the RTC 24 Click driver, applies the default configuration,
 * and sets the starting time and date.
 *
 * ## Application Task
 * Waits for a 1 Hz square wave signal and then reads and displays the current time and date.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc24.h"

static rtc24_t rtc24;
static log_t logger;
static rtc24_time_t time;
static rtc24_date_t date;

/**
 * @brief RTC 24 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static uint8_t *rtc24_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc24_cfg_t rtc24_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 124200
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
    rtc24_cfg_setup( &rtc24_cfg );
    RTC24_MAP_MIKROBUS( rtc24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc24_init( &rtc24, &rtc24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC24_ERROR == rtc24_default_cfg ( &rtc24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC24_OK == rtc24_set_time ( &rtc24, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC24_TUESDAY;
    date.day = 31;
    date.month = 12;
    date.year = 24;
    if ( RTC24_OK == rtc24_set_date ( &rtc24, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc24_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for a square wave output configured at 1 Hz
    while ( rtc24_get_sqw_pin ( &rtc24 ) );
    while ( !rtc24_get_sqw_pin ( &rtc24 ) );

    if ( RTC24_OK == rtc24_read_time ( &rtc24, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC24_OK == rtc24_read_date ( &rtc24, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc24_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static uint8_t *rtc24_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC24_MONDAY:
        {
            return "Monday";
        }
        case RTC24_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC24_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC24_THURSDAY:
        {
            return "Thursday";
        }
        case RTC24_FRIDAY:
        {
            return "Friday";
        }
        case RTC24_SATURDAY:
        {
            return "Saturday";
        }
        case RTC24_SUNDAY:
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
