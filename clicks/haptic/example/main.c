/*!
 * \file 
 * \brief Haptic Click example
 * 
 * # Description
 * This application generate vibrations from the lower frequency range of the audio input.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * first, we enable the device, set soft reset, set calibrating and start the engine.
 * After that, we set Audio-to-Vibe mode, Minimum Input level ( ~ 1.35V ),
 * enable AC coupling, select input mode for Analog input and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Haptic Click board.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "haptic.h"

// ------------------------------------------------------------------ VARIABLES

static haptic_t haptic;
static log_t logger;

uint8_t start_status;

void application_init ( void )
{
    log_cfg_t log_cfg;
    haptic_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    haptic_cfg_setup( &cfg );
    HAPTIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    haptic_init( &haptic, &cfg );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     Haptic  Click     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );

    haptic_enable( &haptic );

    start_status = 1;

    log_printf( &logger, "        Enabled        \r\n" );
    Delay_ms( 200 );

    haptic_soft_reset( &haptic );
    log_printf( &logger, "         Reset         \r\n" );
    Delay_ms( 200 );

    haptic_set_mode( &haptic, HAPTIC_MODE_AUTOCAL );

    log_printf( &logger, "     Calibrating...    \r\n" );
    Delay_ms( 1000 );

    haptic_start_motor( &haptic );
    log_printf( &logger, "   Start the engine    \r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "-----------------------\r\n" );

    haptic_set_mode( &haptic, HAPTIC_MODE_AUDIOVIBE );

    log_printf( &logger, " Set Audio-to-Vibe mode\r\n" );

    haptic_set_audio_minimum_input( &haptic, HAPTIC_DEFAULT_MIN_INPUT );

    log_printf( &logger, "  Minimum Input level  \r\n" );
    log_printf( &logger, "      About 1.35V      \r\n" );

    haptic_enable_ac_coulping( &haptic );
    log_printf( &logger, "  Enable  AC coupling  \r\n" );

    haptic_set_input_to_analog( &haptic );
    log_printf( &logger, " Sets input -  analog  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void )
{
    if ( start_status )
        log_printf( &logger, "         START         \r\n" );

    start_status = 0;
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
