/*!
 * @file main.c
 * @brief Buck 9 Click Example.
 *
 * # Description
 * Demo application shows basic usage of Buck 9 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Enable and Disable device every 5 seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "buck9.h"

static buck9_t buck9;   /**< Buck 9 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck9_cfg_t buck9_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    buck9_cfg_setup( &buck9_cfg );
    BUCK9_MAP_MIKROBUS( buck9_cfg, MIKROBUS_1 );
    if ( buck9_init( &buck9, &buck9_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    buck9_set_device_mode ( &buck9, BUCK9_DEVICE_ENABLE );
    log_printf(&logger, "Output:\t ENABLED\r\n");
    Delay_ms( 5000 );
    buck9_set_device_mode ( &buck9, BUCK9_DEVICE_DISABLE );
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
