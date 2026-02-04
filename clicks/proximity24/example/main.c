/*!
 * @file main.c
 * @brief Proximity 24 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 24 Click board by reading and 
 * displaying the proximity and ALS data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the proximity and ALS data and displays the results on the USB UART every 200ms.
 * The higher the proximity value, the closer the detected object.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity24.h"

static proximity24_t proximity24;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity24_cfg_t proximity24_cfg;  /**< Click config object. */

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
    proximity24_cfg_setup( &proximity24_cfg );
    PROXIMITY24_MAP_MIKROBUS( proximity24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity24_init( &proximity24, &proximity24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY24_ERROR == proximity24_default_cfg ( &proximity24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t ps_data = 0;
    uint16_t als_data = 0;
    uint16_t white_data = 0;
    if ( PROXIMITY24_OK == proximity24_read_proximity ( &proximity24, &ps_data ) )
    {
        log_printf ( &logger, " PS data: %u\r\n", ps_data );
    }
    if ( PROXIMITY24_OK == proximity24_read_als_data ( &proximity24, &als_data ) )
    {
        log_printf ( &logger, " ALS data: %.1f lux\r\n", als_data * proximity24.als_sens );
    }
    if ( PROXIMITY24_OK == proximity24_read_white_data ( &proximity24, &white_data ) )
    {
        log_printf ( &logger, " White data: %u\r\n\n", white_data );
    }
    Delay_ms ( 200 );
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
