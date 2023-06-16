/*!
 * \file 
 * \brief RTC7 Click example
 * 
 * # Description
 * This app is used to accurately measure time with low power consumption.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Waits for a second count-up interrupt and then reads and logs the current
 * time and date on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtc7.h"

// ------------------------------------------------------------------ VARIABLES

static rtc7_t rtc7;
static log_t logger;

rtc7_time_t time_set;
rtc7_time_t time_date;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void rtc7_display_results ( rtc7_t *ctx )
{
    log_printf( &logger, " %.2u:%.2u:%.2u\r\n", 
                ( uint16_t ) time_date.hours, ( uint16_t ) time_date.minutes, ( uint16_t ) time_date.seconds );

    log_printf( &logger, " %.2u/%.2u/%.2u ", 
                ( uint16_t ) time_date.monthday, ( uint16_t ) time_date.month, ( uint16_t ) time_date.year );
    switch ( time_date.weekdays )
    {
        case 1:
        {
            log_printf( &logger, "MONDAY" );
            break;
        }
        case 2:
        {
            log_printf( &logger, "TUESDAY" );
            break;
        }
        case 3:
        {
            log_printf( &logger, "WEDNESDAY" );
            break;
        }
        case 4:
        {
            log_printf( &logger, "THURSDAY" );
            break;
        }
        case 5:
        {
            log_printf( &logger, "FRIDAY" );
            break;
        }
        case 6:
        {
            log_printf( &logger, "SATURDAY" );
            break;
        }
        case 7:
        {
            log_printf( &logger, "SUNDAY" );
            break;
        }
        default:
        {
            break;
        }
    }
    log_printf( &logger, "\r\n-------------------\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtc7_cfg_t cfg;

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
    rtc7_cfg_setup( &cfg );
    RTC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc7_init( &rtc7, &cfg );
    Delay_ms( 300 );
    
    time_set.seconds = 40;
    time_set.minutes = 59;
    time_set.hours = 23;
    time_set.weekdays = 1;
    time_set.monthday = 31;
    time_set.month = 12;
    time_set.year = 22;
    
    err_t error_flag = rtc7_reset( &rtc7 );
    error_flag |= rtc7_init_time ( &rtc7, 0 );
    error_flag |= rtc7_set_gmt_time( &rtc7, &time_set );
    error_flag |= rtc7_set_osc( &rtc7, RTC7_ENABLE_OSC, RTC7_INPUT_FREQ_32768HZ, RTC7_OUTPUT_FREQ_32768HZ );
    error_flag |= rtc7_write_reg( &rtc7, RTC7_TIMER_INIT_REG, 15 );
    error_flag |= rtc7_set_timer( &rtc7, RTC7_TIMER_EN, RTC7_TIMER_FREQ_16HZ );
    Delay_ms( 100 );
    if ( RTC7_ERROR == error_flag )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    // Wait for timer count-down interrupt which is set to 1Hz
    while ( rtc7_check_interrupt ( &rtc7 ) );

    // Clear interrupt status
    uint8_t int_status = 0;
    rtc7_read_reg( &rtc7, RTC7_INT_STATUS_REG, &int_status, 1 );
    
    // Read time
    if ( RTC7_OK == rtc7_get_local_time( &rtc7, &time_date ) )
    {
        // Display time
        rtc7_display_results( &rtc7 );
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
