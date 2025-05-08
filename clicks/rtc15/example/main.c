/*!
 * @file main.c
 * @brief RTC 15 Click example
 *
 * # Description
 * This example demonstrates the use of the RTC 15 Click board by initializing
 * the device and setting up the current time and date. It continuously
 * reads and displays the updated time and date every second using the timer
 * countdown interrupt pin.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the RTC 15 Click driver, applies the default configuration,
 * and sets the starting time and date.
 *
 * ## Application Task
 * Waits for a 1 Hz interrupt signal and then reads and displays the current time and date.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc15.h"

static rtc15_t rtc15;
static log_t logger;
static rtc15_time_t time;
static rtc15_date_t date;

/**
 * @brief RTC 15 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static uint8_t *rtc15_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc15_cfg_t rtc15_cfg;  /**< Click config object. */

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
    rtc15_cfg_setup( &rtc15_cfg );
    RTC15_MAP_MIKROBUS( rtc15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc15_init( &rtc15, &rtc15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC15_ERROR == rtc15_default_cfg ( &rtc15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC15_OK == rtc15_set_time ( &rtc15, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC15_TUESDAY;
    date.day = 31;
    date.month = 12;
    date.year = 24;
    if ( RTC15_OK == rtc15_set_date ( &rtc15, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc15_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for a timer countdown flag configured at 1 Hz
    while ( rtc15_get_int_pin ( &rtc15 ) );

    if ( RTC15_OK == rtc15_read_time ( &rtc15, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC15_OK == rtc15_read_date ( &rtc15, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc15_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 100 );
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

static uint8_t *rtc15_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC15_MONDAY:
        {
            return "Monday";
        }
        case RTC15_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC15_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC15_THURSDAY:
        {
            return "Thursday";
        }
        case RTC15_FRIDAY:
        {
            return "Friday";
        }
        case RTC15_SATURDAY:
        {
            return "Saturday";
        }
        case RTC15_SUNDAY:
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
