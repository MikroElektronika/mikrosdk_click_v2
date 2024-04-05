/*!
 * @file main.c
 * @brief Pressure17 Click example
 *
 * # Description
 * This example demonstrates the use of Pressure 17 click board by reading and displaying 
 * the pressure and temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt and then reads the pressure [mbar] and temperature [C] data
 * and displays the results on the USB UART approximately every 200ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure17.h"

static pressure17_t pressure17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure17_cfg_t pressure17_cfg;  /**< Click config object. */

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
    pressure17_cfg_setup( &pressure17_cfg );
    PRESSURE17_MAP_MIKROBUS( pressure17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pressure17_init( &pressure17, &pressure17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE17_ERROR == pressure17_default_cfg ( &pressure17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !pressure17_get_int_pin ( &pressure17 ) )
    {
        float pressure, temperature;
        if ( PRESSURE17_OK == pressure17_read_data ( &pressure17, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.2f mbar\r\n Temperature: %.2f C\r\n\n", pressure, temperature );
        }
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
