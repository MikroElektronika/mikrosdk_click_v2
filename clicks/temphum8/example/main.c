/*!
 * \file 
 * \brief TempHum8 Click example
 * 
 * # Description
 * This demo-app shows the temperature measurement procedure using Temp&Hum 8 Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring Clicks and log objects. 
 * Setting the Click in the default configuration to start the measurement, 
 * and before that call function software_reset().
 * 
 * ## Application Task  
 * Reads ambient temperature data and Relative Huminidy data, 
 * this data logs to USBUART every 1500ms.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum8.h"

// ------------------------------------------------------------------ VARIABLES

static temphum8_t temphum8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum8_cfg_t cfg;

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

    temphum8_cfg_setup( &cfg );
    TEMPHUM8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum8_init( &temphum8, &cfg );

    temphum8_software_reset( &temphum8 );
    temphum8_default_cfg( &temphum8 ); 
}

void application_task ( void )
{
    float temperature;
    float humidity;

    //  Task implementation.
    
    log_printf( &logger, "\r\n ---- Ambient data ----\r\n" );

    temperature = temphum8_get_temperature_data( &temphum8, TEMPHUM8_TEMPERATURE_IN_CELSIUS );
    log_printf( &logger, "** Temperature: %.2f °C \r\n", temperature );
    
    humidity = temphum8_get_humidity_data( &temphum8 );
    log_printf( &logger, "** Humidity: %.2f %%RH \r\n", humidity );

    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
