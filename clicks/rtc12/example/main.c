/*!
 * @file main.c
 * @brief Rtc12 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the RTC 12 Click board™.
 * 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module, log UART and additional pins.
 * After driver initialization and default settings,
 * the app set the time to 23:59:50 and set the date to 27.05.'21.
 *
 * ## Application Task
 * This is an example that shows the use of a RTC 12 Click board™.
 * In this example, we read and display the current time and date, 
 * which we also previously set.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB changes every 1 sec.
 *
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc12.h"

static rtc12_t rtc12;
static log_t logger;

static uint8_t new_sec = 255;
static rtc12_time_t time;
static rtc12_date_t date;


void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    rtc12_cfg_t rtc12_cfg;   /**< Click config object. */

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

    rtc12_cfg_setup( &rtc12_cfg );
    RTC12_MAP_MIKROBUS( rtc12_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc12_init( &rtc12, &rtc12_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    rtc12_default_cfg ( &rtc12 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    date.day_of_week = 4;
    date.day = 27;
    date.month = 5;
    date.year = 21;
    rtc12_set_date( &rtc12, date );
    Delay_ms ( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 50;
    rtc12_set_time( &rtc12, time );
    Delay_ms ( 100 );
}

void application_task ( void ) {   
    rtc12_get_time( &rtc12, &time );
    Delay_ms ( 1 );
    rtc12_get_date( &rtc12, &date );
    Delay_ms ( 1 );
    
    if ( time.sec != new_sec ) {
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
