/*!
 * \file 
 * \brief DC Motor 6 Click example
 * 
 * # Description
 * This example demonstrates the use of DC Motor 6 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and makes an initial log.
 * 
 * ## Application Task  
 * Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
 * and after that drives it in the reverse direction for 5 seconds, and finally, 
 * disconnects the motor for 2 seconds. Each step will be logged on the USB UART where
 * you can track the program flow.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor6.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor6_t dcmotor6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor6_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    dcmotor6_cfg_setup( &cfg );
    DCMOTOR6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor6_init( &dcmotor6, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_FORWARD );
    Delay_ms( 5000 );
    log_printf( &logger, "Pull brake! \r\n" );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_BRAKE );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor turns in reverse! \r\n" );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_REVERSE );
    Delay_ms( 5000 );
    log_printf( &logger, "The motor is disconnected (High-Z)! \r\n" );
    dcmotor6_set_direction( &dcmotor6, DCMOTOR6_MOTOR_STOP );
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
