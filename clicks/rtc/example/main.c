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

static rtc_c_t rtc_c;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc_c_cfg_t cfg;

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
    rtc_c_cfg_setup( &cfg );
    RTC_C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc_c_init( &rtc_c, &cfg );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "     RTC Click    \r\n" );
    log_printf( &logger, "------------------\r\n" );

    // Set Time: 23h, 59 min, 50 sec and 10 ms
    rtc_c.time.time_hours = 23;
    rtc_c.time.time_minutes = 59;
    rtc_c.time.time_seconds = 50;
    rtc_c.time.time_hun_sec = 10;

    rtc_c_set_time( &rtc_c );
    Delay_100ms( );
    
    // Start counting
    rtc_c_enable_disable_counting( &rtc_c, 1 );
    Delay_100ms( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t time_seconds_new = 0xFF;

    rtc_c_get_time( &rtc_c );

    if ( time_seconds_new != rtc_c.time.time_seconds )
    {
        log_printf( &logger, " Time : %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) rtc_c.time.time_hours, 
                    ( uint16_t ) rtc_c.time.time_minutes, 
                    ( uint16_t ) rtc_c.time.time_seconds );

        log_printf( &logger, "------------------\r\n" );

        time_seconds_new = rtc_c.time.time_seconds;
    }

    Delay_ms ( 500 );
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
