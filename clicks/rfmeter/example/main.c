/*!
 * \file 
 * \brief Rfmeter Click example
 * 
 * # Description
 * Demo app measures and displays signal strenght by using RF Meter click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI, LOG and click drivers.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the RF Meter click by 
 * measuring radio frequency signal strenght.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rfmeter.h"

// ------------------------------------------------------------------ VARIABLES

static rfmeter_t rfmeter;
static log_t logger;
static float signal;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rfmeter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rfmeter_cfg_setup( &cfg );
    RFMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rfmeter_init( &rfmeter, &cfg );
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "    RF Meter Click      \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
}

void application_task ( void )
{
    signal = rfmeter_get_signal_strenght( &rfmeter, RFMETER_DEF_SLOPE, RFMETER_DEF_INTERCEPT );
    
    log_printf( &logger, "Signal strenght: %.2f dBm \r\n", signal );
    
    Delay_ms( 1000 );
    log_printf( &logger, "-----------------------\r\n" );
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
