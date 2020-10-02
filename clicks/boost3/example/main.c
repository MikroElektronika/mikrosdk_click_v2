/*!
 * \file 
 * \brief Boost 3 Click example
 * 
 * # Description
 * Boost 3 click provides an adjustable output voltage through the onboard
 * potentiometer. The chip is a 700-kHz pulse-width modulating (PWM) step-up 
 * converter with an 85-V switch FET with an input ranging from 2.5 V to 5.5 V. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO and LOG structures, and set CS pin as output.
 * 
 * ## Application Task  
 * Demonstrates use of Boost 3 click board by by reading 
 * user's command input from USART terminal and turning the
 * device on or off accordingly. User can use the on-board
 * potentiometer to adjust 'Vout' voltage.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost3.h"

// ------------------------------------------------------------------ VARIABLES

static boost3_t boost3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boost3_cfg_setup( &cfg );
    BOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost3_init( &boost3, &cfg );
}

void application_task ( void )
{
    char cmd;
    
    if ( log_read ( &logger, &cmd, 1 ) != -1)
    {
        cmd -= 48;
        boost3_dev_enable( &boost3, cmd );
        
        if ( cmd == BOOST3_ENABLE )
        {
             log_printf( &logger, "The device is turned on!\r\n" );
             log_printf( &logger, "Use on-board potentiometer\r\n" );
             log_printf( &logger, " to adjust 'Vout' voltage\r\n" );
        }
        else
        {
             log_printf( &logger, "The device is turned off!\r\n" );
        }
        Delay_ms( 10000 );
    }
    else
    {
        log_printf( &logger, "Send '1' to turn the device on\r\n" );
        log_printf( &logger, "Send '0' to turn the device off\r\n" );
        Delay_ms( 2000 );
    }
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
