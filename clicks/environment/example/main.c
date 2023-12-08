/*!
 * \file 
 * \brief Environment Click example
 * 
 * # Description
 * Example demonstrates use of the Environment click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - Device software reset, check device ID, set default configuration of BME680 chip, also display logs.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Environment Click board.
 * Measures temperature, humidity, pressure and gas resistance data from the BME680 chip sensor.
 * Displays ambient temperature data [ degrees Celsius ],
 * humidity data [ % ], pressure data [ mbar ] and gas resistance.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 2 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "environment.h"

// ------------------------------------------------------------------ VARIABLES

static environment_t environment;
static log_t logger;
static float temperature;
static float pressure;
static float humidity;
static int32_t gas;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    environment_cfg_t cfg;

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

    environment_cfg_setup( &cfg );
    ENVIRONMENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    environment_init( &environment , &cfg );
    environment_default_cfg( &environment );
}

void application_task ( void )
{
    //  Task implementation.

    temperature = environment_get_temperature( &environment);
    log_printf( &logger, " Temperature : %.2fC", temperature);

    humidity = environment_get_humidity( &environment );
    log_printf( &logger, "      Humidity : %f%%", humidity);

    pressure = environment_get_pressure( &environment );
    log_printf( &logger, "      Pressure : %.3fmbar", pressure);

    gas = environment_get_gas_resistance( &environment );
    log_printf( &logger, "      Gas Resistance : %ld\r\n", gas);

    Delay_ms( 2000 );
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
