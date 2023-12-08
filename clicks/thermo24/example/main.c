/*!
 * @file main.c
 * @brief Thermo24 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 24 click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, then performs the software reset of the click board 
 * and reads and displays its serial number.
 *
 * ## Application Task
 * Reads the temperature measurement in Celsius and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo24.h"

static thermo24_t thermo24;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo24_cfg_t thermo24_cfg;  /**< Click config object. */

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
    thermo24_cfg_setup( &thermo24_cfg );
    THERMO24_MAP_MIKROBUS( thermo24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo24_init( &thermo24, &thermo24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO24_ERROR == thermo24_soft_reset ( &thermo24 ) )
    {
        log_error( &logger, " Software reset." );
        for ( ; ; );
    }

    uint32_t serial_num;
    if ( THERMO24_OK == thermo24_read_serial ( &thermo24, &serial_num ) )
    {
        log_printf ( &logger, " Serial Number: 0x%.8LX\r\n", serial_num );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature;
    if ( THERMO24_OK == thermo24_read_temperature ( &thermo24, THERMO24_MEASURE_PRECISION_HIGH, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
