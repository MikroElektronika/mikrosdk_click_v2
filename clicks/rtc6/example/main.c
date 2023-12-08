/*!
 * \file 
 * \brief Rtc6 Click example
 * 
 * # Description
 * This application enables usage of Real-TIme clock and calendar with alarm on RTC 6 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, sets time zone, sets UTC-GMT time and alarm time
 * 
 * ## Application Task  
 * Reads GMT time and Local time. Checks if the alarm is activated. 
 * If the alarm is active, it disable alarm and adjusts the new one within 20 seconds.
 * Logs this data on USBUART every 900ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc6.h"

// ------------------------------------------------------------------ VARIABLES

static rtc6_t rtc6;
static log_t logger;
static rtc6_time_t utc_time;
static rtc6_time_t alarm_time;
static rtc6_time_t local_time;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc6_cfg_t cfg;
    int8_t time_zone = 2;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc6_cfg_setup( &cfg );
    RTC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc6_init( &rtc6, &cfg );

    // Set UTC time

    utc_time.seconds  = 40;
    utc_time.minutes  = 59;
    utc_time.hours    = 23;
    utc_time.monthday = 14;
    utc_time.month    = 12;
    utc_time.year     = 18;
    
    // Set alarm time
    
    alarm_time.seconds  = 0;
    alarm_time.minutes  = 0;
    alarm_time.hours    = 0;
    alarm_time.weekdays  = 0;
    alarm_time.monthday = 15;
    alarm_time.month    = 12;
    alarm_time.year     = 18;

    rtc6_default_cfg( &rtc6, time_zone, &utc_time, &alarm_time );
    log_info( &logger, " ----- Init successfully ----- " );
    Delay_ms( 2000 );
}

void application_task ( void )
{
    //  Task implementation.

    rtc6_get_gmt_time( &rtc6, &utc_time );
    rtc6_get_local_time( &rtc6, &local_time );
    
    log_printf( &logger, "--- UTC time ---\r\nTime : %u %u %u\r\n", ( uint16_t )utc_time.hours, ( uint16_t )utc_time.minutes, ( uint16_t )utc_time.seconds );
    
    log_printf( &logger, "Date : %u %u %u\r\n", ( uint16_t )utc_time.monthday, ( uint16_t )utc_time.month, utc_time.year );
    
    log_printf( &logger, "--- Local time ---\r\nTime : %u %u %u\r\n", ( uint16_t )local_time.hours, ( uint16_t )local_time.minutes, ( uint16_t )local_time.seconds );

    log_printf( &logger, "Date : %u %u %u\r\n \r\n", ( uint16_t )local_time.monthday, ( uint16_t )local_time.month, local_time.year );
    
    if ( rtc6_is_active_alarm( &rtc6 ) != 0 )
    {
        log_printf( &logger, " ----- Active alarm ----- \r\n" );
        rtc6_disable_alarm( &rtc6, RTC6_ALARM_0 );
        rtc6_repeat_alarm( &rtc6, RTC6_ALARM_0, 20 );
    }

    Delay_ms( 900 );
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
