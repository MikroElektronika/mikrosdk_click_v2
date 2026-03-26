/*!
 * @file main.c
 * @brief Thermo 31 Click example
 *
 * # Description
 * This example demonstrates the use of the Thermo 31 Click board for
 * temperature measurement. The application reads temperature data via
 * the I2C interface and displays the measured value on the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Thermo 31 Click driver, applies the default
 * configuration, and reads the device unique identifier.
 *
 * ## Application Task
 * Periodically reads the temperature value from the sensor and logs the
 * result to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo31.h"

static thermo31_t thermo31;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo31_cfg_t thermo31_cfg;  /**< Click config object. */

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
    thermo31_cfg_setup( &thermo31_cfg );
    THERMO31_MAP_MIKROBUS( thermo31_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo31_init( &thermo31, &thermo31_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO31_ERROR == thermo31_default_cfg ( &thermo31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint16_t unique_id[ 3 ] = { 0 };
    if ( THERMO31_OK == thermo31_read_unique_id ( &thermo31, unique_id ) )
    {
        log_printf ( &logger, " Device Unique ID: 0x%.2X%.2X%.2X\r\n", 
                     unique_id[ 0 ], unique_id[ 1 ], unique_id[ 2 ] );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    if ( THERMO31_OK == thermo31_read_temperature ( &thermo31, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
    }
    Delay_ms ( 500 );
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
