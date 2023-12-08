/*!
 * @file main.c
 * @brief Thermo 25 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 25 click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and checks the communication by setting the operating mode
 * to shutdown, reading and verifying the device ID, and switching back to the continuous mode.
 *
 * ## Application Task
 * Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo25.h"

static thermo25_t thermo25;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo25_cfg_t thermo25_cfg;  /**< Click config object. */

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
    thermo25_cfg_setup( &thermo25_cfg );
    THERMO25_MAP_MIKROBUS( thermo25_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo25_init( &thermo25, &thermo25_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO25_ERROR == thermo25_check_communication ( &thermo25 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature;
    if ( THERMO25_OK == thermo25_read_temperature ( &thermo25, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
        Delay_ms ( 1000 );
    }
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
