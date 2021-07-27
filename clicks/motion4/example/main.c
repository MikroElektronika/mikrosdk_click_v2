/*!
 * @file main.c
 * @brief Motion 4 Click Example.
 * 
 * # Description
 * This example demonstrates the use of Motion 4 click boards.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the motion sensor.
 *
 * ## Application Task
 * It checks if the sensor has detected movement and therefore displays 
 * the desired message on the USB UART.
 *
 * @author Jelena Milosavljevic
 *
 */
// ------------------------------------------------------------------- INCLUDES
#include "board.h"
#include "log.h"
#include "motion4.h"

// ------------------------------------------------------------------ VARIABLES

static motion4_t motion4;   /**< Motion 4 Click driver object. */
static log_t logger;    /**< Logger object. */

motion4_detect_state_t motion_state;
motion4_detect_state_t motion_old_state;
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    motion4_cfg_t motion4_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    motion4_cfg_setup( &motion4_cfg );
    MOTION4_MAP_MIKROBUS( motion4_cfg, MIKROBUS_1 );
    if ( motion4_init( &motion4, &motion4_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
       
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    motion4_enable( &motion4, MOTION4_MODULE_ENABLE );
    Delay_ms( 100 );
    log_printf( &logger, "The sensor is ready.\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void ) {
    uint8_t int_status;

    int_status = motion4_detect_state( &motion4 );

    if ( int_status == MOTION4_DETECT_OBJECT ) {
        
        log_printf( &logger, "Motion detected!\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        while ( int_status == MOTION4_DETECT_OBJECT ) {
           
            int_status = motion4_detect_state( &motion4 );
        }
        log_printf( &logger, "The sensor is ready.\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms( 100 );
    }
}


void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
