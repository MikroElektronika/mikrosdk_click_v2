/*!
 * @file main.c
 * @brief Charger 16 Click Example.
 *
 * # Description
 * This library contains API for the Charger 16 Click driver.
 * This demo application shows use of a Charger 16 Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that shows the use of an Charger 16 Click board™.
 * The app turns the battery charge on and off every 10 seconds.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger16.h"

static charger16_t charger16;   /**< Charger 16 Click driver object. */
static log_t logger;            /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    charger16_cfg_t charger16_cfg;  /**< Click config object.  */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    charger16_cfg_setup( &charger16_cfg );
    CHARGER16_MAP_MIKROBUS( charger16_cfg, MIKROBUS_1 );
    if ( charger16_init( &charger16, &charger16_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    charger16_default_cfg ( &charger16 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Enable charging \r\n" );
    charger16_enable_charging( &charger16 );
    Delay_ms( 10000 );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, " Disable charging \r\n" );
    charger16_disable_charging( &charger16 );
    Delay_ms( 10000 );
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
