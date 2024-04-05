/*!
 * @file main.c
 * @brief RTC18 Click example
 *
 * # Description
 * This example demonstrates the use of RTC 18 click board by reading and displaying
 * the time and date values as well as the temperature measurements in Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration
 * which enables the periodic interrupt on seconds count-up, and sets the starting time and date.
 *
 * ## Application Task
 * Waits for the second count-up interrupt and then reads and displays on the USB UART 
 * the current time and date values as well as the temperature measurements in Celsius.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc18.h"

static rtc18_t rtc18;
static log_t logger;
static rtc18_time_t time;
static rtc18_date_t date;

/**
 * @brief RTC 18 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc18_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static char *rtc18_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc18_cfg_t rtc18_cfg;  /**< Click config object. */

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
    rtc18_cfg_setup( &rtc18_cfg );
    RTC18_MAP_MIKROBUS( rtc18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc18_init( &rtc18, &rtc18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC18_ERROR == rtc18_default_cfg ( &rtc18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC18_OK == rtc18_set_time ( &rtc18, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC18_SATURDAY;
    date.day = 31;
    date.month = 12;
    date.year = 22;
    if ( RTC18_OK == rtc18_set_date ( &rtc18, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc18_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature;
    
    // Wait for a second count-up interrupt
    while ( rtc18_get_int_pin ( &rtc18 ) );
    
    Delay_ms ( 10 );
    rtc18_clear_periodic_interrupt ( &rtc18 );
    
    if ( RTC18_OK == rtc18_read_time ( &rtc18, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC18_OK == rtc18_read_date ( &rtc18, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc18_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    if ( RTC18_OK == rtc18_read_temperature ( &rtc18, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
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

static char *rtc18_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC18_MONDAY:
        {
            return "Monday";
        }
        case RTC18_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC18_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC18_THURSDAY:
        {
            return "Thursday";
        }
        case RTC18_FRIDAY:
        {
            return "Friday";
        }
        case RTC18_SATURDAY:
        {
            return "Saturday";
        }
        case RTC18_SUNDAY:
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
