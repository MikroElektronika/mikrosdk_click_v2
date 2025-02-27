/*!
 * @file main.c
 * @brief H-Bridge 18 Click example
 *
 * # Description
 * This example demonstrates the operation of the H-Bridge 18 Click board, which
 * provides control over two DC motors using an H-Bridge driver. The application
 * initializes the board and alternates between different motor states, including
 * forward, reverse, coast, and braking, to demonstrate bidirectional motor control.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the H-Bridge 18 Click board. Configures the motor driver
 * to the default settings, preparing it for operation.
 *
 * ## Application Task
 * Alternates motor states in a sequence to demonstrate different control functionalities.
 * The motors are set to move forward and reverse, followed by coasting and braking,
 * repeating the cycle continuously.
 *
 * @note
 * Ensure proper power supply (4.5V-32V, depending on motor specifications) and motor
 * connections (motor 0: O1-O2; motor 1: O3-O4) before running the example.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge18.h"

static hbridge18_t hbridge18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge18_cfg_t hbridge18_cfg;  /**< Click config object. */

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
    hbridge18_cfg_setup( &hbridge18_cfg );
    HBRIDGE18_MAP_MIKROBUS( hbridge18_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge18_init( &hbridge18, &hbridge18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE18_ERROR == hbridge18_default_cfg ( &hbridge18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf( &logger, " Motor 0: Forward\r\n" );
    log_printf( &logger, " Motor 1: Reverse\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_FORWARD );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Motor 0: Coast\r\n" );
    log_printf( &logger, " Motor 1: Brake LS\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_COAST );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_BRAKE_LS );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Motor 0: Reverse\r\n" );
    log_printf( &logger, " Motor 1: Forward\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_REVERSE );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Motor 0: Brake HS\r\n" );
    log_printf( &logger, " Motor 1: Coast\r\n\n" );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_0, HBRIDGE18_MOTOR_STATE_BRAKE_HS );
    hbridge18_set_motor_state ( &hbridge18, HBRIDGE18_MOTOR_1, HBRIDGE18_MOTOR_STATE_COAST );
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
