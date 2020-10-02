/*!
 * \file 
 * \brief HallCurrent6 Click example
 * 
 * # Description
 * This application reads current data.
 * 
 * The application is composed of two sections :
 * 
 * ## Application Init 
 * Initializations driver init
 * 
 * ## Application Task  
 * Reads Current data in mA and logs this data to USBUART every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent6.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent6_t hallcurrent6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent6_cfg_setup( &cfg );
    HALLCURRENT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent6_init( &hallcurrent6, &cfg );

    log_printf( &logger, "---- App Init Done ----\r\n" );
}

void application_task ( void )
{
    float current;

    current = hallcurrent6_get_current( &hallcurrent6 );
    log_printf( &logger, " Current value: %.2f mA \r\n" , current);
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
