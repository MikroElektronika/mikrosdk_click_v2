/*!
 * \file
 * \brief 3dHall5 Click example
 *
 * # Description
 * The Demo application displays and reads 3 magnetic axes.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring clicks and log objects.
 * Reads device ID for check communication.
 *
 * ## Application Task
 * Reads the magnetics X / Y / Z axis data every 1 seconds.
 *
 * *note:*
 * Default communication that is set is I2C communication.
 * If you want to use SPI, you have to set up the cfg structure.
 *
 * \author Katarina PerendicS
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3dhall5.h"

// ------------------------------------------------------------------ VARIABLES

static c3dhall5_t c3dhall5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall5_cfg_t cfg;
    uint8_t device_id;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall5_cfg_setup( &cfg );
    C3DHALL5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall5_init( &c3dhall5, &cfg );

    c3dhall5_default_cfg ( &c3dhall5 );

    device_id = c3dhall5_get_device_id ( &c3dhall5 );
    log_info( &logger, "** Device ID: 0x%x", device_id );
}

void application_task ( void )
{
    int16_t axis_X;
    int16_t axis_Y;
    int16_t axis_Z;

    //  Task implementation.

    axis_X = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_X );
    axis_Y = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_Y );
    axis_Z = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_Z );

    log_printf( &logger, "----- AXIS -----\r\n" );
    log_printf( &logger, "** X: %d \r\n", axis_X );
    log_printf( &logger, "** Y: %d \r\n", axis_Y );
    log_printf( &logger, "** Z: %d \r\n", axis_Z );
    log_printf( &logger, "----------------\r\n" );

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
