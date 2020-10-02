 /*!
 * \file 
 * \brief Microwave2 Click example
 * 
 * # Description
 * This application is an accurate and reliable short to medium range motion detection.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click board for communication.
 * 
 * ## Application Task  
 * Data sen't from the click board is captured and different actions are applied.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "microwave2.h"

// ------------------------------------------------------------------ VARIABLES

static microwave2_t microwave2;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    microwave2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    microwave2_cfg_setup( &cfg );
    MICROWAVE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    microwave2_init( &microwave2, &cfg );
}

void application_task ( void )
{
    char temp;
    char r_dat;
    uint8_t buf[ 6 ];
    
    r_dat = microwave2_generic_single_read( &microwave2 );
    microwave2_uart_handler( &microwave2, &buf, r_dat );

    temp = microwave2_check_trafic( &microwave2 );
    
    if ( temp == MICROWAVE2_MOVING_CLOSER )
    {
       log_printf( &logger, "Approaching \r\n" );
    }
    if ( temp == MICROWAVE2_STOPPED_MOVING )
    {
       log_printf( &logger, "No movesment \r\n");
    }
    if ( temp == MICROWAVE2_MOVING_AWAY )
    {
       log_printf( &logger, "Moving away \r\n" );
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
