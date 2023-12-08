/*!
 * \file 
 * \brief AudioAmp 4 Click example
 * 
 * # Description
 * This example switches device on & off and sets volume channel to 3.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO interface, turns module ON and sets volume level to 0.
 * 
 * ## Application Task  
 * Turns device OFF & ON and sets a three different volume values.
 * 
 * ## Additional Functions
 * - application_error_handler - Collects the response from the functions.
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioamp4.h"

// ------------------------------------------------------------------ VARIABLES

static audioamp4_t audioamp4;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void application_error_handler ( AUDIOAMP4_RETVAL error_code ) 
{
    switch ( error_code ) 
    {
        case AUDIOAMP4_OK :
        {
            log_info( &logger, "OK\r\n");
        break;    
        }
        case AUDIOAMP4_SHTDWN_STATE_ERR :
        {
            log_info( &logger, "Shutdown state error\r\n" );
        break;
        }
        case AUDIOAMP4_VOL_CHANN_ERR :
        {
            log_info( &logger, "Volume channel error\r\n" );
        break;
        }
        default : 
        {
        break;
        }  
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp4_cfg_t cfg;

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

    audioamp4_cfg_setup( &cfg );
    AUDIOAMP4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp4_init( &audioamp4, &cfg );
    audioamp4_default_cfg( &audioamp4 );
}

void application_task ( void )
{
    log_info( &logger, "Turn on device:" );
    application_error_handler( audioamp4_shutdown( &audioamp4, AUDIOAMP4_SHUTDOWN_OFF ) );
    
    log_info( &logger, "Set volume channel 1:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_1 ) );
    Delay_ms( 2000 );
    
    log_info( &logger, "Set volume channel 5:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_5 ) );
    Delay_ms( 2000 );
    
    log_info( &logger, "Set volume channel 7:" );
    application_error_handler( audioamp4_set_channel( &audioamp4, AUDIOAMP4_VOLUME_CHANN_7 ) );
    Delay_ms( 2000 );
    
    log_info( &logger, "Turn off device:" );
    application_error_handler( audioamp4_shutdown( &audioamp4, AUDIOAMP4_SHUTDOWN_ON ) );
    Delay_ms( 500 );
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
