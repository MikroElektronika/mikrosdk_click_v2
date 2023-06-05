/*!
 * @file main.c
 * @brief Illuminance Click example
 *
 * # Description
 * This example demonstrates the use of Illuminance click board by reading
 * and displaying the RAW channels data measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the RAW channels data measurements
 * and displays the results on the USB UART. By default, the data ready interrupt triggers 
 * upon every ADC cycle which will be performed every 200ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "illuminance.h"

static illuminance_t illuminance;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    illuminance_cfg_t illuminance_cfg;  /**< Click config object. */

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
    illuminance_cfg_setup( &illuminance_cfg );
    ILLUMINANCE_MAP_MIKROBUS( illuminance_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == illuminance_init( &illuminance, &illuminance_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ILLUMINANCE_ERROR == illuminance_default_cfg ( &illuminance ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !illuminance_get_int_pin ( &illuminance ) )
    {
        uint16_t ch0 = 0;
        uint16_t ch1 = 0;
        if ( ILLUMINANCE_OK == illuminance_read_raw_data ( &illuminance, &ch0, &ch1 ) )
        {
            log_printf ( &logger, " CH0: %u\r\n", ch0 );
            log_printf ( &logger, " CH1: %u\r\n\n", ch1 );
        }
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
