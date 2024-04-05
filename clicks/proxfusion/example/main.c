/*!
 * \file 
 * \brief ProxFusion Click example
 * 
 * # Description
 * This demo-app reads and displays touch events using ProxFusion click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Checks if a new touch event occurred and prints(logs) event message on usbuart.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proxfusion.h"

// ------------------------------------------------------------------ VARIABLES

static proxfusion_t proxfusion;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proxfusion_cfg_t proxfusion_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    proxfusion_cfg_setup( &proxfusion_cfg );
    PROXFUSION_MAP_MIKROBUS( proxfusion_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proxfusion_init( &proxfusion, &proxfusion_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXFUSION_ERROR == proxfusion_default_cfg ( &proxfusion ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t touch = proxfusion_get_touch( &proxfusion );
    if ( 1 == touch )
    {
        log_printf( &logger, " Touch button 1 is pressed\r\n" );
    }
    else if ( 2 == touch )
    {
        log_printf( &logger, " Touch button 2 is pressed\r\n" );
    }
    else if ( 3 == touch )
    {
        log_printf( &logger, " Both touch buttons are pressed\r\n" );
    }
    Delay_ms ( 100 );
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
