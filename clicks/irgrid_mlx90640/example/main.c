/*!
 * \file 
 * \brief IrGridMlx90640 Click example
 * 
 * # Description
 * The demo application displays a reading of ambient temperature and 
 * a 32x24 pixel object temperature matrix.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Reads the temperature of all pixels and creates a pixel temperature matrix
 * that logs on usbuart every 500ms.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irgrid_mlx90640.h"

// ------------------------------------------------------------------ VARIABLES

static irgrid_mlx90640_t irgrid_mlx90640;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irgrid_mlx90640_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.

    irgrid_mlx90640_cfg_setup( &cfg );
    IRGRID_MLX90640_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irgrid_mlx90640_init( &irgrid_mlx90640, &cfg );

    irgrid_mlx90640_default_cfg( &irgrid_mlx90640 );

    Delay_ms( 1000 );
    log_info( &logger, "---- Start measurement ----" );
}

void application_task ( void )
{
    uint16_t cnt;
    static float px_matrix[ 768 ];
    float temp_ambient;

    //  Task implementation.

    irgrid_mlx90640_get_pixel_temperature( &irgrid_mlx90640, &temp_ambient, px_matrix );

    log_printf( &logger, "** Ambient temperautre is %f C\r\n", temp_ambient );

    log_printf( &logger, "\r\n>> Pixel temperature matrix 32x24 <<\r\n" );

    for ( cnt = 0 ; cnt < 768 ; cnt++)
    {
        log_printf( &logger, " %.2f |", px_matrix[ cnt ] );
        Delay_1ms( );
        if ( ( ( cnt % 32 ) == 0 ) && ( cnt > 0 ) )
        {
            log_printf( &logger, "\r\n" );
        }
    }
    log_printf( &logger, "\r\n" );
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
