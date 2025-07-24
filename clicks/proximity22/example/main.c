/*!
 * @file main.c
 * @brief Proximity 22 Click example
 *
 * # Description
 * This example demonstrates the use of the Proximity 22 Click board by reading
 * and displaying proximity, ambient light (ALS), and temperature measurements.
 * The data is read only when a new measurement is ready, indicated by an interrupt.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Proximity 22 Click driver, then sets the default configuration.
 *
 * ## Application Task
 * Waits for a data ready interrupt and then reads the proximity, temperature,
 * and ALS data (red, green, blue, and clear channels), displaying the results via UART
 * approximately every 200 ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity22.h"

static proximity22_t proximity22;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity22_cfg_t proximity22_cfg;  /**< Click config object. */

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
    proximity22_cfg_setup( &proximity22_cfg );
    PROXIMITY22_MAP_MIKROBUS( proximity22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity22_init( &proximity22, &proximity22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY22_ERROR == proximity22_default_cfg ( &proximity22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    proximity22_data_t meas_data;

    // Wait for a data ready interrupt
    while ( proximity22_get_int_pin ( &proximity22 ) );

    if ( PROXIMITY22_OK == proximity22_read_data ( &proximity22, &meas_data ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n", meas_data.proximity );
        log_printf ( &logger, " Temperature: %.1f degC\r\n", meas_data.temperature );
        log_printf ( &logger, " ALS data (RGBC): %u;%u;%u;%u\r\n\n", meas_data.als.red, 
                                                                     meas_data.als.green, 
                                                                     meas_data.als.blue, 
                                                                     meas_data.als.clear );
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
