/*!
 * \file 
 * \brief SwipeSwitch Click example
 * 
 * # Description
 * This Click is based on integrated touch controller featuring 2 receivers and 3 transmitters, 
 * allowing a 2x3 capacitive touch trackpad to be formed. By using a specific trace pattern on the PCB, 
 * the Click board is able to sense several different swipe gestures, offering several different configuration parameters.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization and configuration of the chip for measurement
 * 
 * ## Application Task  
 * In the first test mode, it checks whether or not a new event ocurred (TAP or SWIPE). 
 * If it did, it writes out data regarding that event via UART.
 * In the second test mode, X and Y coordinates are being read and logged via UART.
 * 
 * *note:* 
 * After reading data or status registers, 
 * there is a certain time which must pass until the device is ready again.
 * The device is ready for a new conversion and reading after the Ready pin is LOW.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "swipeswitch.h"

// ------------------------------------------------------------------ VARIABLES

static swipeswitch_t swipeswitch;
static log_t logger;

static uint8_t x_coordinate     = 0;
static uint8_t y_coordinate     = 0;
static uint8_t old_x_coordinate = 0;
static uint8_t old_y_coordinate = 0;
static uint8_t events           = 0;
static uint8_t gestures         = 0;
static uint8_t display_mode     = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    swipeswitch_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    swipeswitch_cfg_setup( &cfg );
    SWIPESWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    swipeswitch_init( &swipeswitch, &cfg );
    swipeswitch_default_cfg( &swipeswitch );
    Delay_ms( 300 );
}

void application_task ( void )
{
    if ( display_mode == 0)
    {

        events = swipeswitch_read_events( &swipeswitch );
        gestures = swipeswitch_read_gestures( &swipeswitch );

        
        if ( ( events & ( SWIPESWITCH_EVENT_SWIPE ) ) != 0 )
        {
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_UP ) != 0 )
            {
                log_printf( &logger, "SWIPE UP \r\n" );
            }
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_DOWN ) != 0 )
            {
                log_printf( &logger, "SWIPE DOWN \r\n" );
            }
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_LEFT ) != 0 )
            {
                log_printf( &logger, "SWIPE LEFT \r\n" );
            }
            if ( ( gestures & SWIPESWITCH_GESTURE_SWIPE_RIGHT ) != 0 )
            {
                log_printf( &logger, "SWIPE RIGHT \r\n" );
            }
        }
        
        else if ( ( events & ( SWIPESWITCH_EVENT_TAP ) ) != 0 )
        {
            log_printf( &logger,"TAP \r\n" );
        }
    }
    else
    {
        while ( swipeswitch_wait_for_ready( &swipeswitch ) != 0);
        x_coordinate = swipeswitch_read_x_coordinate( &swipeswitch );
        while ( swipeswitch_wait_for_ready( &swipeswitch ) != 0);
        y_coordinate = swipeswitch_read_y_coordinate( &swipeswitch );

        if ( ( x_coordinate != old_x_coordinate) || ( y_coordinate != old_y_coordinate ) )
        {
            log_printf( &logger,"Coordinate : (%d , %d)", x_coordinate, y_coordinate );

            old_x_coordinate = x_coordinate;
            old_y_coordinate = y_coordinate;
        }
    }
    Delay_ms( 300 );
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
