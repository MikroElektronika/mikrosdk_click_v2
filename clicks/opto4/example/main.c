/*!
 * \file 
 * \brief OPTO 4 Click example
 * 
 * # Description
 * This Click sets power on switch enabled and disabled.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init.
 * 
 * ## Application Task  
 * The Output voltage enable and disable every 3 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "opto4.h"

// ------------------------------------------------------------------ VARIABLES

static opto4_t opto4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto4_cfg_t cfg;

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

    opto4_cfg_setup( &cfg );
    OPTO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto4_init( &opto4, &cfg );
}

void application_task ( )
{
    opto4_output_enable( &opto4, OPTO4_OUTPUT_ENABLE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    opto4_output_enable( &opto4, OPTO4_OUTPUT_DISABLE );
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
