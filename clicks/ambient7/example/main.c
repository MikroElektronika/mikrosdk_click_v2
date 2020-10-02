/*!
 * \file 
 * \brief Ambient7 Click example
 * 
 * # Description
 * Reads 12-bit ADC value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes ADC and LOG for logging data.
 * 
 * ## Application Task  
 * Reads ADC value and this data logs to USBUART every 1 sec.
 * 
 * *note:* 
 * Illuminance range [ EV ] - from 0.01 [ lx ] to 10k [ lx ] 
 * depending on the ADC you are using.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient7.h"

// ------------------------------------------------------------------ VARIABLES

static ambient7_t ambient7;
static log_t logger;


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    log_printf( &logger, "------------------\r\n" );

    //  Click initialization.

    ambient7_cfg_setup( &cfg );
    AMBIENT7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient7_init( &ambient7, &cfg );
    
    log_printf( &logger, " Ambient 7 Click\r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    ambient7_data_t tmp;
    
    //  Task implementation.
    
    tmp = ambient7_generic_read ( &ambient7 );
    log_printf( &logger, "     ADC value \r\n" );
    log_printf( &logger, " [ DEC ]  : %d\r\n", tmp );
    log_printf( &logger, " [ HEX ]  : 0x%x \r\n", tmp );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 1000 );

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
