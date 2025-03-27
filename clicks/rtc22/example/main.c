/*!
 * @file main.c
 * @brief RTC 22 Click example
 *
 * # Description
 * This example demonstrates the use of RTC 22 Click board by reading and displaying
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
#include "rtc22.h"

static rtc22_t rtc22;
static log_t logger;
static rtc22_time_t time;
static rtc22_date_t date;

/**
 * @brief RTC 22 get day of week name function.
 * @details This function returns the name of day of the week as a string.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] day_of_week : Day of week decimal value.
 * @return Name of day as a string.
 * @note None.
 */
static uint8_t *rtc22_get_day_of_week_name ( uint8_t day_of_week );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc22_cfg_t rtc22_cfg;  /**< Click config object. */

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
    rtc22_cfg_setup( &rtc22_cfg );
    RTC22_MAP_MIKROBUS( rtc22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc22_init( &rtc22, &rtc22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC22_ERROR == rtc22_check_communication ( &rtc22 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }

    time.hour = 23;
    time.minute = 59;
    time.second = 50;
    time.second_100th = 0;
    if ( RTC22_OK == rtc22_set_time ( &rtc22, &time ) )
    {
        log_printf( &logger, " Set time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    date.day_of_week = RTC22_TUESDAY;
    date.day = 31;
    date.month = 12;
    date.year = 24;
    if ( RTC22_OK == rtc22_set_date ( &rtc22, &date ) )
    {
        log_printf( &logger, " Set date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc22_get_day_of_week_name ( date.day_of_week ),
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( RTC22_OK == rtc22_read_time ( &rtc22, &time ) )
    {
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }
    if ( RTC22_OK == rtc22_read_date ( &rtc22, &date ) )
    {
        log_printf( &logger, " Date: %s, %.2u.%.2u.20%.2u.\r\n", 
                    rtc22_get_day_of_week_name ( date.day_of_week ),
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

static uint8_t *rtc22_get_day_of_week_name ( uint8_t day_of_week )
{
    switch ( day_of_week )
    {
        case RTC22_MONDAY:
        {
            return "Monday";
        }
        case RTC22_TUESDAY:
        {
            return "Tuesday";
        }
        case RTC22_WEDNESDAY:
        {
            return "Wednesday";
        }
        case RTC22_THURSDAY:
        {
            return "Thursday";
        }
        case RTC22_FRIDAY:
        {
            return "Friday";
        }
        case RTC22_SATURDAY:
        {
            return "Saturday";
        }
        case RTC22_SUNDAY:
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
