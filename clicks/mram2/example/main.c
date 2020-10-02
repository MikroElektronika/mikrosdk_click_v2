/*!
 * \file 
 * \brief Mram2 Click example
 * 
 * # Description
 * This demo example writes and reads from memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI module, LOG structure, sets CS, RTS and INT pins as output.
 * 
 * ## Application Task  
 * This example shows capabilities of MRAM 2 Click board
 * by writting "MikroE" into first 6 memory locations, 
 * and then reading it back.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mram2.h"

// ------------------------------------------------------------------ VARIABLES

static mram2_t mram2;
static log_t logger;

char val_in[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
char val_out[ 9 ] = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mram2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mram2_cfg_setup( &cfg );
    MRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram2_init( &mram2, &cfg );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   MRAM 2 Click     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    mram2_write_protect( &mram2, MRAM2_WP_ENABLE );
    mram2_hold( &mram2, MRAM2_HLD_DISABLE );
    log_printf( &logger, "   Initialized      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, "Write enable! \r\n" );
    mram2_wren( &mram2 );
    Delay_ms( 100 );
    log_printf( &logger, "Writing : %s \r\n", val_in );
    mram2_write( &mram2, 0x000000, &val_in[ 0 ], 9 );
    Delay_ms( 100 );
    log_printf( &logger, "Write disable! \r\n" );
    mram2_wrdi ( &mram2 );
    Delay_ms( 100 );
    log_printf( &logger, "Reading : \r\n" );
    mram2_read ( &mram2, 0x000000, &val_out[ 0 ], 9 );
    log_printf( &logger, " %s \r\n", val_out );
    
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms( 5000 );
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
