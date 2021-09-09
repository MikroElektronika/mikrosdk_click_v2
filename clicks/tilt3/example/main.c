/*!
 * @file main.c
 * @brief Tilt 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of Tilt 3 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the tilt switch.
 *
 * ## Application Task
 * As soon as the tilt switch state changes, it displays a corresponding message on the USB UART.
 *
 * @note
 * Tilt switches OFF at an angle of 60 degrees minimum and 
 * switches ON at the horizontal position (up to 10 degrees).
 * The tilt LED will turn ON when the tilt switch is OFF. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tilt3.h"

static tilt3_t tilt3;       /**< Tilt 3 Click driver object. */
static log_t logger;        /**< Logger object. */

static uint8_t tilt3_switch_state = TILT3_SWITCH_OFF;

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    tilt3_cfg_t tilt3_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    tilt3_cfg_setup( &tilt3_cfg );
    TILT3_MAP_MIKROBUS( tilt3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt3_init( &tilt3, &tilt3_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    tilt3_enable_switch( &tilt3 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t state = tilt3_get_switch_state ( &tilt3 );
    if ( tilt3_switch_state != state )
    {
        tilt3_switch_state = state;
        
        if ( TILT3_SWITCH_ON == tilt3_switch_state )
        {
            log_printf( &logger, " Tilt switch ON!\r\n\n" );
        }
        else
        {
            log_printf( &logger, " Tilt switch OFF!\r\n\n" );
        }
        Delay_ms( 500 );
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
