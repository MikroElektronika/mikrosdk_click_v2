/*!
 * \file 
 * \brief TempHum12 Click example
 * 
 * # Description
 * This application measures temperature and humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and configuration device for measurement.
 * 
 * ## Application Task  
 * Reads Temperature and Humidity data and this data logs to the USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum12.h"

// ------------------------------------------------------------------ VARIABLES

static temphum12_t temphum12;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum12_cfg_t cfg;
    uint16_t tmp;
    uint8_t read_reg[ 2 ];

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

    temphum12_cfg_setup( &cfg );
    TEMPHUM12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum12_init( &temphum12, &cfg );

    temphum12_default_cfg( &temphum12 );
    
    Delay_ms( 1500 );
    log_printf( &logger, "--- Start measurement ----\r\n" );
}

void application_task ( void )
{
    float temperature;
    float humidity;

    temperature = temphum12_get_temperature( &temphum12, 
                                             TEMPHUM12_TEMP_IN_CELSIUS );

    log_printf( &logger, "Temperature: %.2f \r\n", temperature );
    Delay_1sec( );
    
    humidity = temphum12_get_humidity( &temphum12 );

    log_printf( &logger, "Humidity: %.2f \r\n", humidity );
    
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_1sec( );
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
