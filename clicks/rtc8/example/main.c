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
 * Settings the Click in the default configuration.
 * Sets new: Time, Date, UNIX time and alarm data.
 * 
 * ## Application Task  
 * Read current Time, Date and UNIX time and checks if the alarm is active.
 * 
 * @note
 * Comment out the lines for setting date and time if you would like the 
 * module to keep counting time after a reset or shut down.
 * 
 * \author MikroE Team
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

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void display_weekday ( uint8_t weekday )
{
    switch ( weekday )
    {
        case 0: 
        {
            log_printf( &logger, "      Monday      \r\n" );
            break;
        }
        case 1: 
        {
            log_printf( &logger, "      Tuesday     \r\n" );
            break;
        }
        case 2: 
        {
            log_printf( &logger, "     Wednesday    \r\n" );
            break;
        }
        case 3: 
        {
            log_printf( &logger, "     Thursday     \r\n" );
            break;
        }
        case 4: 
        {
            log_printf( &logger, "      Friday      \r\n" );
            break;
        }
        case 5: 
        {
            log_printf( &logger, "     Saturday     \r\n" );
            break;
        }
        case 6: 
        {
            log_printf( &logger, "      Sunday      \r\n" );
            break;
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc8_cfg_t rtc8_cfg;

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
    rtc8_cfg_setup( &rtc8_cfg );
    RTC8_MAP_MIKROBUS( rtc8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rtc8_init( &rtc8, &rtc8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( RTC8_ERROR == rtc8_default_cfg ( &rtc8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    // 24h format - HH,MM,SS
    time_s.hours = 23;
    time_s.minutes = 59;
    time_s.seconds = 50;

    rtc8_set_time( &rtc8, &time_s );

    // Set date format
    date_s.weekdays = 5;
    date_s.day = 31;
    date_s.month = 12;
    date_s.year = 22;

    rtc8_set_date( &rtc8, &date_s );

    // Set UNIX time
    rtc8_set_unix_time( &rtc8, 1672527590ul );

    // Set alarm format
    alarm_s.weekdays = 6;
    alarm_s.hours = 0;
    alarm_s.minutes = 0;

    rtc8_set_alarm( &rtc8, &alarm_s );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t time_seconds = 0xFF;
    uint8_t alarm = 0;
    uint32_t unix_time = 0;
    
    err_t error_flag = rtx8_get_time_and_date( &rtc8, &time_s, &date_s );
    error_flag |= rtc8_get_uinx_time( &rtc8, &unix_time );
    error_flag |= rtc8_get_alarm_flag( &rtc8, &alarm );

    if ( ( RTC8_OK == error_flag ) && ( time_seconds != time_s.seconds ) )
    {
        display_weekday ( date_s.weekdays );
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n Date: %.2u.%.2u.20%.2u.\r\n", 
                    ( uint16_t ) time_s.hours, ( uint16_t ) time_s.minutes,
                    ( uint16_t ) time_s.seconds, ( uint16_t ) date_s.day, 
                    ( uint16_t ) date_s.month, ( uint16_t ) date_s.year );
        log_printf( &logger, " UNIX: %lu\r\n", unix_time );
        if ( RTC8_ALARM_IS_ACTIVE == alarm )
        {
            log_info( &logger, " Alarm Activated!!! " );
            rtc8_reset_alarm_flag( &rtc8 );
        }
        log_printf( &logger, "------------------\r\n" );
        time_seconds = time_s.seconds;
    }
    Delay_ms ( 200 );
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
