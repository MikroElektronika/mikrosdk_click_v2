/*!
 * \file 
 * \brief Rtc2 Click example
 * 
 * # Description
 * This application give time and date information.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 *  Initialization driver enable's - I2C,set start time and date, enable counting and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of RTC 2 Click board.
 *    RTC 2 Click communicates with register via I2C by write to register and read from register,
 *    set time and date, get time and date, enable and disable counting
 *    and set frequency by write configuration register.
 *    Results are being sent to the Usart Terminal where you can track their changes.
 *    All data logs write on usb uart changes for every 1 sec.
 * 
 * *note:* 
 * Additional Functions :
 *
 * - void displayDayOfTheWeek( uint8_t dayOfTheWeek ) - Write day of the week log on USART terminal.
 * - void displayLogUart( uint8_t value ) - Write the value ( time or date ) of a two-digit number.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc2.h"

// ------------------------------------------------------------------ VARIABLES

static rtc2_t rtc2;
static log_t logger;
static rtc2_data_t date;

uint8_t time_hours;
uint8_t time_minutes;
uint8_t time_seconds;
uint8_t day_of_the_week;
uint8_t date_day;
uint8_t date_month;
uint16_t date_year;
uint8_t time_seconds_new = 0;

void display_day_of_the_week ( uint8_t day_of_the_week )
{
    if ( day_of_the_week == 1 )
    {
        log_printf( &logger, "      Monday      " );
    }
    if ( day_of_the_week == 2 )
    {
        log_printf( &logger, "      Tuesday     " );
    }
    if ( day_of_the_week == 3 )
    {
        log_printf( &logger, "     Wednesday    " );
    }
    if ( day_of_the_week == 4 )
    {
        log_printf( &logger, "     Thursday     " );
    }
    if ( day_of_the_week == 5 )
    {
        log_printf( &logger, "      Friday      " );
    }
    if ( day_of_the_week == 6 )
    {
        log_printf( &logger, "     Saturday     " );
    }
    if ( day_of_the_week == 7 )
    {
        log_printf( &logger, "      Sunday      " );
    }
}

void display_log_uart ( uint8_t value )
{
   
    log_printf( &logger,"%u", ( uint16_t )( value / 10 ) );
    
    log_printf( &logger,"%u", ( uint16_t )( value % 10 ) );
}


void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc2_cfg_t cfg;
    
    date.day_of_the_week = 1;
    date.date_day = 31;
    date.date_month = 12;
    date.date_year = 2018;

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

    rtc2_cfg_setup( &cfg );
    RTC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc2_init( &rtc2, &cfg );

    rtc2_set_time( &rtc2, 23, 59, 50 );
    rtc2_set_date( &rtc2, &date );
    rtc2_enable_counting( &rtc2 );
}

void application_task ( void )
{
    rtc2_get_time( &rtc2, &time_hours, &time_minutes, &time_seconds );

    rtc2_get_date( &rtc2, &date );

    if ( time_seconds_new !=  time_seconds )
    {
        log_printf( &logger, " Time : " );

        display_log_uart( time_hours );
        log_printf( &logger, ":" );

        display_log_uart( time_minutes );
        log_printf( &logger, ":" );

        display_log_uart( time_seconds );
        log_printf( &logger, "" );

        display_day_of_the_week( date.day_of_the_week );

        log_printf( &logger, " Date: " );

        display_log_uart( date.date_day );
        log_printf( &logger, "." );

        display_log_uart( date.date_month );
        log_printf( &logger, "." );

        log_printf( &logger, "20" );

        display_log_uart( date.date_year );
        log_printf( &logger, ".\r\n" );

        log_printf( &logger, "-------------------\r\n" );

        time_seconds_new =  time_seconds;
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
