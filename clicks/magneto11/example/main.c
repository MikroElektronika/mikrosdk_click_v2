/*!
 * @file main.c
 * @brief Magneto11 Click example
 *
 * # Description
 * This example demonstrates the use of Magneto 11 Click board by reading and displaying
 * the magnetic field strength value.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the magnetic field strength value in milliTesla and displays the results on the USB UART
 * every 200ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneto11.h"

static magneto11_t magneto11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto11_cfg_t magneto11_cfg;  /**< Click config object. */

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
    magneto11_cfg_setup( &magneto11_cfg );
    MAGNETO11_MAP_MIKROBUS( magneto11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magneto11_init( &magneto11, &magneto11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO11_ERROR == magneto11_default_cfg ( &magneto11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float magnetic_field;
    if ( MAGNETO11_OK == magneto11_get_magnetic_field ( &magneto11, &magnetic_field ) )
    {
        log_printf ( &logger, " Magnetic Field: %.3f mT \r\n\n", magnetic_field );
        Delay_ms ( 200 );
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
