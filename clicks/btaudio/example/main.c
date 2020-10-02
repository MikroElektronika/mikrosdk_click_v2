/*!
 * \file 
 * \brief BtAudio Click example
 * 
 * # Description
 * This example reads and processes data from BT Audio clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Demo of application controls.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "btaudio.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static btaudio_t btaudio;
static log_t logger;

char buffer[ 255 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    btaudio_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    btaudio_cfg_setup( &cfg );
    BTAUDIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btaudio_init( &btaudio, &cfg );
    Delay_ms( 1000 );

    log_printf( &logger, "      Power On       \r\n" );
    btaudio_set_power_on( &btaudio );
    Delay_ms( 5000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "  Set Command mode   \r\n" );
    btaudio_set_cmd_mode( &btaudio, 1, buffer );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "    Set Data mode    \r\n" );
    btaudio_set_cmd_mode( &btaudio, 0, buffer );
    Delay_ms( 1000 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "   Factory  Reset    \r\n" );
    btaudio_set_factory_defaults( &btaudio );
    Delay_ms( 1000 );
    log_printf( &logger, "-------------------- \r\n" );
}

void application_task ( void )
{
    log_printf( &logger, "    - Volume Up -\r\n" );
    btaudio_increase_volume( &btaudio );
    Delay_ms( 3500 );

    btaudio_decrease_volume( &btaudio );
    log_printf( &logger, "   - Volume Down - \r\n" );
    Delay_ms( 3500 );

    btaudio_next_track( &btaudio );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "     Next Track     \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 3500 );

    btaudio_previous_track( &btaudio );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "   Previous Track   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 3500 );

    btaudio_pause_play_track( &btaudio );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Play/Pause Track  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 3500 );
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
