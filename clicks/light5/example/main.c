/*!
 * @file main.c
 * @brief Light 5 Click example
 *
 * # Description
 * This example demonstrates the use of the Light 5 Click board for ambient
 * light measurement. The application waits for a data-ready interrupt and
 * then reads illuminance (lux) and wide-band light intensity values via the
 * I2C interface, displaying the results on the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Light 5 Click driver and applies the default
 * device configuration.
 *
 * ## Application Task
 * Waits for the interrupt signal indicating new measurement data and reads
 * light measurement results, which are then logged to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "light5.h"

static light5_t light5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light5_cfg_t light5_cfg;  /**< Click config object. */

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
    light5_cfg_setup( &light5_cfg );
    LIGHT5_MAP_MIKROBUS( light5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light5_init( &light5, &light5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT5_ERROR == light5_default_cfg ( &light5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    light5_data_t light_data;

    // Wait for a data ready interrupt
    while ( light5_get_int_pin ( &light5 ) );

    if ( LIGHT5_OK == light5_read_data ( &light5, &light_data ) )
    {
        log_printf ( &logger, "Light: %.1f lux\r\n", light_data.lux );
        log_printf ( &logger, "Wide Band: %.1f uW/cm2\r\n\n", light_data.wide_band );
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
