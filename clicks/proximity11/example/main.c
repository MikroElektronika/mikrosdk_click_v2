/*!
 * \file 
 * \brief Proximity11 Click example
 * 
 * # Description
 * This appication enables usage of the proximity and ambient light sensors
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and performs device initialization
 * 
 * ## Application Task  
 * Gets ALS and PS values and logs those values
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity11.h"

// ------------------------------------------------------------------ VARIABLES

static proximity11_t proximity11;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity11_cfg_t cfg;
    uint8_t init_status;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity11_cfg_setup( &cfg );
    PROXIMITY11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity11_init( &proximity11, &cfg );

    Delay_ms( 500 );

    init_status = proximity11_default_cfg( &proximity11 );

    if ( init_status == 1 )
    {
        log_printf( &logger, "> app init fail\r\n" );
		while( 1 );
    }
    else if ( init_status == 0 )
    {
        log_printf( &logger, "> app init done\r\n" );
    }
}

void application_task ( void )
{
    //  Task implementation

    uint16_t ps_value;
    float als_value;

    proximity11_get_ps_als_values( &proximity11, &ps_value, &als_value );

    log_printf( &logger, "PS  : %u [count]\r\n", ps_value );
    log_printf( &logger, "ALS : %.2f [Lx]\r\n\r\n", als_value );

    Delay_ms( 500 );

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
