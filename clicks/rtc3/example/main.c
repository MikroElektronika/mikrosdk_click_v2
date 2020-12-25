/*!
 * \file 
 * \brief Rtc3 Click example
 * 
 * # Description
 * This application enables time measurment over RTC3 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * set start time and date, enable counting and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of RTC 3 Click board.
 * RTC 3 Click communicates with register via I2C by write to register and read from register,
 * set time and date, get time and date, enable and disable counting
 * and set frequency by write configuration register.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 1 sec.
 * 
 * *note:* 
 * Time stats measuring correctly but from 0 seconds, after 10 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc3.h"

// ------------------------------------------------------------------ VARIABLES

static rtc3_t rtc3;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void display_log_day_of_the_week ( uint8_t day_of_the_week )
{
    if ( day_of_the_week == 1 )
    {
        log_printf( &logger, "      Monday      \r\n" );
    }        
    if ( day_of_the_week == 2 )
    {
        log_printf( &logger, "      Tuesday     \r\n" );
    }        
    if ( day_of_the_week == 3 )
    {
        log_printf( &logger, "     Wednesday    \r\n" );
    }        
    if ( day_of_the_week == 4 )
    {
        log_printf( &logger, "     Thursday     \r\n" );
    }        
    if ( day_of_the_week == 5 )
    {
        log_printf( &logger, "      Friday      \r\n" );
    }        
    if ( day_of_the_week == 6 )
    {
        log_printf( &logger, "     Saturday     \r\n" );
    }
    if ( day_of_the_week == 7 )
    {
        log_printf( &logger, "      Sunday      \r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc3_cfg_setup( &cfg );
    RTC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc3_init( &rtc3, &cfg );

    /// Set Time: 23h, 59 min, 50 sec

    rtc3.time.time_hours = 23;
    rtc3.time.time_minutes = 59;
    rtc3.time.time_seconds = 50;

    rtc3_set_time( &rtc3 );

    // Set Date: 1 ( Day of the week ), 31 ( day ), 12 ( month ) and 2018 ( year )

    rtc3.date.day_of_the_week = 1;
    rtc3.date.date_day = 31;
    rtc3.date.date_month = 12;
    rtc3.date.date_year = 2018;

    rtc3_set_date( &rtc3 );

    // Start counting
   
    rtc3_enable_disable_counting( &rtc3, 1 );
    Delay_100ms( );
    
    Delay_ms( 1000 );
}

void application_task ( void )
{
    //  Task implementation.

    uint8_t time_seconds_new = 0xFF;
    
     

    rtc3_get_time( &rtc3 );

    rtc3_get_date( &rtc3 );

    if ( time_seconds_new != rtc3.time.time_seconds )
    {
        if ( ( ( rtc3.time.time_hours | rtc3.time.time_minutes | rtc3.time.time_seconds ) == 0 )  && ( ( rtc3.date.date_day | rtc3.date.date_month ) == 1 ) )
        {
            log_printf( &logger, "  Happy New Year  \r\n" );
            log_printf( &logger, "------------------\r\n" );
        }

        log_printf( &logger, " Time : %d:%d:%d \r\n Date: %d.%d.20%d.\r\n------------------\r\n", (uint16_t)rtc3.time.time_hours, (uint16_t)rtc3.time.time_minutes,
                                                                                            (uint16_t)rtc3.time.time_seconds, 
                                                                                            (uint16_t)rtc3.date.date_day, (uint16_t)rtc3.date.date_month, (uint16_t)rtc3.date.date_year );

        time_seconds_new = rtc3.time.time_seconds;
    }

    Delay_ms( 200 );
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
