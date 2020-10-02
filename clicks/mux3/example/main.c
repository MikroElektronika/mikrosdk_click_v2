/*!
 * \file 
 * \brief MUX 3 Click example
 * 
 * # Description
 * This application sets multiplexing one input channel to eight single-ended output channels. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of MUX 3 Click board.
 * Sets the current active and changes the channel every 1 sec.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on Usart Terminal changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mux3.h"

// ------------------------------------------------------------------ VARIABLES

static mux3_t mux3;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void display_log ( uint8_t sel_ch )
{
    log_printf( &logger, "     S %d", sel_ch );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mux3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    mux3_cfg_setup( &cfg );
    MUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux3_init( &mux3, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "------------------- \r\n " );
    log_printf( &logger, "  Enable Channel:   \r\n " );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S1 );
    //display_log( MUX3_ENABLE_CHANNEL_S1 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S1 );
    Delay_1sec( );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S2 );
    //display_log( MUX3_ENABLE_CHANNEL_S2 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S2 );
    Delay_1sec( );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S3 );
    //display_log( MUX3_ENABLE_CHANNEL_S3 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S3 );
    Delay_1sec( );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S4 );
    //display_log( MUX3_ENABLE_CHANNEL_S4 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S4 );
    Delay_1sec( );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S5 );
    //display_log( MUX3_ENABLE_CHANNEL_S5 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S5 );
    Delay_1sec( );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S6 );
    //display_log( MUX3_ENABLE_CHANNEL_S6 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S6 );
    Delay_1sec( );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S7 );
    //display_log( MUX3_ENABLE_CHANNEL_S7 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S7 );
    Delay_1sec( );

    log_printf( &logger, "S%d", MUX3_ENABLE_CHANNEL_S8 );
    //display_log( MUX3_ENABLE_CHANNEL_S8 );
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S8 );
    Delay_1sec( );
    
    log_printf( &logger, "------------------- \r\n " );
    log_printf( &logger, "      Disable       \r\n " );
    log_printf( &logger, "    All Channels    \r\n " );
    mux3_set_channel( &mux3, MUX3_DISABLE_ALL_CHANNELS );
    Delay_1sec( );
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
