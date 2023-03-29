/*!
 * @file main.c
 * @brief Thermo 27 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 27 Click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and reads the device id, and after that resets the device and 
 * performs default configuration.
 *
 * ## Application Task
 * Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
 * at a rate of once per second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo27.h"

static thermo27_t thermo27;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo27_cfg_t thermo27_cfg;  /**< Click config object. */

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
    thermo27_cfg_setup( &thermo27_cfg );
    THERMO27_MAP_MIKROBUS( thermo27_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo27_init( &thermo27, &thermo27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t device_id;
    thermo27_get_device_id( &thermo27, &device_id );
    if ( THERMO27_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( THERMO27_ERROR == thermo27_default_cfg( &thermo27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
   
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ======================= \r\n");
}

void application_task ( void ) 
{
    float temperature;
    uint8_t status;
    
    thermo27_get_alert_reg( &thermo27, &status );
    if ( THERMO27_DATA_READY_FLAG & status )
    {
        thermo27_read_temp( &thermo27, &temperature );
        log_printf( &logger, " Temperature: %f degC \r\n", temperature );
        log_printf( &logger, " ======================= \r\n");
    }
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
