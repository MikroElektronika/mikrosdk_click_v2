/*!
 * \file 
 * \brief Nano Power Click example
 * 
 * # Description
 * This aplication performs control of the device's voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver.
 * 
 * ## Application Task  
 * Turns device on for 5 seconds and than turns device off for 10 seconds,
 * then the output voltage starts to fall.
 * When input voltage rises from 0.8V to 5.5V,
 * the output voltage rises from 5.1V to 5.25V.
 * When input voltage is less than 0.8V, the output voltage is less than 5V.
 * 
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nanopower.h"

// ------------------------------------------------------------------ VARIABLES

static nanopower_t nanopower;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanopower_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    nanopower_cfg_setup( &cfg );
    NANOPOWER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanopower_init( &nanopower, &cfg );
}

void application_task ( void )
{
    log_printf(&logger,"Device enabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_ENABLE_DEVICE );
    Delay_ms( 5000 );
    log_printf(&logger,"Device disabled\r\n");
    nanopw_enable_device( &nanopower, NANOPW_DISABLE_DEVICE );
    Delay_ms( 10000 );
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
