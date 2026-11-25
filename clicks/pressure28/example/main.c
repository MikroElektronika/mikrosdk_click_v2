/*!
 * @file main.c
 * @brief Pressure 28 Click example
 *
 * # Description
 * This example demonstrates the use of the Pressure 28 Click board for measuring
 * gage pressure and temperature. The application starts a measurement session in
 * MODE1 and displays the results on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Restarts the measurement session, then reads and displays the pressure and
 * temperature results on the USB UART approximately once per second.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure28.h"

#ifndef MIKROBUS_POSITION_PRESSURE28
    #define MIKROBUS_POSITION_PRESSURE28 MIKROBUS_1
#endif

static pressure28_t pressure28;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure28_cfg_t pressure28_cfg;  /**< Click config object. */

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
    pressure28_cfg_setup( &pressure28_cfg );
    PRESSURE28_MAP_MIKROBUS( pressure28_cfg, MIKROBUS_POSITION_PRESSURE28 );
    err_t init_flag = pressure28_init( &pressure28, &pressure28_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE28_ERROR == pressure28_default_cfg ( &pressure28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;

    /* The device converts temperature only once per measurement session, so the
     * session is restarted to refresh the temperature result */
    if ( PRESSURE28_OK != pressure28_reset_device( &pressure28 ) )
    {
        log_printf( &logger, " Failed to reset device.\r\n" );
    }
    else if ( PRESSURE28_OK != pressure28_start_measurement( &pressure28, PRESSURE28_DEFAULT_MODE ) )
    {
        log_printf( &logger, " Failed to start measurement.\r\n" );
    }
    else
    {
        if ( PRESSURE28_OK == pressure28_read_pressure( &pressure28, &pressure ) )
        {
            log_printf( &logger, " Pressure: %.3f mmHg\r\n", pressure );
        }
        else
        {
            log_printf( &logger, " Failed to read pressure.\r\n" );
        }
        if ( PRESSURE28_OK == pressure28_read_temperature( &pressure28, &temperature ) )
        {
            log_printf( &logger, " Temperature: %.2f degC\r\n\n", temperature );
        }
        else
        {
            log_printf( &logger, " Failed to read temperature.\r\n" );
        }
    }

    Delay_ms( 1000 );
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
