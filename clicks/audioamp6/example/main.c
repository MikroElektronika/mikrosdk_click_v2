/*!
 * \file 
 * \brief AudioAmp 6 Click example
 * 
 * # Description
 *  The demo application displays the volume change using AudioAmp 6 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Select mode and sets output on the enable state.
 * 
 * ## Application Task  
 * Changes the gain settings ( 20dB - 26dB )
 * 
 * *note:* 
 * Sets the input voltage from 3.5V to 14.4V.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioamp6.h"

// ------------------------------------------------------------------ VARIABLES

static audioamp6_t audioamp6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp6_cfg_t cfg;

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

    audioamp6_cfg_setup( &cfg );
    AUDIOAMP6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp6_init( &audioamp6, &cfg );

    audioamp6_set_mode( &audioamp6, AUDIOAMP6_MODE_BD );
    audioamp6_set_output( &audioamp6, AUDIOAMP6_OUTPUT_ENABLE );

    log_info( &logger,"---- Start control AudioAmp 6 click ----" );
}

void application_task ( void )
{
    //  Task implementation.

    log_printf( &logger,">> Set gain 20 dB \r\n" );
    audioamp6_set_gain( &audioamp6, AUDIOAMP6_GAIN_20dB );
    Delay_ms( 2000 );
    log_printf( &logger,">> Set gain 26 dB \r\n" );
    audioamp6_set_gain( &audioamp6, AUDIOAMP6_GAIN_26dB );
    Delay_ms( 2000 );
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
