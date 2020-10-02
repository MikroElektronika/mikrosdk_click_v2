/*!
 * \file 
 * \brief Ozone2 Click example
 * 
 * # Description
 * This example shows value of data aquired from Ozone2 Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialization   
 * 
 * ## Application Task  
 * Reading ADC value and displaying it on terminal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ozone2.h"

// ------------------------------------------------------------------ VARIABLES

static ozone2_t ozone2;
static log_t logger;
static uint32_t read_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ozone2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ozone2_cfg_setup( &cfg );
    OZONE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ozone2_init( &ozone2, &cfg );
}

void application_task ( void )
{
    read_value = ozone2_read( &ozone2 );
    log_printf( &logger, "Read Value: %d\r\n", read_value);
    
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
