/*!
 * @file main.c
 * @brief RTC 19 Click example
 *
 * # Description
 * This example demonstrates the use of RTC 19 click board by reading and displaying
 * the time and date values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration
 * which resets the device and sets the timer interrupt to 1 Hz. 
 * After that, it sets the starting time and date.
 *
 * ## Application Task
 * Waits for a timer countdown interrupt (1 Hz) and then reads and displays on the USB UART 
 * the current time and date values.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc19.h"

static rtc19_t rtc19;
static log_t logger;
static rtc19_time_t time;
static rtc19_date_t date;

/**
 * @brief RTC 19 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc19_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static char *rtc19_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc19_cfg_t rtc19_cfg;  /**< Click config object. */

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
    rtc19_cfg_setup( &rtc19_cfg );
    RTC19_MAP_MIKROBUS( rtc19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc19_init( &rtc19, &rtc19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC19_ERROR == rtc19_default_cfg ( &rtc19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC19_OK == rtc19_set_time ( &rtc19, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC19_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC19_OK == rtc19_set_date ( &rtc19, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc19_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for a timer countdown flag configured at 1 Hz
    while ( rtc19_get_inta_pin ( &rtc19 ) );

    Delay_ms ( 100 );
    rtc19_clear_interrupts ( &rtc19 );
    if ( RTC19_OK == rtc19_read_time ( &rtc19, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC19_OK == rtc19_read_date ( &rtc19, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc19_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static char *rtc19_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC19_MONDAY:
        {
            return "Monday";
        }
        case RTC19_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC19_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC19_THURSDAY:
        {
            return "Thursday";
        }
        case RTC19_FRIDAY:
        {
            return "Friday";
        }
        case RTC19_SATURDAY:
        {
            return "Saturday";
        }
        case RTC19_SUNDAY:
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
