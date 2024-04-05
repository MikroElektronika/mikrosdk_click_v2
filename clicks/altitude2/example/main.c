/*!
 * \file 
 * \brief Altitude2 Click example
 * 
 * # Description
 * This demo demonstrates the use of Altitude 2 Click to measure temperature, altitude and pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and performs the device reset,
 * after which the calibration coefficients will be read.
 * Determines the ratio value for temperature and pressure measurements.
 * Calibration coefficients are necessary to read after the device reset.
 * 
 * ## Application Task  
 * Gets temperature data in celsius value and pressure data in mbar value.
 * Gets the calculated altitude value in meters which depends on the temperature and pressure measurements.
 * Logs results on USBUART and repeats operation each second.
 * 
 * @note
 * Altitude is dependent from correct outside readings. It's calculated from pressure and temperature readings.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "altitude2.h"

// ------------------------------------------------------------------ VARIABLES

static altitude2_t altitude2;
static log_t logger;
float temperature;
float pressure;
float altitude;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude2_cfg_t cfg;

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

    altitude2_cfg_setup( &cfg );
    ALTITUDE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude2_init( &altitude2, &cfg );
    Delay_ms ( 500 );
    altitude2_reset( &altitude2 );
    
    altitude2_set_ratio ( &altitude2, ALTITUDE2_RATIO_2048, ALTITUDE2_RATIO_2048 );
    log_printf( &logger, "Altitude 2 is initialized\r\n" );
    Delay_ms ( 200 );
}

void application_task ( void )
{
    altitude2_read_data( &altitude2, &temperature, &pressure, &altitude );

    log_printf( &logger, "Temperature: %.2f Celsius\r\n", temperature );
    log_printf( &logger, "Pressure: %.2f mbar\r\n", pressure );
    log_printf( &logger, "Altitude: %.2f m\r\n", altitude );
    log_printf( &logger, "---------------------------------------\r\n\r\n" );

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
