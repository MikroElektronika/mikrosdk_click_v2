/*!
 * @file main.c
 * @brief Pressure 25 Click example
 *
 * # Description
 * This example demonstrates the use of the Pressure 25 Click board for
 * measuring pressure and temperature data. The application reads sensor
 * values via the I2C interface and displays the measured results on
 * the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Pressure 25 Click driver.
 *
 * ## Application Task
 * Periodically reads pressure and temperature values from the sensor and
 * logs the results to the serial terminal.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure25.h"

#ifndef MIKROBUS_POSITION_PRESSURE25
    #define MIKROBUS_POSITION_PRESSURE25 MIKROBUS_1
#endif

static pressure25_t pressure25;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure25_cfg_t pressure25_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    pressure25_cfg_setup( &pressure25_cfg );
    PRESSURE25_MAP_MIKROBUS( pressure25_cfg, MIKROBUS_POSITION_PRESSURE25 );
    if ( PRESSURE25_ERROR == pressure25_init( &pressure25, &pressure25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float pressure = 0.0f;
    float temperature = 0.0f;

    if ( PRESSURE25_OK == pressure25_get_press_temp( &pressure25, &pressure, &temperature ) )
    {
        log_printf( &logger, " Pressure: %.2f kPa\r\n", pressure );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", temperature );
    }
    else
    {
        log_error( &logger, " Error reading data.\r\n" );
    }
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
