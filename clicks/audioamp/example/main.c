/*!
 * \file 
 * \brief AudioAmp Click example
 * 
 * # Description
 * AudioAmp Click is a stereo audio amplifier
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, turn on the Audio Amp click and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of AudioAmp Click board.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioamp.h"

// ------------------------------------------------------------------ VARIABLES

static audioamp_t audioamp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audioamp_cfg_setup( &cfg );
    AUDIOAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp_init( &audioamp, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "~~~~~~~~~~~~~~~~~~~~~~\r\n " );
    log_printf( &logger, "    AudioAmp Click   \r\n " );
    log_printf( &logger, "~~~~~~~~~~~~~~~~~~~~~~\r\n" );

    log_printf( &logger, "       Power ON       \r\n" );
    
    audioamp_power_on( &audioamp );
    Delay_ms( 1000 );

    log_printf( &logger, "----------------------\r\n" );
}

void application_task ( void )
{
    log_printf( &logger, " Set volume to lvl 15 \r\n" );
    log_printf( &logger, " for the next 10 sec. \r\n" );

    audioamp_set_volume( &audioamp, 15 );
    Delay_ms( 10000 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Set volume to lvl 5  \r\n" );
    log_printf( &logger, " for the next 15 sec. \r\n" );

    audioamp_set_volume( &audioamp, 5 );
    Delay_ms( 15000 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Set volume to lvl 10 \r\n" );
    log_printf( &logger, " for the next 20 sec. \r\n" );

    audioamp_set_volume( &audioamp, 10 );
    Delay_ms( 20000 );
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "      Mute  mode      \r\n" );
    log_printf( &logger, " for the next 5 sec.  \r\n" );

    audioamp_mute_mode( &audioamp );
    Delay_ms( 5000 );
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "     Unmute  mode     \r\n" );

    audioamp_unmute_mode( &audioamp );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
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
