/*!
 * \file 
 * \brief Peltier Click example
 * 
 * # Description
 * This application is ultralow power energy harvester and battery charger.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver, disables both 1.8V and 3.3V outputs and starts write log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Peltier Click board by first enableing 1.8V output, second 
   by enableing 3.3V output, then enabling both outputs and finally disabling both outputs in 5 seconds intervals.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "peltier.h"

// ------------------------------------------------------------------ VARIABLES

static peltier_t peltier;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    peltier_cfg_t cfg;

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

    peltier_cfg_setup( &cfg );
    PELTIER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    peltier_init( &peltier, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "   1.8V output    \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_enable_ldo1( &peltier );
    peltier_disable_ldo2( &peltier );
    Delay_ms( 5000 );
    
    log_printf( &logger, "   3.3V output    \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_disable_ldo1( &peltier );
    peltier_enable_ldo2( &peltier );
    Delay_ms( 5000 );
    
    log_printf( &logger, "   Both outputs   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_enable_ldo1( &peltier );
    peltier_enable_ldo2( &peltier );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Disable  outputs \r\n" );
    log_printf( &logger, "------------------\r\n" );
    peltier_disable_ldo1( &peltier );
    peltier_disable_ldo2( &peltier );
    Delay_ms( 5000 );
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
