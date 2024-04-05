/*!
 * @file main.c
 * @brief Pressure 21 Click example
 *
 * # Description
 * This example demonstrates the use of Pressure 21 click board by reading and displaying
 * the pressure and temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt and then reads the pressure and temperature data
 * and displays them on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure21.h"

static pressure21_t pressure21;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure21_cfg_t pressure21_cfg;  /**< Click config object. */

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
    pressure21_cfg_setup( &pressure21_cfg );
    PRESSURE21_MAP_MIKROBUS( pressure21_cfg, MIKROBUS_1 );
    err_t init_flag = pressure21_init( &pressure21, &pressure21_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE21_ERROR == pressure21_default_cfg ( &pressure21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( pressure21_get_int_pin ( &pressure21 ) )
    {
        float pressure, temperature;
        if ( PRESSURE21_OK == pressure21_get_sensor_data ( &pressure21, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.2f mBar\r\n", pressure * PRESSURE21_PA_TO_MBAR );
            log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
        }
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
