/*!
 * \file 
 * \brief StereoAmp Click example
 * 
 * # Description
 * This is an example which demonstrates the use of StereoAmp Click board -
 * stereo amplifier and is ideal for battery operated devices or as a lab amplifier.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This examples first set volume level 20 of 31 ( gain: 1,5 dB ) for 10 seconds. 
 * After that, we increase the volume to level 10 ( gain: -13,5 dB ) for the next 10 seconds. 
 * Results are being sent to the UART Terminal where you can track their changes.
 *  
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stereoamp.h"

// ------------------------------------------------------------------ VARIABLES

static stereoamp_t stereoamp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stereoamp_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms ( 500 );

    //  Click initialization.

    stereoamp_cfg_setup( &cfg );
    STEREOAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stereoamp_init( &stereoamp, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ---  StereoAmp Click --- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    stereoamp_default_cfg( &stereoamp );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "         Power  On        \r\n" );
    stereoamp_set_power_on( &stereoamp );
    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "     Set Volume: -80dB    \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_NEG_80dB );
    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "       Enable Fault       \r\n" );
    stereoamp_enable_fault( &stereoamp );
    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "     Enable Diagnostic    \r\n" );
    stereoamp_enable_diagnostic( &stereoamp );
    Delay_ms ( 500 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 500 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " -----  Play  Music ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    log_printf( &logger, "        Gain 1.5 dB        \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_1_5dB );
    Delay_ms ( 10000 );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "        Gain -13.5 dB      \r\n" );
    stereoamp_set_volume( &stereoamp, STEREOAMP_GAIN_NEG_13_5dB );
    Delay_ms ( 10000 );
    log_printf( &logger, "--------------------------\r\n" );
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
