/*!
 * \file 
 * \brief Audio Amp 2 Click example
 * 
 * # Description
 * This application amplifies the sound on the speakers.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and puts device in Standby Mode as default
 * operation mode and selects 20dB as default gain selection.
 * 
 * ## Application Task  
 * Activates Mute operation mode for 4 seconds and after that activates Play mode.
 * When the device is in Play mode then changes the gain selection, first sets the minimum gain (20dB) for 8 seconds
 * and then sets the maximum gain (32dB) for 8 seconds too.
 * 
 * *note:* 
 * Internally, the gain is set by changing the feedback resistors of the amplifier.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioamp2.h"

// ------------------------------------------------------------------ VARIABLES

static audioamp2_t audioamp2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    audioamp2_cfg_setup( &cfg );
    AUDIOAMP2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp2_init( &audioamp2, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "AudioAmp 2 is initialized \r\n \r\n" );
    Delay_ms( 200 );
}

void application_task ( void )
{
    audioamp2_set_mode( &audioamp2, AUDIOAMP2_MUTE_MODE );
    Delay_ms( 4000 );
    audioamp2_set_gain( &audioamp2, AUDIOAMP2_20DB_GAIN );
    audioamp2_set_mode( &audioamp2, AUDIOAMP2_PLAY_MODE );
    Delay_ms( 8000 );
    audioamp2_set_gain( &audioamp2, AUDIOAMP2_32DB_GAIN );
    Delay_ms( 8000 );
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
