/*!
 * @file main.c
 * @brief RTC 23 Click example
 *
 * # Description
 * This example demonstrates the use of RTC 23 Click board by reading and displaying
 * the time and date values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, checks the communication, and sets the starting time and date.
 *
 * ## Application Task
 * Reads and displays on the USB UART the current time and date values once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc23.h"

static rtc23_t rtc23;
static log_t logger;
static rtc23_time_t time;
static rtc23_date_t date;

/**
 * @brief RTC 23 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc23_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static uint8_t *rtc23_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc23_cfg_t rtc23_cfg;  /**< Click config object. */

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
    rtc23_cfg_setup( &rtc23_cfg );
    RTC23_MAP_MIKROBUS( rtc23_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == rtc23_init( &rtc23, &rtc23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC23_ERROR == rtc23_check_communication ( &rtc23 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    time.second_100th = 0;
    if ( RTC23_OK == rtc23_set_time ( &rtc23, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC23_TUESDAY;
    date.day = 31;
    date.month = 12;
    date.year = 24;
    if ( RTC23_OK == rtc23_set_date ( &rtc23, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc23_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( RTC23_OK == rtc23_read_time ( &rtc23, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC23_OK == rtc23_read_date ( &rtc23, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc23_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 1000 );
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

static uint8_t *rtc23_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC23_MONDAY:
        {
            return "Monday";
        }
        case RTC23_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC23_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC23_THURSDAY:
        {
            return "Thursday";
        }
        case RTC23_FRIDAY:
        {
            return "Friday";
        }
        case RTC23_SATURDAY:
        {
            return "Saturday";
        }
        case RTC23_SUNDAY:
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
