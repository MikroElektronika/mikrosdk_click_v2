/*!
 * @file main.c
 * @brief Thermo 29 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 29 click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the click default configuration which enables
 * continuous conversion and sets the conversion rate to 1 Hz with a data ready flag enabled on
 * the alert pin. After that, reads and displays the device 48-bit unique ID.
 *
 * ## Application Task
 * Waits for the data ready alert flag, then reads the temperature measurement in Celsius
 * and displays the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo29.h"

static thermo29_t thermo29;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo29_cfg_t thermo29_cfg;  /**< Click config object. */

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
    thermo29_cfg_setup( &thermo29_cfg );
    THERMO29_MAP_MIKROBUS( thermo29_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo29_init( &thermo29, &thermo29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO29_ERROR == thermo29_default_cfg ( &thermo29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint16_t unique_id[ 3 ];
    if ( THERMO29_OK == thermo29_read_unique_id ( &thermo29, unique_id ) )
    {
        log_printf ( &logger, " Device Unique ID: 0x%.2X%.2X%.2X\r\n", 
                     unique_id[ 0 ], unique_id[ 1 ], unique_id[ 2 ] );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature;
    // Wait for the data ready alert flag
    while ( thermo29_get_alert_pin ( &thermo29 ) );
    
    if ( ( THERMO29_OK == thermo29_clear_alert_status ( &thermo29 ) ) && 
         ( THERMO29_OK == thermo29_read_temperature ( &thermo29, &temperature ) ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
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
