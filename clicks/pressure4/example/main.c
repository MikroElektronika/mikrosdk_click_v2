/*!
 * \file 
 * \brief Pressure4 Click example
 * 
 * # Description
 * This app measure barometric pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click board.
 * 
 * ## Application Task  
 * The pressure and temperature data is read from the sensor 
 * and it is printed to the UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure4.h"

// ------------------------------------------------------------------ VARIABLES

static pressure4_t pressure4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure4_cfg_t cfg;

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

    pressure4_cfg_setup( &cfg );
    PRESSURE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure4_init( &pressure4, &cfg );

    pressure4_default_cfg( &pressure4 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    double pressure;
    double temperature;

    temperature = pressure4_get_temperature( &pressure4 );
    log_printf( &logger, "Temperature : %.2lf \r\n", temperature );
    Delay_ms( 100 );
    
    pressure = pressure4_get_pressure( &pressure4 );
    log_printf( &logger, "Pressure : %.2lf hPa \r\n", pressure );
    log_printf( &logger, "========================\r\n" );

    Delay_ms( 500 );
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
