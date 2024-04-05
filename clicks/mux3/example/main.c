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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mux3_cfg_t cfg;

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

    mux3_cfg_setup( &cfg );
    MUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mux3_init( &mux3, &cfg );
}

void application_task ( void )
{
    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S1 );
    log_printf( &logger, "Active channel: S1\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S2 );
    log_printf( &logger, "Active channel: S2\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S3 );
    log_printf( &logger, "Active channel: S3\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S4 );
    log_printf( &logger, "Active channel: S4\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S5 );
    log_printf( &logger, "Active channel: S5\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S6 );
    log_printf( &logger, "Active channel: S6\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S7 );
    log_printf( &logger, "Active channel: S7\r\n" );
    Delay_1sec( );

    mux3_set_channel( &mux3, MUX3_ENABLE_CHANNEL_S8 );
    log_printf( &logger, "Active channel: S8\r\n" );
    Delay_1sec( );
    
    mux3_set_channel( &mux3, MUX3_DISABLE_ALL_CHANNELS );
    log_printf( &logger, "Active channel: none\r\n" );
    log_printf( &logger, "-------------------\r\n" );
    Delay_1sec( );
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
