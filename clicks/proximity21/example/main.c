/*!
 * @file main.c
 * @brief Proximity 21 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 21 Click board by reading and displaying
 * the target distance in millimeters on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for a data ready interrupt, then reads the measurement results and logs
 * the target distance (millimeters) and signal quality (the higher the value the better
 * the signal quality) to the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity21.h"

static proximity21_t proximity21;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity21_cfg_t proximity21_cfg;  /**< Click config object. */

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
    proximity21_cfg_setup( &proximity21_cfg );
    PROXIMITY21_MAP_MIKROBUS( proximity21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity21_init( &proximity21, &proximity21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY21_ERROR == proximity21_default_cfg ( &proximity21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    proximity21_data_t results;
    // Wait for a data ready interrupt
    while ( proximity21_get_gpio1_pin ( &proximity21 ) );

    if ( PROXIMITY21_OK == proximity21_get_result ( &proximity21, &results ) )
    {
        log_printf( &logger, " Distance [mm]: %u\r\n", results.distance_mm );
        log_printf( &logger, " Signal [kcps/SPAD]: %u\r\n\n", results.signal_per_spad_kcps );
        proximity21_clear_interrupt ( &proximity21 );
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
