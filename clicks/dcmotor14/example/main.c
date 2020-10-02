/*!
 * \file 
 * \brief DC MOTOR 14 Click example
 * 
 * # Description
 * This IC includes one channel of motor output block, using a wide range of supply voltages, while delivering reasonably high current to the connected DC motors. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and starts log.
 * 
 * ## Application Task  
 * This example demonstrates the use of DC Motor 14 click by driving it forward motion for 5 seconds,
 * than applying brakes it for 2 second, and then driving it in reverse for 5 seconds, after that, it stops for 2 second.
 * 

 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor14.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor14_t dcmotor14;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor14_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    dcmotor14_cfg_setup( &cfg );
    DCMOTOR14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor14_init( &dcmotor14, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    dcmotor14_forward( &dcmotor14 );
    Delay_ms( 5000 );
    log_printf( &logger, "The motor brakes! \r\n" );
    dcmotor14_brake( &dcmotor14 );
    Delay_ms( 2000 );
    log_printf( &logger, "The motor turns in reverse \r\n" );
    dcmotor14_reverse( &dcmotor14 );
    Delay_ms( 5000 );
    log_printf( &logger, "The motor stops \r\n" );
    dcmotor14_stop( &dcmotor14 );
    Delay_ms( 2000 );
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
