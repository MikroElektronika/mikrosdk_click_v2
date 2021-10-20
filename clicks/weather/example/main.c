/*!
 * \file 
 * \brief Weather Click example
 * 
 * # Description
 * This demo-app shows the temperature, pressure and humidity measurement using Weather click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Setting the click in the default configuration to start the measurement.
 * 
 * ## Application Task  
 * Reads Temperature data, Relative Huminidy data and Pressure data, 
 * this data logs to USBUART every 1500ms.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "weather.h"

// ------------------------------------------------------------------ VARIABLES

static weather_t weather;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    weather_cfg_t cfg;

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

    weather_cfg_setup( &cfg );
    WEATHER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    weather_init( &weather, &cfg );

    weather_default_cfg( &weather );
}

void application_task ( void )
{
    weather_data_t weather_data;

    //  Task implementation.

    weather_get_ambient_data( &weather, &weather_data );

    log_printf( &logger, " \r\n ---- Weather data ----- \r\n" );
    log_printf( &logger, "[PRESSURE]: %.2f mBar.\n\r", weather_data.pressure );
    log_printf( &logger, "[TEMPERATURE]: %.2f C.\n\r", weather_data.temperature );
    log_printf( &logger, "[HUMIDITY]: %.2f %%.\n\r", weather_data.humidity );

    Delay_ms( 1500 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
