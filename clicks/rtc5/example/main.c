/*!
 * \file 
 * \brief Rtc5 Click example
 * 
 * # Description
 * This is a example which demonstrates the use of RTC 5 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO, SPI and LOG structures, sets CS pin as output and INT pin as input.
 * Initialization driver enable's - SPI, clear RTCC and SRAM memory, 
 * sets starting time and date, enable counting and start write log.
 * 
 * ## Application Task  
 * RTC 5 Click communicates with register via SPI 
 * by write to register and read from register, display RTC time and date.
 * 
 * *note:* 
 *  Additional Functions: 
 * void display_log_day_of_the_week( uint8_t w_day ) - Write day of the week log.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc5.h"

// ------------------------------------------------------------------ VARIABLES

static rtc5_t rtc5;
static log_t logger;

static uint8_t time_sec_new;
rtc5_timedate_t time_date_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void display_log_day_of_the_week ( uint8_t w_day )
{
    switch ( w_day )
    {
        case RTC5_DAY_OF_THE_WEEK_MONDAY:
        {
            log_printf( &logger, " ~~~  Monday  ~~~\r\n" );
            break;
        }
        case RTC5_DAY_OF_THE_WEEK_TUESDAY:
        {
            log_printf( &logger, " ~~~  Tuesday  ~~~\r\n" );
            break;
        }
        case RTC5_DAY_OF_THE_WEEK_WEDNESDAY:
        {
            log_printf( &logger, " ~~~ Wednesday  ~~~\r\n" );
            break;
        }
        case RTC5_DAY_OF_THE_WEEK_THURSDAY:
        {
            log_printf( &logger, " ~~~ Thursday  ~~~\r\n" );
            break;
        }
        case RTC5_DAY_OF_THE_WEEK_FRIDAY:
        {
            log_printf( &logger, " ~~~  Friday  ~~~\r\n" );
            break;
        }
        case RTC5_DAY_OF_THE_WEEK_SATURDAY:
        {
            log_printf( &logger, " ~~~ Saturday  ~~~\r\n" );
            break;
        }
        case RTC5_DAY_OF_THE_WEEK_SUNDAY:
        {
            log_printf( &logger, "  ~~~  Sunday  ~~~\r\n" );
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc5_cfg_setup( &cfg );
    RTC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc5_init( &rtc5, &cfg );
    
    rtc5_default_cfg ( &rtc5);
    Delay_ms( 100 );
    
    rtc5_clear( &rtc5 );
    Delay_ms( 100 );
    
    time_sec_new = 255;

    // Set Time: 17h, 59 min and 50 sec
    rtc5_set_time( &rtc5, 23, 59, 50 );
    
    // Set Day of the week : Wednesday
    rtc5_set_day_of_the_week( &rtc5, RTC5_DAY_OF_THE_WEEK_TUESDAY );
    
    // Set Date: 31 ( day ), 12 ( month ) and 2019 ( year )
    rtc5_set_date( &rtc5, 31, 12, 2019 );
    
    // Start counting
    rtc5_set_counting( &rtc5, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    RTC 5  Click    \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    
}

void application_task ( void )
{
    rtc5_get_time_and_date( &rtc5, &time_date_data );
    
    if ( time_sec_new != time_date_data.sec )
    {
        log_printf( &logger, " Time : %d:%d:%d\r\n", (uint16_t)time_date_data.hours, (uint16_t)time_date_data.min, (uint16_t)time_date_data.sec );
    
        display_log_day_of_the_week( time_date_data.w_day );
    
        log_printf( &logger, " Date : %d.%d.%d.\r\n", (uint16_t)time_date_data.day, (uint16_t)time_date_data.month, (uint16_t)time_date_data.year );
        log_printf( &logger, "--------------------\r\n" );
    
        time_sec_new = time_date_data.sec;
    }
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
