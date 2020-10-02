/*!
 * \file 
 * \brief 2X5W AMP Click example
 * 
 * # Description
 * This is a example which demonstrates the use of 2x5W Amp Click board.
 * 2x5W AMP click functions as an amplifier and features the TDA7491LP 
 * 2x5-watt dual BTL class-D audio amplifier.
 * It communicates with the target MCU over the following pins
 * on the mikroBUS™ line: AN, RST, CS, PWM, INT.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO and LOG structures,
 * set DIA pin as input and sets GN0, GN1, STB and MUTE pins as output.
 * 
 * ## Application Task  
 * This examples first activates operation mode MUTE for 5 seconds 
 * and after that activates operation mode PLAY.
 * When the device is in Play mode then changes the gain selection, 
 * first sets the minimum gain ( 20dB ) for 10 seconds
 * and then sets the maximum gain (32dB) for 5 seconds too.
 * Results are being sent to the Usart Terminal 
 * where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c2x5wamp.h"

// ------------------------------------------------------------------ VARIABLES

static c2x5wamp_t c2x5wamp;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x5wamp_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, "-- Application Init --\r\n" );
    Delay_ms( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    2x5W Amp  Click    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );

    //  Click initialization.

    c2x5wamp_cfg_setup( &cfg );
    C2X5WAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x5wamp_init( &c2x5wamp, &cfg );
    Delay_ms( 100 );
    
    c2x5wamp_default_cfg ( &c2x5wamp );
    Delay_ms( 100 );
}

void application_task ( void )
{
    c2x5wamp_set_mode( &c2x5wamp, C2X5WAMP_MODE_MUTE );

    log_printf( &logger, "       MUTE  MODE      \r\n" );
    Delay_ms( 5000 );
    log_printf( &logger, "-----------------------\r\n" );

    if ( c2x5wamp_set_mode( &c2x5wamp, C2X5WAMP_MODE_PLAY ) )
    {
        log_printf( &logger, "       PLAY  MODE       \r\n" );
    }
    else
    {
        log_printf( &logger, "    ERROR PLAY MODE    \r\n" );
    }

    log_printf( &logger, "-----------------------\r\n" );

    c2x5wamp_set_gain( &c2x5wamp, C2X5WAMP_GAIN_20DB );

    log_printf( &logger, "   Gain set to  20dB   \r\n" );
    Delay_ms( 10000 );
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );

    c2x5wamp_set_gain( &c2x5wamp, C2X5WAMP_GAIN_32DB );

    log_printf( &logger, "   Gain set to  32dB   \r\n" );
    Delay_ms( 5000 );
    log_printf( &logger, "-----------------------\r\n" );
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
