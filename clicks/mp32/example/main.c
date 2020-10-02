/*!
 * \file 
 * \brief Mp32 Click example
 * 
 * # Description
 * This example reads and processes data from MP3 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - UART,
 reset the device, set specify a device play tracks inside ( SD Card ),
 set volume lvl ( 50% ), set equalizer to normal mode and
 set commmand for specifying a track to play.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of MP3 2 click board.
 Waits for valid user input and executes functions based 
 on set of valid commands.
 Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * ## Additional Function
 * - mp32_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mp32.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static mp32_t mp32;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mp32_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mp32_cfg_setup( &cfg );
    MP32_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp32_init( &mp32, &cfg );

    Delay_ms( 500 );

    log_printf( &logger, "-------------------------/r/n" );
    log_printf( &logger, "       MP3 2 click       /r/n" );
    log_printf( &logger, "-------------------------/r/n" );
    Delay_100ms( );

    mp32_hw_reset( &mp32 );
    Delay_ms( 100 );
    mp32_hw_reset( &mp32 );
    mp32_set_device( &mp32, MP32_SDCARD );
    mp32_set_volume( &mp32, 50 );
    mp32_set_eq( &mp32, MP32_EQ_NORMAL );
    Delay_ms( 100 );
    
    mp32_play_specific ( &mp32, 1 );
}

void application_task ( void )
{
    char received_data;
     
    mp32_play_mode( &mp32 );
    log_printf( &logger, " >>> Play\r\n" );
    Delay_ms( 5000 );

    mp32_stop_mode( &mp32 );
    log_printf( &logger, " >>> Stop\r\n" );
    Delay_ms( 5000 );            
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
