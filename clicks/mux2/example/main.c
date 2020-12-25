/*!
 * \file 
 * \brief MUX 2 Click example
 * 
 * # Description
 * Sets the current active channel. Changes the channel every 5 sec.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO module and sets RST, CS, PWM and INT pins as OUTPUT.
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
#include "mux2.h"

// ------------------------------------------------------------------ VARIABLES

static mux2_t mux2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mux2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mux2_cfg_setup( &cfg );
    MUX2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux2_init( &mux2, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "       MUX 2 Click\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    
    mux2_device_enable( &mux2 );
    log_printf( &logger, "    Enable MUX device\r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t n_cnt;
    
    //  Task implementation.
    
    for ( n_cnt = MUX2_CHANNEL_S1; n_cnt < MUX2_CHANNEL_END; n_cnt++ )
    {
        log_printf( &logger, "      CHANNEL  S%d\r\n", ( uint16_t )n_cnt );
        log_printf( &logger, "------------------------\r\n" );
        
        mux2_active_mux_channel( &mux2, n_cnt );
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
