/*!
 * \file main.c
 * \brief Altitude Click example
 *
 * # Description
 * This is a example which demonstrates the use of Altitude Click board.
 * This demo example offers the altitude [m], pressure [mbar] and temperature
 * [deg C] measurements from sensor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and all used pins, performs a default configuration
 * for Altitude Click board and initializes the uart console for results
 * logging.
 *
 * ## Application Task
 * Shows two different uses of sensor, altimeter and barometer mode.
 * Reads the altitude, pressure and temperature results in standard units and
 * sends this results to the console.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "altitude.h"


// ------------------------------------------------------------------ VARIABLES

static altitude_t altitude;
static log_t console;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    altitude_cfg_t altitude_cfg;
    log_cfg_t log_cfg;

    //  Click initialization.
    altitude_cfg_setup( &altitude_cfg );
    ALTITUDE_MAP_MIKROBUS( altitude_cfg, MIKROBUS_1 );
    altitude_init( &altitude, &altitude_cfg );
    altitude_default_cfg( &altitude );

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
    log_init( &console, &log_cfg );
    log_printf( &console, "***  Altitude initialization done  ***\r\n" );
    log_printf( &console, "**************************************\r\n" );
}

void application_task( void )
{
    float altitude_result;
    float pressure_result;
    float temperature_result;

    //  Altimeter sensor mode for altitude data reading.
    altitude_set_sensor_mode( &altitude, ALTITUDE_SENSMOD_ALTIMETER );
    Delay_ms( 100 );

    while ( 0 == altitude_get_drdy_status( &altitude, ALTITUDE_STATUS_FLAG_PDR ) );

    altitude_result = altitude_get_altitude( &altitude );

    //  Barometer sensor mode for pressure data reading.
    altitude_set_sensor_mode( &altitude, ALTITUDE_SENSMOD_BAROMETER );
    Delay_ms( 100 );

    while ( 0 == altitude_get_drdy_status( &altitude, ALTITUDE_STATUS_FLAG_PDR ) );

    pressure_result = altitude_get_pressure( &altitude );
    temperature_result = altitude_get_temperature( &altitude );

    log_printf( &console, "** Altitude is %.2f m\r\n", altitude_result );
    log_printf( &console, "** Pressure is %.2f mbar\r\n", pressure_result );
    log_printf( &console, "** Temperature is %.2f Celsius\r\n", temperature_result );
    log_printf( &console, "**************************************\r\n" );
}

void main( void )
{
    application_init( );
    
    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
