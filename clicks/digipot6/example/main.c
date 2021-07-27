/*!
 * \file 
 * \brief DIGIPOT6 Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the DIGI POT 6 click module. The
 * click is a digital potentiometer. The potentiometer has a programmable wiper which controls 
 * the resistance between P0W-POA and POW-POB. An external power supply is required for this example.  
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules. This function also sets
 * the click default configuration.
 * 
 * ## Application Task  
 * This function programs the wiper position and shows the current wiper position in the UART
 * console every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digipot6.h"

// ------------------------------------------------------------------ VARIABLES

static digipot6_t digipot6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digipot6_cfg_setup( &cfg );
    DIGIPOT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot6_init( &digipot6, &cfg );
    Delay_100ms( );
    digipot6_default_cfg( &digipot6 );
    Delay_100ms( );
}

void application_task ( void )
{
    uint8_t wiper;
    uint16_t cnt;
    
    for ( cnt = 0; cnt <= 255; cnt += 15 )
    {
        digipot6_write_data( &digipot6, DIGIPOT6_VOLATILE_WIPER_0, cnt );
        Delay_ms( 10 );

        wiper = digipot6_read_data( &digipot6, DIGIPOT6_VOLATILE_WIPER_0 );

        log_printf( &logger, " * Wiper position: %u *\r\n", ( uint16_t ) wiper );
        Delay_ms( 1000 );
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
