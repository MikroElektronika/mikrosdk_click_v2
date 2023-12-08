/*!
 * \file 
 * \brief H-Bridge 4 Click example
 * 
 * # Description
 * This application is used to turn on DC or Stepper motors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO and also starts write log.
 * 
 * ## Application Task  
 * This example demonstrates the use of H-Bridge 4 click board by putting A motor
 * in standby mode, then spining it in clockwise direction and applying brake function, and then
 * spining it in counter-clockwise direction and applying brake function again.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hbridge4.h"

// ------------------------------------------------------------------ VARIABLES

static hbridge4_t hbridge4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge4_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    hbridge4_cfg_setup( &cfg );
    HBRIDGE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge4_init( &hbridge4, &cfg );

    hbridge4_enable( &hbridge4, 1 );
    Delay_ms( 100 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, " H-Bridge 4 click \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}

void application_task ( )
{
    log_printf( &logger, "The motor A is in standby mode \r\n" );
    hbridge4_motor_a_standby( &hbridge4 );
    Delay_ms( 100 );
    log_printf( &logger, "The motor A turns clockwise \r\n" );
    hbridge4_motor_acw( &hbridge4 );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor A applies brake \r\n" );
    hbridge4_motor_a_brake( &hbridge4 );
    Delay_ms( 1000 );
    log_printf( &logger, "The motor A turns counter-clockwise \r\n" );
    hbridge4_motor_accw( &hbridge4 );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor A applies brake \r\n" );
    hbridge4_motor_a_brake( &hbridge4 );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
