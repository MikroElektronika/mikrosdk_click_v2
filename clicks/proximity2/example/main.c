/*!
 * \file 
 * \brief Proximity2 Click example
 * 
 * # Description
 * This is an example that shows the most important
 * functions that Proximity 2 click has.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Setting the click in the default configuration.
 * 
 * ## Application Task  
 * Shows the most important proximity and ambient value.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity2.h"

// ------------------------------------------------------------------ VARIABLES

static proximity2_t proximity2;
static log_t logger;

static uint8_t proxi_val;
static uint8_t avg_proxi_val;
static uint8_t proxi_val_old;
static uint8_t sensitivity;
static uint16_t ambient;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.

    proximity2_cfg_setup( &cfg );
    PROXIMITY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity2_init( &proximity2, &cfg );
    
    proximity2_default_cfg ( &proximity2 );
    
    avg_proxi_val = PROXIMITY2_PROXI_AVG_VAL;
    proxi_val_old = PROXIMITY2_PROXI_MAX_VAL;
    sensitivity = PROXIMITY2_PROXI_SENSITIVITY;
    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void )
{
    proxi_val =  proximity2_read_prox ( &proximity2 );
    ambient = proximity2_read_als ( &proximity2 );

    if ( ( ( proxi_val - proxi_val_old ) > sensitivity ) || ( ( proxi_val_old - proxi_val ) > sensitivity ) )
    {        
        log_printf( &logger, " Distance : %d \r\n", proxi_val );
        
        log_printf( &logger, " Light    : %d \r\n", ambient );

        log_printf( &logger, "------------------\r\n" );
        
        proxi_val_old = proxi_val;
        Delay_ms( 1 );
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
