/*!
 * \file 
 * \brief Boost Click example
 * 
 * # Description
 * Boost click provides an adjustable output voltage through the onboard DAC that drives the FB 
 * pin of the MIC2606 to set desired output voltage. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI, set configuration and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Boost Click board.
     Boost Click communicates with register via SPI by read from MCP3551 chip and write DAC value to the MCP4921 chip.
     This example periodicaly increases and decreases voltage in range between 15 and 30 Volts.
     All data logs write on usb uart for aproximetly every 3 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost.h"

// ------------------------------------------------------------------ VARIABLES

static boost_t boost;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boost_cfg_setup( &cfg );
    BOOST_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost_init( &boost, &cfg );

    boost_default_cfg ( &boost );

    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, " Setting voltage to 15000 mV \r\n" );

    boost_set_voltage( &boost, 15000 );
    Delay_ms( 5000 );

    log_printf( &logger, " Setting voltage to 30000 mV \r\n" );

    boost_set_voltage( &boost, 30000 );
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
