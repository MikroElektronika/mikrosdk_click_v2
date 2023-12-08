/*!
 * \file 
 * \brief c2x20WAmp Click example
 * 
 * # Description
 * This application changes the volume level.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * start write log and enable amplifire of 2x20W Amp Click board.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of 2x20W Amp Click board.
 * This examples first activates operation mode PLAY and set volume lvl 32,
 * after that, we increase the volume level one level ten times for 5 seconds
 * and  we decrease the volume level one level ten times for 5 seconds.
 * And finally, we set MUTE mode for next 5 seconds.
 * Results are being sent to the Usart Terminal 
 * where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c2x20wamp.h"

// ------------------------------------------------------------------ VARIABLES

static c2x20wamp_t c2x20wamp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c2x20wamp_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c2x20wamp_cfg_setup( &cfg );
    C2X20WAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c2x20wamp_init( &c2x20wamp, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "    2x20W Amp Click    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    c2x20wamp_enable( &c2x20wamp );
    log_printf( &logger,"    Enable  Amplifier   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );

    Delay_ms( 200 );
}

void application_task ( void )
{
    log_printf( &logger, "       PLAY MODE       \r\n" );
    c2x20wamp_mode_play( &c2x20wamp );
    Delay_ms( 200 );

    uint8_t volume = 32;

    log_printf( &logger, "  Set Volume lvl : %u  \r\n", (uint16_t)volume );
    log_printf( &logger, "-----------------------\r\n" );
    c2x20wamp_set_volume( &c2x20wamp, volume );

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );

    Delay_ms( 5000 );

    for ( uint8_t cnt = 0; cnt < 10; cnt++ )
    {
        log_printf( &logger, "       Volume Up       \r\n" );

        c2x20wamp_volume_up( &c2x20wamp );

        Delay_ms( 100 );
    }

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );

    Delay_ms( 5000 );

    for ( uint8_t cnt = 0; cnt < 10; cnt++ )
    {
        log_printf( &logger, "       Volume Down       \r\n" );

        c2x20wamp_volume_down( &c2x20wamp );

        Delay_ms( 100 );
    }

    log_printf( &logger, "-----------------------\r\n" );

    Delay_ms( 5000 );

    log_printf( &logger, "       MUTE MODE       \r\n" );

    c2x20wamp_mode_mute( &c2x20wamp );

    log_printf( &logger, "-----------------------\r\n" );

    Delay_ms( 5000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
