/*!
 * @file main.c
 * @brief Headphone AMP 3 Click Example.
 *
 * # Description
 * This library contains API for the Headphone AMP 3 Click driver.
 * This demo application shows use of a Headphone AMP 3 Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This example demonstrates the use of the Headphone AMP 3 Click board™.
 * The app is enabling and disabling headphone output by changing ENA pin state every 10 seconds. 
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "headphoneamp3.h"

static headphoneamp3_t headphoneamp3;   /**< Headphone AMP 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    headphoneamp3_cfg_t headphoneamp3_cfg;  /**< Click config object. */

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
    headphoneamp3_cfg_setup( &headphoneamp3_cfg );
    HEADPHONEAMP3_MAP_MIKROBUS( headphoneamp3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == headphoneamp3_init( &headphoneamp3, &headphoneamp3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    headphoneamp3_default_cfg ( &headphoneamp3 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Enabling headphone output \r\n" );
    headphoneamp3_enable_amp( &headphoneamp3, HEADPHONEAMP3_ENABLE );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Disabling headphone output \r\n" );
    headphoneamp3_enable_amp( &headphoneamp3, HEADPHONEAMP3_DISABLE );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
