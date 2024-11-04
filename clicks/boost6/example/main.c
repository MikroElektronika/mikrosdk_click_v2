/*!
 * \file 
 * \brief Boost 6 Click example
 * 
 * # Description
 * This app enable or disable monolithic high-voltage switching regulator.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Boost 6 Click board.
 * Enable device 5000ms and disable device 5000ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost6.h"

// ------------------------------------------------------------------ VARIABLES

static boost6_t boost6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost6_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    boost6_cfg_setup( &cfg );
    BOOST6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost6_init( &boost6, &cfg );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, "  Boost 6 Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Hardware  Reset \r\n" );
    log_printf( &logger, "-----------------\r\n" );
    boost6_hw_reset ( &boost6 );
    Delay_100ms( );

    boost6_power_off(  &boost6  );
    log_printf( &logger, "     Disable     \r\n" );
    log_printf( &logger, "-----------------\r\n" );
    Delay_100ms( );
}

void application_task ( void )
{
    boost6_power_on( &boost6 );
    log_printf( &logger, "     Enable      \r\n" );
    log_printf( &logger, "-----------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    boost6_power_off(  &boost6  );
    log_printf( &logger, "     Disable     \r\n" );
    log_printf( &logger, "-----------------\r\n" );

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
