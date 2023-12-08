/*!
 * @file main.c
 * @brief RTC14 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the RTC 14 click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module, log UART and additional pins.
 * After driver initialization and default settings,
 * the app set the time to 11:59:50 PM ( 12-hour format ) 
 * and set date to Thursday 05.08.2021.
 *
 * ## Application Task
 * This is an example that shows the use of a RTC 14 click board™.
 * In this example, we read and display the current time ( AM or PM ) 
 * and date ( day of the week ), which we also previously set.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB changes every 1 sec.
 *
 * ## Additional Function
 * - static void display_day_of_week ( void ) - The function displays the day of the week.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc14.h"

static rtc14_t rtc14;
static log_t logger;
static uint8_t new_sec = 255;
static rtc14_time_t time;
static rtc14_date_t date;

static void display_day_of_week ( void ) 
{
    switch ( date.day_of_week ) 
    {
        case RTC14_DW_SUNDAY: 
        {
            log_printf( &logger, "Su\r\n" );
            break;
        }
        case RTC14_DW_MONDAY: 
        {
            log_printf( &logger, "Mo\r\n" );
            break;
        }
        case RTC14_DW_TUESDAY: 
        {
            log_printf( &logger, "Tu\r\n" );
            break;
        }
        case RTC14_DW_WEDNESDAY: 
        {
            log_printf( &logger, "We\r\n" );
            break;
        }
        case RTC14_DW_THURSDAY: 
        {
            log_printf( &logger, "Th\r\n" );
            break;
        }
        case RTC14_DW_FRIDAY: 
        {
            log_printf( &logger, "Fr\r\n" );
            break;
        }
        case RTC14_DW_SATURDAY: 
        {
            log_printf( &logger, "Sa\r\n" );
            break;
        }
    }
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc14_cfg_t rtc14_cfg;  /**< Click config object. */

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
    rtc14_cfg_setup( &rtc14_cfg );
    RTC14_MAP_MIKROBUS( rtc14_cfg, MIKROBUS_1 );
    err_t init_flag = rtc14_init( &rtc14, &rtc14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc14_default_cfg ( &rtc14 );
    Delay_ms( 100 );
    
    time.hours_format = RTC14_SET_HOURS_FORMAT_12;
    time.am_pm = RTC14_SET_HOURS_FORMAT_12_PM;
    time.hours = 11;
    time.min = 59;
    time.sec = 50;
    rtc14_set_time( &rtc14, time );
    Delay_ms( 100 );
    
    date.day_of_week = RTC14_DW_THURSDAY;
    date.day = 5;
    date.month = 8;
    date.year = 21;
    rtc14_set_date( &rtc14, date );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
}

void application_task ( void ) 
{    
    rtc14_get_time( &rtc14, &time );
    Delay_ms( 1 );
    rtc14_get_date( &rtc14, &date );
    Delay_ms( 1 );
    
    if ( time.sec != new_sec ) 
    {       
        log_printf( &logger, "  Date : %.2d-%.2d-%.2d ", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        display_day_of_week( );
        log_printf( &logger, "  Time : %.2d:%.2d:%.2d ", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "%cM\r\n", ( time.am_pm == RTC14_SET_HOURS_FORMAT_12_PM ? 'P' : 'A' ) );
        log_printf( &logger, "- - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        Delay_ms( 1 );
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

// ------------------------------------------------------------------------ END
