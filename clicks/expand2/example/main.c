/*!
 * \file 
 * \brief Expand2 Click example
 * 
 * # Description
 * This application demonstrates the use of the Expand 2 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger, and then sets the click 
 * default configuration: PORTA as output, PORTB as input with pull-ups on all pins.
 * 
 * ## Application Task  
 * Sets other pin of PORTA every 3 seconds, then reads and displays the status of 
 * both ports on USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "expand2.h"

// ------------------------------------------------------------------ VARIABLES

static expand2_t expand2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    expand2_cfg_setup( &cfg );
    EXPAND2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand2_init( &expand2, &cfg );

    expand2_default_cfg ( &expand2 );

    log_printf( &logger, "----------------\r\n" );
    log_printf( &logger, " Expand 2 Click \r\n" );
    log_printf( &logger, "----------------\r\n" );

    Delay_ms( 100 );
}

void application_task ( void )
{
    //  Task implementation.

    uint8_t port_status;
    uint8_t pin_position;

    for ( pin_position = 0; pin_position < 8; pin_position++ )
    {
        expand2_set_port_a( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0, pin_position );
        
        port_status = expand2_read_port_a( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0 );

        log_printf( &logger, " Status PA (output): %d\r\n", (uint16_t) port_status );
        
        port_status = expand2_read_port_b( &expand2, EXPAND2_I2C_MODULE_ADDRESS_0 );

        log_printf( &logger, " Status PB (input) : %d  \r\n", (uint16_t) port_status );
        log_printf( &logger, "----------------\r\n" );
        
        Delay_ms( 3000 );
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
