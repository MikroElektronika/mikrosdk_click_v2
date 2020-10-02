/*!
 * \file 
 * \brief Rmeter Click example
 * 
 * # Description
 * Demo app measures and displays resistance of a resistor connected 
 * to the R Meter click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI, LOG and click drivers
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the R Meter click by 
 * measuring resistance.
 * 
 * *note:* 
 * R Meter click is a handy tool but it is not to be used as a precision 
 * instrument! The linearity of the OpAmp impacts the measurement.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rmeter.h"

// ------------------------------------------------------------------ VARIABLES

static rmeter_t rmeter;
static log_t logger;

static float ohms;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rmeter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rmeter_cfg_setup( &cfg );
    RMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rmeter_init( &rmeter, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "    R Meter  Click      \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
}

void application_task ( void )
{
    ohms = rmeter_get_ohms( &rmeter );
    
    if ( ohms == RMETER_OVER_RANGE )
    {
        log_printf( &logger, " Over range! \r\n" );
    }
    else
    {
        log_printf( &logger, "Resistance: %.2f ohm \r\n", ohms );
    }
    
    log_printf( &logger, "----------------------- \r\n" );
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
