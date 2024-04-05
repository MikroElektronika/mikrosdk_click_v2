/*!
 * @file main.c
 * @brief RTC13 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the RTC 13 click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module, log UART and additional pins.
 * After driver initialization and default settings,
 * the app set the time to 23:59:50 and set the date to 04.08.2021.
 *
 * ## Application Task
 * This is an example that shows the use of a RTC 13 click board™.
 * In this example, we read and display the current time and date, 
 * which we also previously set.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB changes every 1 sec.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc13.h"

static rtc13_t rtc13;
static log_t logger;

static uint8_t new_sec = 255;
static rtc13_time_t time;
static rtc13_date_t date;

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc13_cfg_t rtc13_cfg;  /**< Click config object. */

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

    rtc13_cfg_setup( &rtc13_cfg );
    RTC13_MAP_MIKROBUS( rtc13_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc13_init( &rtc13, &rtc13_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc13_default_cfg ( &rtc13 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    date.weekday = 3;
    date.day = 4;
    date.month = 8;
    date.year = 21;
    rtc13_set_date( &rtc13, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    rtc13_set_time( &rtc13, time );
    Delay_ms ( 100 );
}

void application_task ( void )
{  
    rtc13_get_time( &rtc13, &time );
    Delay_ms ( 1 );
    rtc13_get_date( &rtc13, &date );
    Delay_ms ( 1 );
    
    if ( time.sec != new_sec ) 
    {
        log_printf( &logger, "  Date      : %.2d-%.2d-%.2d\r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, "  Time      : %.2d:%.2d:%.2d\r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger, "- - - - - - - - - - - -\r\n" );
        new_sec = time.sec;
        Delay_ms ( 1 );
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

// ------------------------------------------------------------------------ END
