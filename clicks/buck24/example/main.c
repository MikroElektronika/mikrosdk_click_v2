/*!
 * @file main.c
 * @brief Buck 24 Click example
 *
 * # Description
 * This example demonstrates the use of the Buck 24 Click board by monitoring the output voltage, 
 * current, and power via I2C communication. It also checks the Power-Good (PG) status pin to detect 
 * undervoltage conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board driver, and applies the default configuration.
 *
 * ## Application Task
 * Checks if the Power-Good (PG) pin is active and logs an undervoltage warning if triggered.
 * Reads and logs the average voltage, current, and power values from the device every second.
 *
 * @note
 * Use an on-board VOUT SEL switch to select the buck output voltage level (1.0V, 1.8V, 2.5V, 3.3V).
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck24.h"

static buck24_t buck24;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck24_cfg_t buck24_cfg;  /**< Click config object. */

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
    buck24_cfg_setup( &buck24_cfg );
    BUCK24_MAP_MIKROBUS( buck24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck24_init( &buck24, &buck24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK24_ERROR == buck24_default_cfg ( &buck24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    buck24_data_t buck;

    if ( !buck24_get_pg_pin ( &buck24 ) )
    {
        log_printf( &logger, " Undervoltage: below 90%% of nominal voltage\r\n" );
    }

    if ( BUCK24_OK == buck24_read_data_avg ( &buck24, BUCK24_DEFAULT_NUM_CONV, &buck ) )
    {
        log_printf( &logger, " Voltage: %.3f V\r\n", buck.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", buck.current );
        log_printf( &logger, " Power: %.2f W\r\n\n", buck.power );
    }

    Delay_ms ( 1000 );
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
