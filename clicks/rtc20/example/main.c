/*!
 * @file main.c
 * @brief RTC 20 Click example
 *
 * # Description
 * This example demonstrates the use of the RTC 20 click board™
 * by reading and displaying the RTC time and date values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module, log UART and additional pins.
 * After driver initialization the app set RTC time to 23:59:50
 * and set date to Tuesday 28.02.2023.
 *
 * ## Application Task
 * This is an example that shows the use of a RTC 20 Click board™.
 * In this example, we read and display the current time ( PM ) 
 * and date ( day of the week ), which we also previously set.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB changes every 1 sec.
 *
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc20.h"

static rtc20_t rtc20;
static log_t logger;
static uint8_t new_sec = 255;
static rtc20_time_t time;
static rtc20_date_t date;

/**
 * @brief RTC 20 display day of week name function.
 * @details This function display the name of day of the week.
 */
static void display_day_of_week ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc20_cfg_t rtc20_cfg;  /**< Click config object. */

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
    rtc20_cfg_setup( &rtc20_cfg );
    RTC20_MAP_MIKROBUS( rtc20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc20_init( &rtc20, &rtc20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    time.hour   = 23;
    time.minute = 59;
    time.second = 50;
    if ( RTC20_OK == rtc20_set_time( &rtc20, time ) )
    {
        log_printf( &logger, "  Set time : %.2d:%.2d:%.2d\r\n", 
                    ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
    }

    date.day_of_week = RTC20_DW_TUESDAY;
    date.day         = 28;
    date.month       = 2;
    date.year        = 23;
    if ( RTC20_OK == rtc20_set_date( &rtc20, date ) )
    {
        log_printf( &logger, "  Set date : %.2d-%.2d-%.2d\r\n", 
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    }

    Delay_ms( 1000 );
    log_printf( &logger, "---------------------\r\n" );
}

void application_task ( void ) 
{
    if ( RTC20_OK == rtc20_get_time( &rtc20, &time ) )
    {
        if ( RTC20_OK == rtc20_get_date( &rtc20, &date ) )
        {
            if ( time.second != new_sec )
            {
                log_printf( &logger, "  Date : %.2d-%.2d-%.2d\r\n", 
                            ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
                display_day_of_week( );
                log_printf( &logger, "  Time : %.2d:%.2d:%.2d\r\n", 
                            ( uint16_t ) time.hour, ( uint16_t ) time.minute, ( uint16_t ) time.second );
                log_printf( &logger, "- - - - - - - - - - -\r\n" );
                new_sec = time.second;
                Delay_ms( 1 );
            }
        }
    }
    Delay_ms( 1 );
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

static void display_day_of_week ( void ) 
{
    switch ( date.day_of_week ) 
    {
        case RTC20_DW_SUNDAY: 
        {
            log_printf( &logger, "Sunday\r\n" );
            break;
        }
        case RTC20_DW_MONDAY: 
        {
            log_printf( &logger, "Monday\r\n" );
            break;
        }
        case RTC20_DW_TUESDAY: 
        {
            log_printf( &logger, "Tuesday\r\n" );
            break;
        }
        case RTC20_DW_WEDNESDAY: 
        {
            log_printf( &logger, "Wednesday\r\n" );
            break;
        }
        case RTC20_DW_THURSDAY: 
        {
            log_printf( &logger, "Thursday\r\n" );
            break;
        }
        case RTC20_DW_FRIDAY: 
        {
            log_printf( &logger, "Friday\r\n" );
            break;
        }
        case RTC20_DW_SATURDAY: 
        {
            log_printf( &logger, "Saturday\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, "Unknown\r\n" );
        }
    }
}

// ------------------------------------------------------------------------ END
