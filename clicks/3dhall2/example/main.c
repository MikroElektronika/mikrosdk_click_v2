/*!
 * \file 
 * \brief C3dHall2 Click example
 * 
 * # Description
 * 
 * This application reads X/Y/Z hall axis and temperature
 * data and converts it to human readable format.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the Click board.
 * 
 * ## Application Task  
 * Reads X/Y/Z hall axis and Temperature data.
 * All data logs on the USBUART every 200ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3dhall2.h"

// ------------------------------------------------------------------ VARIABLES

static c3dhall2_t c3dhall2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall2_cfg_t cfg;

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

    c3dhall2_cfg_setup( &cfg );
    C3DHALL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall2_init( &c3dhall2, &cfg );
    c3dhall2_default_cfg( &c3dhall2 );

}

void application_task ( void )
{
    float xyz_axis[ 3 ] = { 0 };
    float temperature = 0;
    if ( C3DHALL2_OK == c3dhall2_get_axis_temp_data( &c3dhall2, &xyz_axis[ 0 ], &temperature ) )
    {
        log_printf( &logger, " Axis X: %.2f mT\r\n", xyz_axis[ 0 ] );
        log_printf( &logger, " Axis Y: %.2f mT\r\n", xyz_axis[ 1 ] );
        log_printf( &logger, " Axis Z: %.2f mT\r\n", xyz_axis[ 2 ] );
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
        Delay_ms ( 200 );
    }
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
