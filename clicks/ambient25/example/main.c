/*!
 * @file main.c
 * @brief Ambient 25 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 25 Click by reading and displaying
 * the values from two modulator channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets
 * the ALS gain level to 32x and 4x for modulators 0 and 1.
 *
 * ## Application Task
 * Waits for a data ready interrupt then reads data from two modulator channels
 * and displays the results on the USB UART every 200ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient25.h"

static ambient25_t ambient25;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient25_cfg_t ambient25_cfg;  /**< Click config object. */

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
    ambient25_cfg_setup( &ambient25_cfg );
    AMBIENT25_MAP_MIKROBUS( ambient25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient25_init( &ambient25, &ambient25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT25_ERROR == ambient25_default_cfg ( &ambient25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    ambient25_data_t als_data;

    // Wait for a data ready interrupt
    while ( ambient25_get_int_pin ( &ambient25 ) );

    if ( AMBIENT25_OK == ambient25_read_data ( &ambient25, &als_data ) )
    {
        log_printf ( &logger, "\r\n ALS data 0: " );
        if ( AMBIENT25_ALS_DATA_SATURATION != als_data.als_data_0 )
        {
            log_printf ( &logger, "%u", als_data.als_data_0 );
        }
        else
        {
            log_printf ( &logger, "SATURATION" );
        }
        log_printf ( &logger, "\r\n ALS data 1: " );
        if ( AMBIENT25_ALS_DATA_SATURATION != als_data.als_data_1 )
        {
            log_printf ( &logger, "%u", als_data.als_data_1 );
        }
        else
        {
            log_printf ( &logger, "SATURATION" );
        }
        log_printf ( &logger, "\r\n" );
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
