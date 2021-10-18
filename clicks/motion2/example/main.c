/*!
 * @file main.c
 * @brief Motion 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Motion 2 click boards.
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
#include "motion2.h"

// ------------------------------------------------------------------ VARIABLES

static motion2_t motion2;   /**< Motion 2 Click driver object. */
static log_t logger;    /**< Logger object. */


motion2_detect_state_t motion_state;
motion2_detect_state_t motion_old_state;
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
   
    log_cfg_t log_cfg;  /**< Logger config object. */
    motion2_cfg_t motion2_cfg;  /**< Click config object. */

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
    log_info( &logger, "---- Application Init ----" );

    // Click initialization.

    motion2_cfg_setup( &motion2_cfg );
    MOTION2_MAP_MIKROBUS( motion2_cfg, MIKROBUS_1 );
    if ( motion2_init( &motion2, &motion2_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
       
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    motion2_enable( &motion2, MOTION2_MODULE_ENABLE );
    Delay_ms( 100 );
    log_printf( &logger, "The sensor is ready.\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void ) {  
    uint8_t int_status;

    int_status = motion2_detect_state( &motion2 );

    if ( int_status == MOTION2_DETECT_OBJECT ) {
        log_printf( &logger, "Motion detected!\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        while ( int_status == MOTION2_DETECT_OBJECT ) {
            int_status = motion2_detect_state( &motion2 );
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
