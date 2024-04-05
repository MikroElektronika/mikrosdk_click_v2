/*!
 * \file
 * \brief Thermo15 Click example
 *
 * # Description
 * This demo-app shows the temperature measurement procedure using Thermo 15 click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring clicks and log objects.
 * Setting the click in the default configuration to start the measurement.
 *
 * ## Application Task
 * Reads ambient temperature data and this data logs to USBUART every 1500ms.
 *
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo15.h"

// ------------------------------------------------------------------ VARIABLES

static thermo15_t thermo15;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo15_cfg_t cfg;

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

    thermo15_cfg_setup( &cfg );
    THERMO15_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo15_init( &thermo15, &cfg );

    thermo15_default_cfg ( &thermo15 );
    log_info( &logger, "---- Start measurement ----" );
}

void application_task ( void )
{
    float temperature;

    temperature = thermo15_get_temperature_data( &thermo15, THERMO15_TEMP_IN_CELSIUS );
    log_printf( &logger, "** Temperature: %.2f C \r\n", temperature );

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
