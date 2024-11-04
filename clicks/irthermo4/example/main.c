/*!
 * @file main.c
 * @brief IR Thermo 4 Click example
 *
 * # Description
 * This example demonstrates the use of IR Thermo 4 Click board by reading and displaying
 * the ambient and object temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the ambient and object temperature measurements twice per second and displays
 * the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irthermo4.h"

static irthermo4_t irthermo4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo4_cfg_t irthermo4_cfg;  /**< Click config object. */

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
    irthermo4_cfg_setup( &irthermo4_cfg );
    IRTHERMO4_MAP_MIKROBUS( irthermo4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irthermo4_init( &irthermo4, &irthermo4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRTHERMO4_ERROR == irthermo4_default_cfg ( &irthermo4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float ambient_temp = 0;
    float object_temp = 0;
    if ( IRTHERMO4_OK == irthermo4_read_ambient_temp ( &irthermo4, &ambient_temp ) )
    {
        log_printf ( &logger, " Ambient temperature: %.2f degC\r\n", ambient_temp );
        if ( IRTHERMO4_OK == irthermo4_read_object_temp ( &irthermo4, &object_temp, ambient_temp ) )
        {
            log_printf ( &logger, " Object temperature: %.2f degC\r\n\n", object_temp );
        }
    }
    Delay_ms ( 500 );
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
