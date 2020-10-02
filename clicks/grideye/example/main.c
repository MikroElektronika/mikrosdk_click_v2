/*!
 * \file 
 * \brief Grideye Click example
 * 
 * # Description
 * 64 individual thermal sensors build an image on a display. The detecting distance is 5m.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies default settings, and makes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Grid-EYE click board by reading full grid and displaying values via USART terminal
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "grideye.h"

// ------------------------------------------------------------------ VARIABLES

static grideye_t grideye;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    grideye_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    grideye_cfg_setup( &cfg );
    
    GRIDEYE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    grideye_init( &grideye, &cfg );

    grideye_default_cfg ( &grideye );
}

void application_task ( void )
{
    uint8_t i;
    uint8_t j;
    uint16_t grid_array[ 64 ];
    uint16_t grid_array_tmp;

    grideye_read_grid( &grideye, &grid_array );

    for( i = 1; i < 9; i++ )
    {
        for( j = 1; j < 9; j++ )
        {
            log_printf( &logger, "| " );
            grid_array_tmp = grid_array[ i * j ];
            
            log_printf( &logger, "%d ", grid_array_tmp );
        }
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "-------------------------------------- \r\n" );
    }
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
