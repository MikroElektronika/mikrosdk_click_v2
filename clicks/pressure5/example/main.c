/*!
 * \file 
 * \brief Pressure5 Click example
 * 
 * # Description
 * This example preforms Temperature and Pressure measurement.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, test comunication, software reset, update
 * coefficient and configuration module for start measurement.
 * 
 * ## Application Task  
 * Reads Pressure data in [mBar] and Temperature data in [C]. 
 * Logs all data to the USBUART every 2 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure5.h"

// ------------------------------------------------------------------ VARIABLES

static pressure5_t pressure5;
static log_t logger;

static float temperature;
static float pressure;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure5_cfg_t cfg;
    PRESSURE5_RETVAL init_ret;

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

    pressure5_cfg_setup( &cfg );
    PRESSURE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure5_init( &pressure5, &cfg );
    pressure5_default_cfg( &pressure5 );
}

void application_task ( void )
{
    //  Task implementation.

    temperature = pressure5_get_temperature_data ( &pressure5 );
    log_printf( &logger, "Temperature: %.2f C\r\n", temperature );
    
    pressure = pressure5_get_pressure_data ( &pressure5 );
    log_printf( &logger, "Pressure: %.2f mBar\r\n ", pressure );
    log_printf( &logger, "\r\n" );
    
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
