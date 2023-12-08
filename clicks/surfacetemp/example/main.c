/*!
 * \file 
 * \brief SurfaceTemp Click example
 * 
 * # Description
 * This example demonstrates the use of Surface Temp Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes the driver and configures the click board.
 * 
 * ## Application Task  
 * Reads the temperature in Celsius and displays the value on the USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "surfacetemp.h"

// ------------------------------------------------------------------ VARIABLES

static surfacetemp_t surfacetemp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    surfacetemp_cfg_t cfg;

    uint8_t status;

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

    surfacetemp_cfg_setup( &cfg );
    SURFACETEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    surfacetemp_init( &surfacetemp, &cfg );

    status = surfacetemp_setup( &surfacetemp );

    surfacetemp_set_high_threshold( &surfacetemp, 40.00 );
    surfacetemp_set_low_threshold( &surfacetemp, 10.00 );
    surfacetemp_set_critical_threshold( &surfacetemp, 70.00 );
    surfacetemp_set_hysteresis( &surfacetemp, 0 );

    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
    Delay_ms( 1000 );
}

void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( &surfacetemp );
    log_printf( &logger, "> Temperature : %.2f \r\n", temperature );
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
