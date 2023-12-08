/*!
 * @file main.c
 * @brief RTC11 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the RTC 11 click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes SPI, performs software reset, sets 
 * system time and date, and starts clocking system.
 *
 * ## Application Task
 * Demonstrates use of RTC 11 click board by reading and
 * displaying time and date via USART terminal.
 * 
 * Additional Functions :
 * 
 * void disp_day_of_the_week ( uint8_t w_day ) - Writes the day of the week on 
 * USART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "rtc11.h"

static rtc11_t rtc11;
static log_t logger;

static rtc11_time_t time;
static rtc11_date_t date;

uint8_t sec_flag = 0xFF;

void disp_day_of_the_week ( uint8_t w_day ) {
    switch ( w_day )
    {
        case 0 :
        {
            log_printf( &logger, "Monday" );
            break;
        }
        case 1 :
        {
            log_printf( &logger, "Tuesday" );
            break;
        }
        case 2 :
        {
            log_printf( &logger, "Wednesday" );
            break;
        }
        case 3 :
        {
            log_printf( &logger, "Thursday" );
            break;
        }
        case 4 :
        {
            log_printf( &logger, "Friday" );
            break;
        }
        case 5 :
        {
            log_printf( &logger, "Saturday" );
            break;
        }
        case 6 :
        {
            log_printf( &logger, "Sunday" );
            break;
        }
        default :
        {
        break;
        }
    }
}
void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rtc11_cfg_t rtc11_cfg;  /**< Click config object. */

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

    rtc11_cfg_setup( &rtc11_cfg );
    RTC11_MAP_MIKROBUS( rtc11_cfg, MIKROBUS_1 );
    err_t init_flag  = rtc11_init( &rtc11, &rtc11_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Software reset \r\n" );
    rtc11_soft_rst( &rtc11 );
    Delay_ms( 100 );
    
    time.hours = 23;
    time.min = 59;
    time.sec = 55;
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Setting time: %.2d:%.2d:%.2d \r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
    rtc11_set_time ( &rtc11, time );
    Delay_ms( 100 );
    
    date.day_of_week = 0;
    date.day = 19;
    date.month = 7;
    date.year = 21;
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger," Setting date: %.2d/%.2d/%.2d \r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
    rtc11_set_date( &rtc11, date );
    Delay_ms( 100 );
    
    rtc11_stp_sys_slk ( &rtc11, RTC11_PROP_DIS );
    log_info( &logger, " Application Task " );
    log_printf( &logger,"------------------------\r\n" );
}

void application_task ( void ) {
    rtc11_get_time ( &rtc11, &time );
    Delay_ms( 10 );
    rtc11_get_date ( &rtc11, &date );
    Delay_ms( 10 );
    
    if ( sec_flag != time.sec ) {
        log_printf( &logger, " Date: " );
        disp_day_of_the_week( date.day_of_week );
        log_printf( &logger, " %.2d/%.2d/20%.2d \r\n", ( uint16_t ) date.day, ( uint16_t ) date.month, ( uint16_t ) date.year );
        log_printf( &logger, " Time: %.2d:%.2d:%.2d \r\n", ( uint16_t ) time.hours, ( uint16_t ) time.min, ( uint16_t ) time.sec );
        log_printf( &logger,"--------------------------\r\n" );
    }
    sec_flag = time.sec;
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
