/*!
 * \file 
 * \brief Rtc3 Click example
 * 
 * # Description
 * This example demonstrates the use of RTC 3 click board by reading and displaying
 * the time and date values.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger and then sets the starting time and date.
 * 
 * ## Application Task  
 * Reads and displays on the USB UART the current time and date values once per second.
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
    if ( 1 == day_of_the_week )
    {
        log_printf( &logger, "      Monday      \r\n" );
    }        
    if ( 2 == day_of_the_week )
    {
        log_printf( &logger, "      Tuesday     \r\n" );
    }        
    if ( 3 == day_of_the_week )
    {
        log_printf( &logger, "     Wednesday    \r\n" );
    }        
    if ( 4 == day_of_the_week )
    {
        log_printf( &logger, "     Thursday     \r\n" );
    }        
    if ( 5 == day_of_the_week )
    {
        log_printf( &logger, "      Friday      \r\n" );
    }        
    if ( 6 == day_of_the_week )
    {
        log_printf( &logger, "     Saturday     \r\n" );
    }
    if ( 7 == day_of_the_week )
    {
        log_printf( &logger, "      Sunday      \r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc3_cfg_t cfg;

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

    //  Click initialization.
    rtc3_cfg_setup( &cfg );
    RTC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc3_init( &rtc3, &cfg );
    Delay_ms ( 100 );
    
    // Stop counting
    rtc3_set_counting( &rtc3, 0 );

    // Set Time: 23h, 59 min, 50 sec
    rtc3.time.time_hours = 23;
    rtc3.time.time_minutes = 59;
    rtc3.time.time_seconds = 50;

    rtc3_set_time( &rtc3 );

    // Set Date: 6 ( Day of the week ), 31 ( day ), 12 ( month ) and 2022 ( year )
    rtc3.date.day_of_the_week = 6;
    rtc3.date.date_day = 31;
    rtc3.date.date_month = 12;
    rtc3.date.date_year = 22;

    rtc3_set_date( &rtc3 );

    // Start counting
    rtc3_set_counting( &rtc3, 1 );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t time_seconds = 0xFF;

    rtc3_get_time( &rtc3 );

    rtc3_get_date( &rtc3 );

    if ( time_seconds != rtc3.time.time_seconds )
    {
        display_log_day_of_the_week ( rtc3.date.day_of_the_week );
        log_printf( &logger, " Time: %.2u:%.2u:%.2u\r\n Date: %.2u.%.2u.20%.2u.\r\n------------------\r\n", 
                    ( uint16_t ) rtc3.time.time_hours, ( uint16_t ) rtc3.time.time_minutes,
                    ( uint16_t ) rtc3.time.time_seconds, ( uint16_t ) rtc3.date.date_day, 
                    ( uint16_t ) rtc3.date.date_month, ( uint16_t ) rtc3.date.date_year );

        time_seconds = rtc3.time.time_seconds;
    }

    Delay_ms( 200 );
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
