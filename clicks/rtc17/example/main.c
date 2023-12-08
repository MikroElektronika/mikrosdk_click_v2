/*!
 * @file main.c
 * @brief RTC17 Click example
 *
 * # Description
 * This example demonstrates the use of RTC 17 click board by reading and displaying
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
#include "rtc17.h"

static rtc17_t rtc17;
static log_t logger;
static rtc17_time_t time;
static rtc17_date_t date;

/**
 * @brief RTC 17 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static char *rtc17_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc17_cfg_t rtc17_cfg;  /**< Click config object. */

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
    rtc17_cfg_setup( &rtc17_cfg );
    RTC17_MAP_MIKROBUS( rtc17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc17_init( &rtc17, &rtc17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC17_ERROR == rtc17_default_cfg ( &rtc17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC17_OK == rtc17_set_time ( &rtc17, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC17_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC17_OK == rtc17_set_date ( &rtc17, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc17_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for interrupt which is synchronized with second count-up
    while ( rtc17_get_int_pin ( &rtc17 ) );
    
    rtc17_clear_interrupts ( &rtc17 );
    if ( RTC17_OK == rtc17_read_time ( &rtc17, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC17_OK == rtc17_read_date ( &rtc17, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n\n", 
                    rtc17_get_day_of_week_name ( date.day_of_week ),
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

static char *rtc17_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC17_MONDAY:
        {
            return "Monday";
        }
        case RTC17_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC17_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC17_THURSDAY:
        {
            return "Thursday";
        }
        case RTC17_FRIDAY:
        {
            return "Friday";
        }
        case RTC17_SATURDAY:
        {
            return "Saturday";
        }
        case RTC17_SUNDAY:
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
