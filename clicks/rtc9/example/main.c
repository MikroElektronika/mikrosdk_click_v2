/*!
 * \file 
 * \brief Rtc9 Click example
 * 
 * # Description
 * This example demonstrates the use of RTC 9 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, wakes up the module, and sets the time and date.
 * 
 * ## Application Task  
 * Reads the current time and date and displays the results on the USB UART each second.
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
static uint8_t seconds_old = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc9_cfg_t cfg;
    rtc9_set_data_t set_data;

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

    rtc9_cfg_setup( &cfg );
    RTC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc9_init( &rtc9, &cfg );

    Delay_ms( 500 );

    rtc9_wakeup( &rtc9 );

    rtc9_set_time( &rtc9, 23, 59, 50 );

    set_data.day = 22;
    set_data.day_of_week = RTC9_DAY_MONDAY;
    set_data.month = RTC9_MONTH_MARCH;
    set_data.year = 21;
    rtc9_set_date ( &rtc9, &set_data );
    
    rtc9_wakeup( &rtc9 );
}

void application_task ( void )
{
    rtc9_get_time_t get_time;
    rtc9_get_date_t get_date;

    char *week_string;
    char *month_string;

    rtc9_get_time( &rtc9, &get_time );
    rtc9_get_date( &rtc9, &get_date );
    
    if ( get_time.sec != seconds_old )
    {
        seconds_old = get_time.sec;
        log_printf( &logger, "- Time [ %.2u:%.2u:%.2u ] \r\n", ( uint16_t ) get_time.hour, 
                                                               ( uint16_t ) get_time.min, 
                                                               ( uint16_t ) get_time.sec );

        week_string = rtc9_current_day_of_week( get_date.day_of_week );
        month_string = rtc9_current_month( get_date.month );

        log_printf( &logger, "- Date [ %s, %s %.2u, %u ] \r\n", week_string, month_string, 
                                                               ( uint16_t ) get_date.day, 
                                                               ( uint16_t ) get_date.year + 2000 );
        log_printf( &logger, "---------------------------------------- \r\n" );
    }
    Delay_ms( 10 );
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
