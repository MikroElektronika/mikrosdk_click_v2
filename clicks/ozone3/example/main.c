/*!
 * @file main.c
 * @brief Ozone3 Click example
 *
 * # Description
 * This library contains API for the Ozone 3 click driver.
 * This demo application shows an example of the O3 ppm data measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that shows the use of a Ozone 3 click board™.
 * Get and logs O3 ( Trioxygen ) data as ppm value.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ozone3.h"

static ozone3_t ozone3;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;        /**< Logger config object. */
    ozone3_cfg_t ozone3_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ozone3_cfg_setup( &ozone3_cfg );
    OZONE3_MAP_MIKROBUS( ozone3_cfg, MIKROBUS_1 );
    err_t init_flag = ozone3_init( &ozone3, &ozone3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ozone3_default_cfg ( &ozone3 );
    log_info( &logger, " Application Task " );
    Delay_ms( 300 );
}

void application_task ( void ) {
    float o3_ppm = ozone3_get_o3_ppm( &ozone3 );
    log_printf( &logger, "\tOzone : %.2f ppm \r\n", o3_ppm );
    Delay_ms( 500 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
