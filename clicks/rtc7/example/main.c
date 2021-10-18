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
 * Waits until device be stable and logs time after each second.
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
uint8_t check_change;
uint8_t check_year;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void rtc7_display_results ( rtc7_t *ctx )
{
    log_printf( &logger, "%d : %d : %d ", time_date.hours, time_date.minutes, time_date.seconds );

    if ( ( ctx->rtc7_am_pm & 0x02 ) != 0 )
    {
        if ( ( ctx->rtc7_am_pm & 0x01 ) == 0 )
        {
            log_printf( &logger, " AM \r\n" );
        }
        else
        {
            log_printf( &logger, " PM \r\n" );
        }
    }
    else
    {
        log_printf( &logger, " " );
    }

    switch ( time_date.weekdays )
    {
        case 1 :
        {
            log_printf( &logger, "MONDAY" );
            break;
        }
        case 2 :
        {
            log_printf( &logger, "TUESDAY" );
            break;
        }
        case 3 :
        {
            log_printf( &logger, "WEDNESDAY" );
            break;
        }
        case 4 :
        {
            log_printf( &logger, "THURSDAY" );
            break;
        }
        case 5 :
        {
            log_printf( &logger, "FRIDAY" );
            break;
        }
        case 6 :
        {
            log_printf( &logger, "SATURDAY" );
            break;
        }
        case 7 :
        {
            log_printf( &logger, "SUNDAY" );
            break;
        }
        default :
        {
        break;
        }
    }

    log_printf( &logger, "  %d / %d / %d \r\n", time_date.monthday, time_date.month, time_date.year );
    log_printf( &logger, "---------------------------\r\n" );
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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtc7_cfg_setup( &cfg );
    RTC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtc7_init( &rtc7, &cfg );
    
    Delay_ms( 300 );

    time_set.seconds = 40;
    time_set.minutes = 59;
    time_set.hours = 1;
    time_set.weekdays = 1;
    time_set.monthday = 1;
    time_set.month = 1;
    time_set.year = 18;
    
    check_change = 0;
    check_year = 0;
    
    rtc7_reset( &rtc7 );
    rtc7_disable_dst( &rtc7 );
    rtc7_init_time ( &rtc7, -2, RTC7_12HR_FORMAT );
    rtc7_set_gmt_time( &rtc7, &time_set );
    log_printf( &logger, "RTC 7 is initialized \r\n" );
    Delay_ms( 1000 );
    rtc7_set_osc( &rtc7, RTC7_ENABLE_OSC, RTC7_INPUT_FREQ_32768HZ, RTC7_OUTPUT_FREQ_32768HZ );
    rtc7_set_timer( &rtc7, RTC7_TIMER_EN, RTC7_TIMER_FREQ_16HZ );

}

void application_task ( void )
{
    rtc7_get_local_time( &rtc7, &time_date );
    
    if ( check_year == 0 )
    {
        log_printf( &logger, "Wait... \r\n" );
        while ( ( time_date.year != time_set.year ) && ( time_date.year != ( time_set.year + 1 ) ) && ( time_date.year != ( time_set.year - 1 ) ) )
        {
            rtc7_get_local_time( &rtc7, &time_date );
        }
        check_year = 1;
    }
    
    if ( check_change != time_date.seconds )
    {
        rtc7_display_results( &rtc7 );
        check_change = time_date.seconds;
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
