/*!
 * @file main.c
 * @brief RTC 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of the RTC 4 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and then sets the starting time 
 * to 23:59:50 and date to 31.12.2022.
 *
 * ## Application Task
 * With the usage of rtc4_get_date_time we get the time and 
 * date from the register and display them on the UART Terminal. 
 * The counter increments once per second. 
 *
 * @author Aleksandra Cvjetićanin
 *
 */

#include "board.h"
#include "log.h"
#include "rtc4.h"

static rtc4_t rtc4;
static log_t logger;

rtc4_time_t time; 
rtc4_date_t date; 

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc4_cfg_t rtc4_cfg;  /**< Click config object. */

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
    rtc4_cfg_setup( &rtc4_cfg );
    RTC4_MAP_MIKROBUS( rtc4_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == rtc4_init( &rtc4, &rtc4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RTC4_ERROR == rtc4_check_communication ( &rtc4 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    time.hours = 23;
    time.min = 59; 
    time.sec = 50; 
    
    date.day = 31;
    date.month = 12; 
    date.year = 2022; 
    
    rtc4_set_date_time ( &rtc4, &date, &time, RTC4_DCB_INTERVAL_1S ); 
    
    log_info( &logger, " Application Task " );
}    

void application_task ( void ) 
{
    while ( rtc4_get_interrupt ( &rtc4 ) ); 
    
    if ( RTC4_OK == rtc4_get_date_time ( &rtc4, &date, &time ) ) 
    {
        log_printf( &logger, "Time: %.2u:%.2u:%.2u\r\n", 
                    ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec ); 
        log_printf( &logger, "Date: %.2u/%.2u/%u\r\n", 
                    ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year ); 
        log_printf( &logger, "------------------------\r\n\n"); 
    }
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
