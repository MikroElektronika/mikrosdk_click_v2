/*!
 * @file main.c
 * @brief SolidSwitch 8 Click Example.
 *
 * # Description
 * This example demonstrates the use of SolidSwitch 8 Click board by 
 * switching state of the switch.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration.
 *
 * ## Application Task
 * Switching state of the output every 5 seconds, 
 * and monitoring the status of the device.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch8.h"

static solidswitch8_t solidswitch8;   /**< SolidSwitch 8 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch8_cfg_t solidswitch8_cfg;  /**< Click config object. */

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
    solidswitch8_cfg_setup( &solidswitch8_cfg );
    SOLIDSWITCH8_MAP_MIKROBUS( solidswitch8_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == solidswitch8_init( &solidswitch8, &solidswitch8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    solidswitch8_default_cfg ( &solidswitch8 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( SOLIDSWITCH8_PIN_STATE_LOW == solidswitch8_get_sts_pin( &solidswitch8 ) )
    {
        solidswitch8_set_err_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_HIGH );
        log_error( &logger, " Detected over temperature condition." );
        for ( ; ; );
    }

    log_printf( &logger, " Switch state closed. \r\n" );
    solidswitch8_set_in_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Switch state open. \r\n" );
    solidswitch8_set_in_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_LOW );
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
