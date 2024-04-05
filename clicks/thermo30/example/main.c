/*!
 * @file main.c
 * @brief Thermo 30 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 30 click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the device, and
 * starts the periodic measurements at 1 mps with high repeatability.
 *
 * ## Application Task
 * Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo30.h"

static thermo30_t thermo30;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo30_cfg_t thermo30_cfg;  /**< Click config object. */

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
    thermo30_cfg_setup( &thermo30_cfg );
    THERMO30_MAP_MIKROBUS( thermo30_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo30_init( &thermo30, &thermo30_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
   
    if ( THERMO30_ERROR == thermo30_default_cfg( &thermo30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}


void application_task ( void ) 
{
    float temperature;
    
    if ( THERMO30_OK == thermo30_read_temperature( &thermo30, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f deg C\r\n\n", temperature );
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
