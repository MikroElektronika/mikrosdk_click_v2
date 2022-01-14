/*!
 * @file main.c
 * @brief UVA Click example
 *
 * # Description
 * This example demonstrates the use of UVA click board by reading and displaying
 * the UVA data measurement results.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and applies the click default configuration.
 *
 * ## Application Task
 * Reads the UVA data measurements every 100ms and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "uva.h"

static uva_t uva;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uva_cfg_t uva_cfg;  /**< Click config object. */

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
    uva_cfg_setup( &uva_cfg );
    UVA_MAP_MIKROBUS( uva_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == uva_init( &uva, &uva_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UVA_ERROR == uva_default_cfg ( &uva ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t uva_data = 0;
    if ( UVA_OK == uva_read_data ( &uva, &uva_data ) )
    {
        log_printf ( &logger, " UVA data: %u \r\n\n", uva_data );
        Delay_ms ( 100 );
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
