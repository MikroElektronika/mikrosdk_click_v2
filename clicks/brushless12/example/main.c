/*!
 * @file main.c
 * @brief Brushless 12 Click Example.
 *
 * # Description
 * This example demonstrates the use of Brushless 12 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the click default configuration.
 *
 * ## Application Task
 * Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
 * and after that drives it in the reverse direction for 5 seconds, and pulls brake for 2 seconds.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless12.h"

static brushless12_t brushless12;       /**< Brushless 12 Click driver object. */
static log_t logger;                    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    brushless12_cfg_t brushless12_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    brushless12_cfg_setup( &brushless12_cfg );
    BRUSHLESS12_MAP_MIKROBUS( brushless12_cfg, MIKROBUS_1 );
    
    if ( brushless12_init( &brushless12, &brushless12_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    brushless12_default_cfg( &brushless12 );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    brushless12_set_direction ( &brushless12, BRUSHLESS12_DIR_FORWARD );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_START );
    Delay_ms( 5000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_BRAKE );
    Delay_ms( 2000 );
    
    log_printf( &logger, "The motor turns in reverse! \r\n" );
    brushless12_set_direction ( &brushless12, BRUSHLESS12_DIR_REVERSE );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_START );
    Delay_ms( 5000 );
    
    log_printf( &logger, "Pull brake! \r\n" );
    brushless12_set_brake ( &brushless12, BRUSHLESS12_BRAKE );
    Delay_ms( 2000 );
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
