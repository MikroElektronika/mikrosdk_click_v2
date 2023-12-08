/*!
 * \file 
 * \brief 3DHall3 Click example
 * 
 * # Description
 * This example returns values of X,Y and Z axes.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and sets basic configuration.
 * 
 * ## Application Task  
 * Reads the values of the X,Y and Z axes.
 * 
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3dhall3.h"

// ------------------------------------------------------------------ VARIABLES

static c3dhall3_t c3dhall3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall3_cfg_t cfg;

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

    c3dhall3_cfg_setup( &cfg );
    C3DHALL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall3_init( &c3dhall3, &cfg );
    c3dhall3_default_cfg ( &c3dhall3 );
    log_info( &logger, "---- System Init ----" );
}

void application_task ( void )
{
    int16_t axes_xyz[ 3 ]; 
    
    c3dhall3_read_xyz( &c3dhall3, axes_xyz );
    log_printf( &logger, "X: %d \r\n", axes_xyz[ 0 ] );
    log_printf( &logger, "Y: %d \r\n", axes_xyz[ 1 ] );
    log_printf( &logger, "Z: %d \r\n", axes_xyz[ 2 ] );

    Delay_ms( 500 );
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
