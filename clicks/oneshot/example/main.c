/*!
 * \file 
 * \brief OneShot Click example
 * 
 * # Description
 * This example shows the user how to configure and use the One Shot Click. The Click has a 
 * monostable monovibrator which cam generate a pulse of width between 1μs and 33.6 seconds. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and Click modules. Resistance data,
 * acquired from the AD5241, is displayed at the end of the initialization process. 
 * 
 * ## Application Task  
 * This function triggers one shot every 8 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oneshot.h"

// ------------------------------------------------------------------ VARIABLES

static oneshot_t oneshot;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    oneshot_cfg_t cfg;

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

    oneshot_cfg_setup( &cfg );
    ONESHOT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oneshot_init( &oneshot, &cfg );
    Delay_100ms( );
    oneshot_default_cfg( &oneshot );
    Delay_100ms( );
    log_printf( &logger, " * Resistance: %.1f Ohm\r\n", oneshot_get_resistance( &oneshot ) );
}

void application_task ( )
{
    oneshot_digital_write_cs( &oneshot, 1 );
    Delay_ms ( 1 );
    oneshot_digital_write_cs( &oneshot, 0 );
    log_printf( &logger, " * One shot triggered \r\n" );
    log_printf( &logger, " --------------------------- \r\n" );
    // 8 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
