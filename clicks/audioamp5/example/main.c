/*!
 * \file 
 * \brief Audio Amp 5 Click example
 * 
 * # Description
 * This example consist of sending special commands for audio output control, 
 * selecting different output modes and turning on/off the audio output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO interface on the desired mikrobus selection,
 * and performs a device init configuration.
 * 
 * ## Application Task  
 * Checks the entered command and, if the command is valid,
 * performs a device configuration which the entered command determines.
 * 
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioamp5.h"

// ------------------------------------------------------------------ VARIABLES

static audioamp5_t audioamp5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp5_cfg_t cfg;

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

    audioamp5_cfg_setup( &cfg );
    AUDIOAMP5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp5_init( &audioamp5, &cfg );
    
    audioamp5_default_cfg( &audioamp5 );
    log_printf( &logger, "** Audio Amp 5 is initialized **\r\n" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    //  Task implementation.
    
    audioamp5_gain_select( &audioamp5, AUDIOAMP5_GAIN_26DB );
    audioamp5_config_update( &audioamp5 );
    log_printf( &logger, "** Gain value is 26dB **\r\n" );    

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    audioamp5_gain_select( &audioamp5, AUDIOAMP5_GAIN_20DB );
    audioamp5_config_update( &audioamp5 );
    log_printf( &logger, "** Gain value is 20dB **\r\n" );  
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
