/*!
 * \file 
 * \brief HallCurrent4 Click example
 * 
 * # Description
 * Demo application shows is reading current data in mA using Hall current 4 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Reads Current value in mA and logs this data to USBUART every 1 sec.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent4.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent4_t hallcurrent4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hallcurrent4_cfg_setup( &cfg );
    HALLCURRENT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent4_init( &hallcurrent4, &cfg );
}

void application_task ( void )
{
    float current;

    current = hallcurrent4_get_current_data( &hallcurrent4 );

    log_printf( &logger, " >> Current value: %.2f mA\r\n", current );
    log_printf( &logger, " ------------------------- \r\n" );
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
