/*!
 * \file 
 * \brief RTC Click example
 * 
 * # Description
 * This application enables setup and measurement of time with RTC click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, set start time, enable counting and start write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of RTC Click board.
 * RTC Click communicates with register via I2C by write to register and read from register.
 * This example show time when the value of time_seconds is changed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "rtc.h"

static rtc_t rtc;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc_cfg_t cfg;

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
    rtc_cfg_setup( &cfg );
    RTC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc_init( &rtc, &cfg );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "     RTC Click    \r\n" );
    log_printf( &logger, "------------------\r\n" );

    // Set Time: 23h, 59 min, 50 sec and 10 ms
    rtc.time.time_hours = 23;
    rtc.time.time_minutes = 59;
    rtc.time.time_seconds = 50;
    rtc.time.time_hun_sec = 10;

    rtc_set_time( &rtc );
    Delay_100ms( );
    
    // Start counting
    rtc_enable_disable_counting( &rtc, 1 );
    Delay_100ms( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t time_seconds_new = 0xFF;

    rtc_get_time( &rtc );

    if ( time_seconds_new != rtc.time.time_seconds )
    {
        log_printf( &logger, " Time : %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) rtc.time.time_hours, 
                    ( uint16_t ) rtc.time.time_minutes, 
                    ( uint16_t ) rtc.time.time_seconds );

        log_printf( &logger, "------------------\r\n" );

        time_seconds_new = rtc.time.time_seconds;
    }

    Delay_ms( 500 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
