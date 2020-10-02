/*!
 * \file 
 * \brief Rtc10 Click example
 * 
 * # Description
 * This application is a real-time clock module.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * hardware reset, set start time and date, enable counting also, write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of RTC 10 Click board.
 * RTC 10 Click communicates with register via I2C interface,
 * set time and date, enable counting and display time and date values,
 * also, display temperature value for every 1 sec.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on Usart Terminal changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc10.h"

// ------------------------------------------------------------------ VARIABLES

static rtc10_t rtc10;
static log_t logger;

uint8_t sec_flag;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void display_day_of_the_week( uint8_t day_of_the_week )
{
    if ( day_of_the_week == 1 )
    {
        log_printf( &logger, "      Monday    \r\n\n " );
    }
    if ( day_of_the_week == 2 )
    {
        log_printf( &logger, "      Tuesday   \r\n\n " );
    }
    if ( day_of_the_week == 3 )
    {
        log_printf( &logger, "     Wednesday  \r\n\n " );
    }
    if ( day_of_the_week == 4 )
    {
        log_printf( &logger, "     Thursday   \r\n\n " );
    }
    if ( day_of_the_week == 5 )
    {
        log_printf( &logger, "      Friday    \r\n\n " );
    }
    if ( day_of_the_week == 6 )
    {
        log_printf( &logger, "     Saturday   \r\n\n " );
    }
    if ( day_of_the_week == 7 )
    {
        log_printf( &logger, "      Sunday    \r\n\n " );
    }        
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc10_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc10_cfg_setup( &cfg );
    RTC10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc10_init( &rtc10, &cfg );

    Delay_ms( 1000 );
    
    sec_flag = 0xFF;

    log_printf( &logger, "-------------------:%d \r\n" );
    log_printf( &logger, "  Hardware  Reset  :%d \r\n" );
    rtc10_hw_reset(  &rtc10 );
    Delay_ms( 1000 );

    // Set Time: 23h, 59 min and 50 sec
    rtc10_set_time(  &rtc10, 23, 59, 50 );
    Delay_ms( 10 );

    // Set Date: 6 ( Day of the week: Saturday ), 31 ( day ), 8 ( month ) and 2019 ( year )
    rtc10_set_date(  &rtc10,  6, 31, 8, 2019 );
    Delay_ms( 100 );

    log_printf( &logger, "------------------- :%d \r\n" );
    log_printf( &logger, "  Enable Counting :%d \r\n" );
    log_printf( &logger, "-------------------:%d \r\n" );
    log_printf( &logger, "     Start RTC     :%d \r\n" );
    log_printf( &logger, "-------------------:%d \r\n" );
    rtc10_enable_counting(  &rtc10 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t i;
    uint8_t time_hours;
    uint8_t time_minutes;
    uint8_t time_seconds;

    uint8_t day_of_the_week;
    uint8_t date_day;
    uint8_t date_month;
    uint8_t date_year;
    
    float temperature;
    
    rtc10_get_time( &rtc10, &time_hours, &time_minutes, &time_seconds );
    Delay_ms( 100 );

    rtc10_get_date( &rtc10, &day_of_the_week, &date_day, &date_month, &date_year );
    Delay_ms( 100 );

    if ( sec_flag !=  time_seconds )
    {
        log_printf( &logger, " \r\n\n Time: %d:%d:%d  Date: %d.%d.20%d. ", \
        time_hours, time_minutes, time_seconds, date_day, date_month, date_year );
        
        display_day_of_the_week( day_of_the_week );
        
        if ( time_seconds == 0 )
        {
            temperature = rtc10_get_temperature( &rtc10 );

            log_printf( &logger, "\r\n\n Temp.:%.2f C", temperature);
        }
        log_printf( &logger, "--------------------------------------------" );

        sec_flag =  time_seconds;
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
