/*!
 * @file main.c
 * @brief Watchdog Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the Watchdog Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - GPIO, configure the watchdog window,
 * enable watchdog, also write log.
 *
 * ## Application Task
 * In the first part of the example,
 * we send pulses in a valid time window (Correct Operation).
 * The second part of the example sends pulses outside the valid time window
 * and then the watchdog detects a fault condition, display "Fault",
 * performs the reset and turn on the LED ( WDT FLT ) on the Watchdog Click board.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "watchdog.h"

static watchdog_t watchdog;   /**< Watchdog Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    watchdog_cfg_t watchdog_cfg;  /**< Click config object. */

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
    watchdog_cfg_setup( &watchdog_cfg );
    WATCHDOG_MAP_MIKROBUS( watchdog_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == watchdog_init( &watchdog, &watchdog_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    watchdog_default_cfg ( &watchdog );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Configure of the  \r\n" );
    log_printf( &logger, "   watchdog window   \r\n" );
    watchdog_setup_time( &watchdog, WATCHDOG_SETUP_TIME_MODE_2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Watchdog enabled  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, "  Correct Operation  \r\n" );
    uint8_t n_cnt = 40;
    while ( n_cnt > 0 ) {
        watchdog_send_pulse( &watchdog, 1 );
        Delay_ms ( 50 );
        n_cnt--;
    }
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "        Fault        \r\n" );
    n_cnt = 8;
    while ( n_cnt > 0 ) {
        watchdog_send_pulse( &watchdog, 1 );
        Delay_ms ( 250 );
        n_cnt--;
    }
    log_printf( &logger, "---------------------\r\n" );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
