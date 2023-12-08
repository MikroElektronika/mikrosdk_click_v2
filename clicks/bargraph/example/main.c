/*!
 * \file 
 * \brief BarGraph Click example
 * 
 * # Description
 * This application uses a high-quality bar graph LED display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and BarGraph init.
 * 
 * ## Application Task  
 * Counter passes through the loop and logs the value of the counter on the bargraph display.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "bargraph.h"

// ------------------------------------------------------------------ VARIABLES

static bargraph_t bargraph;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    bargraph_cfg_t cfg;

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

    bargraph_cfg_setup( &cfg );
    BARGRAPH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph_init( &bargraph, &cfg );
    bargraph_reset( &bargraph );
}

void application_task ( void )
{
    uint8_t cnt = 0;
    
    for ( cnt = 0; cnt <= 10; cnt++ )
    {
        bargraph_display( &bargraph, cnt );
        Delay_ms( 500 );
    }
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
