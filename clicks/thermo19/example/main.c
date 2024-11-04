/*!
 * @file main.c
 * @brief Thermo19 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 19 Click board by reading
 * and displaying the temperature in Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads and displays the temperature measured by the Click board on the USB UART
 * approximately every 400ms as this matches the required conversion time for 12-bit 
 * temperature resolution.
 *
 * @author Nikola Citakovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo19.h"

static thermo19_t thermo19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo19_cfg_t thermo19_cfg;  /**< Click config object. */

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
    thermo19_cfg_setup( &thermo19_cfg );
    THERMO19_MAP_MIKROBUS( thermo19_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thermo19_init( &thermo19, &thermo19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO19_ERROR == thermo19_default_cfg ( &thermo19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature;
    if ( THERMO19_OK == thermo19_read_temperature ( &thermo19, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
