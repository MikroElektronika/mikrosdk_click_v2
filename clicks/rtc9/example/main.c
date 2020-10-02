/*!
 * \file 
 * \brief Rtc9 Click example
 * 
 * # Description
 * This demo application shows a real time.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Starts waking the chip and sets the start time and date
 * 
 * ## Application Task  
 * It reads current time and date and logs to usb uart every 1000 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc9.h"

// ------------------------------------------------------------------ VARIABLES

static rtc9_t rtc9;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void time_process ( )
{
    rtc9_get_time_t get_time;

    rtc9_get_time( &rtc9, &get_time );

    log_printf( &logger, "- Time [ %d h %d - min %d - s %d - ms ] \r\n", 
                         get_time.hour, get_time.min, get_time.sec, get_time.part_sec );
}

void date_process ( )
{
    rtc9_get_date_t get_date;

    char *week_string;
    char *month_string;

    rtc9_get_date( &rtc9, &get_date );

    week_string = rtc9_current_day_of_week( get_date.day_of_week );
    month_string = rtc9_current_month( get_date.month );

    log_printf( &logger, "- Date [ %d:%s:%s:%d Year ] \r\n", 
                         get_date.day, week_string, month_string, get_date.year + 2000 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc9_cfg_t cfg;
    rtc9_set_data_t set_data;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc9_cfg_setup( &cfg );
    RTC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc9_init( &rtc9, &cfg );

    Delay_ms( 500 );

    rtc9_wakeup( &rtc9 );

    rtc9_set_time( &rtc9, 12, 15, 45 );

    set_data.day = 20;
    set_data.day_of_week = RTC9_DAY_FRIDAY;
    set_data.month = RTC9_MONTH_MARCH;
    set_data.year = 20;
    rtc9_set_date ( &rtc9, &set_data );
}

void application_task ( void )
{
    time_process( );
    date_process( );
    
    log_printf( &logger, "---------------------------------------- \r\n" );
    Delay_ms( 1000 );
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
