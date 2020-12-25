/*!
 * \file 
 * \brief AudioAmp Click example
 * 
 * # Description
 * AudioAmp Click is a stereo audio amplifier which can be controlled by using this
 * click driver.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init
 * Performs driver and log module initialization, enables I2C, turns on the AudioAmp device
 * and sends a message about init status.
 * 
 * ## Application Task
 * This is a example which demonstrates the use and control of the AudioAmp Click board.
 * 
 * \author Nemanja Medakovic
 *
 */

#include "board.h"
#include "log.h"
#include "audioamp.h"

static audioamp_t audioamp;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init... ----" );

    audioamp_cfg_t audioamp_cfg;

    //  Click initialization.

    audioamp_cfg_setup( &audioamp_cfg );
    AUDIOAMP_MAP_MIKROBUS( audioamp_cfg, MIKROBUS_1 );

    if ( audioamp_init( &audioamp, &audioamp_cfg ) == AUDIOAMP_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );
    log_info( &logger, "---- Application Running... ----" );
    log_info( &logger, "---- Check your audio speaker. ----\n" );

    audioamp_power_on( &audioamp );
}

void application_task ( void )
{
    log_info( &logger, "---- Volume level control testing... ----" );

    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 5 );
    Delay_ms( 3000 );
    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 15 );
    Delay_ms( 3000 );
    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 25 );
    Delay_ms( 3000 );
    audioamp_set_volume( &audioamp, AUDIOAMP_IN_1 | AUDIOAMP_IN_2, 32 );
    Delay_ms( 3000 );

    log_info( &logger, "---- Volume level control test done. ----" );
    log_info( &logger, "---- Input mute/unmute control testing... ----" );

    audioamp_mute( &audioamp );
    Delay_ms( 3000 );
    audioamp_unmute( &audioamp );
    Delay_ms( 10000 );

    log_info( &logger, "---- Input mute/unmute control test done. ----" );
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
