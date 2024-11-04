/*!
 * \file 
 * \brief Step Down 2 Click example
 * 
 * # Description
 * This example showcases how to initialize and use the Step Down 2 Click. The Click is a 
 * step-down monolithic switching regulator able to deliver up to 2 A (DC).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and Click modules.
 * 
 * ## Application Task  
 * This function checks error input on the RST pin and reports if the device is working properly
 * or not. It does so every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stepdown2.h"

// ------------------------------------------------------------------ VARIABLES

static stepdown2_t stepdown2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    stepdown2_cfg_t cfg;

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

    stepdown2_cfg_setup( &cfg );
    STEPDOWN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stepdown2_init( &stepdown2, &cfg );

    stepdown2_digital_write_cs( &stepdown2, 1 );
    Delay_100ms( );
}

void application_task ( )
{
    if ( stepdown2_digital_read_rst( &stepdown2 ) )
    {
        log_printf( &logger, " * The device works as it should. *\r\n" );
    }
    else 
    {
        log_printf( &logger, " * The device does not work as it should. *\r\n" );
    }

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
