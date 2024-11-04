/*!
 * \file 
 * \brief Mcp16331 Click example
 * 
 * # Description
 * This application is buck-boost voltage regulator.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Sends hal pointers, and initializes Click
 * 
 * ## Application Task  
 * Switches between 5 V and 12 V values
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp16331.h"

// ------------------------------------------------------------------ VARIABLES

static mcp16331_t mcp16331;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp16331_cfg_t cfg;

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

    mcp16331_cfg_setup( &cfg );
    MCP16331_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp16331_init( &mcp16331, &cfg );
}

void application_task ( void )
{
    mcp16331_set_vout( &mcp16331, 5000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    mcp16331_set_vout( &mcp16331, 12000 );
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
