/*!
 * \file 
 * \brief HallCurrent2 Click example
 * 
 * # Description
 * This application very accurately measures current using Hall effect.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and reset chip
 * 
 * ## Application Task  
 * Reads current and logs on usbuart every 1 second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallcurrent2.h"

// ------------------------------------------------------------------ VARIABLES

static hallcurrent2_t hallcurrent2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent2_cfg_t cfg;

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

    hallcurrent2_cfg_setup( &cfg );
    HALLCURRENT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent2_init( &hallcurrent2, &cfg );

    hallcurrent2_reset( &hallcurrent2 );
}

void application_task ( void )
{
    int16_t current_data;

    current_data = hallcurrent2_get_current( &hallcurrent2 );
    log_printf( &logger, "--- Current : %d mA\r\n", current_data );
    Delay_ms( 1000 );
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
