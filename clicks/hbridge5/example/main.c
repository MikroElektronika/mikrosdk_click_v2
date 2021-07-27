/*!
 * \file 
 * \brief HBridge5 Click example
 * 
 * # Description
 * This application controls DC motors and inductive loads.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, configures all ports as output and writes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of H-Bridge 5 Click board, by running dc motor forward, 
 * then stoping and then running it in reverse and stoping again.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hbridge5.h"

// ------------------------------------------------------------------ VARIABLES

static hbridge5_t hbridge5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge5_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hbridge5_cfg_setup( &cfg );
    HBRIDGE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge5_init( &hbridge5, &cfg );
    hbridge5_default_cfg( &hbridge5 );
}

void application_task ( void )
{
    log_printf( &logger, "Mode - FORWARD\r\n" );
    hbridge5_forward( &hbridge5 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "Mode - SLEEP\r\n" );
    hbridge5_sleep( &hbridge5, HBRIDGE5_DISABLE_ALL_OUTPUT_PORT );
    Delay_ms( 3000 );
    
    log_printf( &logger, "Mode - REVERSE\r\n" );
    hbridge5_reverse( &hbridge5 );
    Delay_ms( 3000 );
    
    log_printf( &logger, "Mode - SLEEP\r\n" );
    hbridge5_sleep( &hbridge5, HBRIDGE5_DISABLE_ALL_OUTPUT_PORT );
    Delay_ms( 3000 );
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
