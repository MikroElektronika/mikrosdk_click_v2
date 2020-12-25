/*!
 * \file 
 * \brief MUX Click example
 * 
 * # Description
 * Sets the current active channel. Changes the channel every 5 sec.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO module and sets RST, CS and PWM pins as OUTPUT.
 * 
 * ## Application Task  
 * Changes currently active channel every 5 sec.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mux.h"

// ------------------------------------------------------------------ VARIABLES

static mux_t mux;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mux_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mux_cfg_setup( &cfg );
    MUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux_init( &mux, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "        MUX Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    mux_device_enable( &mux );
    log_printf( &logger, "    Enable MUX device\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint16_t n_cnt;
    
    for ( n_cnt = MUX_CHANNEL_1A_AND_1B; n_cnt < MUX_CHANNEL_END; n_cnt++ )
    {
        log_printf( &logger, "      CHANNEL  S%u\r\n", n_cnt );
        log_printf( &logger, "------------------------\r\n" );
        
        mux_active_mux_channel( &mux, n_cnt );
        Delay_ms( 5000 );
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
