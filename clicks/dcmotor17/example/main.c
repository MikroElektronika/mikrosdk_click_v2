/*!
 * @file main.c
 * @brief DC Motor 17 Click Example.
 *
 * # Description
 * The library covers all the necessary functions to control DC Motor 17 Click board. 
 * Library performs a standard GPIO interface communication.
 * DC Motor 17 Click board is a dual H Bridge driver IC for one or two DC brushed
 * motors which incorporates DMOS with low on-resistance in output transistors. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes GPIO driver, set default configuration and start to write log.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the DC Motor 17 click board.
 * This example demonstrates the use of DC Motor 17 click,
 * we first control motion A by driving it forward motion for 5 seconds, 
 * than applying short brakes it for 2 second, then driving it in reverse for 5 seconds
 * and stop the motor for 2 seconds.
 * In the second part of the example, we control motion B by the same principle.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor17.h"

static dcmotor17_t dcmotor17;   /**< DC Motor 17 Click driver object. */
static log_t logger;            /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor17_cfg_t dcmotor17_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "      DC Motor 17 click     \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dcmotor17_cfg_setup( &dcmotor17_cfg );
    DCMOTOR17_MAP_MIKROBUS( dcmotor17_cfg, MIKROBUS_1 );
    if ( dcmotor17_init( &dcmotor17, &dcmotor17_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dcmotor17_default_cfg ( &dcmotor17 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "          Motor A           \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor forward.  \r\n" );
    dcmotor17_forward( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 5000 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 2000 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor reverse.  \r\n" );
    dcmotor17_reverse( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 5000 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_A );
    Delay_ms( 2000 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "          Motor B           \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor forward.  \r\n" );
    dcmotor17_forward( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 5000 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 2000 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "  Start the motor reverse.  \r\n" );
    dcmotor17_reverse( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 5000 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "       Stop the motor.      \r\n" );
    dcmotor17_stop( &dcmotor17, DCMOTOR17_SEL_OUT_B );
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
