/*!
 * \file 
 * \brief Rtc8 Click example
 * 
 * # Description
 * Demo application shows the operation of RTC 8 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * Sets new: Time, Date, UNIX time and alarm data.
 * 
 * ## Application Task  
 * Read current Time, Date and UNIX time and checks if the alarm is active.
 * 
 * *note:* 
 * Comment the lines for setting date and time if you would like the 
 * module to keep counting time after a reset or shut down.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc8.h"

// ------------------------------------------------------------------ VARIABLES

static rtc8_t rtc8;
static log_t logger;

static rtc8_time_t time_s;
static rtc8_date_t date_s;
static rtc8_alarm_t alarm_s;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc8_cfg_t cfg;

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

    rtc8_cfg_setup( &cfg );
    RTC8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc8_init( &rtc8, &cfg );

    rtc8_default_cfg( &rtc8 );

    // 24h format - HH,MM,SS

    time_s.hours = 23;
    time_s.minutes = 58;
    time_s.seconds = 30;

    rtc8_set_time( &rtc8, &time_s );

    // Set date format

    date_s.day = 31;
    date_s.month = 12;
    date_s.year = 18;

    rtc8_set_date( &rtc8, &date_s );

    // Set UNIX time

    rtc8_set_unix_time( &rtc8, 1545053360 );

    // Set alarm format

    alarm_s.weekdays = 3;
    alarm_s.hours = 0;
    alarm_s.minutes = 0;

    rtc8_set_alarm( &rtc8, &alarm_s );
    Delay_100ms();
}

void application_task ( void )
{
    uint8_t alarm;
    uint32_t unix_time;

    //  Task implementation.

    rtx8_get_time_and_date( &rtc8, &time_s, &date_s );
    unix_time = rtc8_get_uinx_time( &rtc8 );

    log_printf( &logger, "\r\n>> ----------------------------- <<\r\n" );

    log_printf( &logger, ">> Time : %d : %d : %d \r\n", time_s.hours, time_s.minutes, time_s.seconds );
    log_printf( &logger, ">> Weekday : %d \r\n", date_s.weekdays );
    log_printf( &logger, ">> Date : %d : %d : %d \r\n", date_s.day, date_s.month, date_s.year );
    log_printf( &logger, ">> UNIX : %ld \r\n", unix_time );

    alarm  = rtc8_get_alarm_flag( &rtc8 );

    if ( alarm == RTC8_ALARM_IS_ACTIVE )
    {
        log_printf( &logger, " - Alarm Active!!! " );
        rtc8_reset_alarm_flag( &rtc8 );
    }
    else
    {
        log_printf( &logger, " - No Alarm." );
    }

    Delay_ms(1000);
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
