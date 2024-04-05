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
 * Configures the click board in Audio-to-Vibe mode.
 * 
 * ## Application Task  
 * An infinite loop.
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

void application_init ( void )
{
    log_cfg_t log_cfg;
    haptic_cfg_t cfg;

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

    haptic_cfg_setup( &cfg );
    HAPTIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    haptic_init( &haptic, &cfg );

    log_printf( &logger, " Configuring the click board...\r\n" );
    log_printf( &logger, "----------------------- \r\n" );
    
    haptic_enable( &haptic );
    haptic_set_mode( &haptic, HAPTIC_MODE_AUTOCAL );
    haptic_start_motor( &haptic );
    Delay_ms ( 500 );

    haptic_set_mode( &haptic, HAPTIC_MODE_AUDIOVIBE );
    haptic_enable_ac_coulping( &haptic );
    haptic_set_input_to_analog( &haptic );
    
    log_printf( &logger, " The click board is configured in Audio-to-Vibe mode...\r\n" );
}

void application_task ( void )
{
    // Nothing to do here...
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
