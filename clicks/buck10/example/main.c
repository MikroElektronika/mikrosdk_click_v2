/*!
 * @file main.c
 * @brief Buck 10 Click Example.
 *
 * # Description
 *  Demo application shows basic usage of Buck 10 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 *  Configuring clicks and log objects.
 *  Settings the click in the default configuration.
 * 
 * ## Application Task  
 *  Enable and Disable device every 5 seconds.
 *
 * @note
 *  Input voltage recommended range - from 4V to 18V
 *  Low-side valley current limit - from 3A to 3.9A
 *  Low-side negative current limit - (-2.5A)
 *  Output voltage - 3.3V or 5V
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "buck10.h"

static buck10_t buck10;   /**< Buck 10 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck10_cfg_t buck10_cfg;  /**< Click config object. */

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

    buck10_cfg_setup( &buck10_cfg );
    BUCK10_MAP_MIKROBUS( buck10_cfg, MIKROBUS_1 );
    if ( buck10_init( &buck10, &buck10_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    buck10_set_device_mode ( &buck10, BUCK10_DEVICE_ENABLE );
    log_printf(&logger, "Output:\t ENABLED\r\n");
    Delay_ms( 5000 );
    buck10_set_device_mode ( &buck10, BUCK10_DEVICE_DISABLE );
    log_printf(&logger, "Output:\t DISABLED\r\n");
    Delay_ms( 5000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
