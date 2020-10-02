/*!
 * \file 
 * \brief GmrAngle Click example
 * 
 * # Description
 * This is an example which demonstrates the use of GMR Angle Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO pins, SPI and LOG modules.
 * 
 * ## Application Task  
 * Display angle value in degrees.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gmrangle.h"

// ------------------------------------------------------------------ VARIABLES

static gmrangle_t gmrangle;
static log_t logger;
static float angle;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gmrangle_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gmrangle_cfg_setup( &cfg );
    GMRANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gmrangle_init( &gmrangle, &cfg );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   GMR Angle Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "        Start\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    angle = gmrangle_calculate_angle( &gmrangle );
    log_printf( &logger, " Angle is %0.2f\r\n", angle );
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
