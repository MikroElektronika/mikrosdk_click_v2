/*!
 * @file main.c
 * @brief Thermo22 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 22 Click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which
 * enables continuous conversation and sets the overtemperature limits to 35.0 Celsius.
 *
 * ## Application Task
 * Reads the temperature measurement in Celsius and displays the results on the USB UART
 * every 200ms approximately. It also checks the overtemperature alert indicator and displays
 * an appropriate message if the indicator is active.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo22.h"

static thermo22_t thermo22;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo22_cfg_t thermo22_cfg;  /**< Click config object. */

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
    thermo22_cfg_setup( &thermo22_cfg );
    THERMO22_MAP_MIKROBUS( thermo22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo22_init( &thermo22, &thermo22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO22_ERROR == thermo22_default_cfg ( &thermo22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature;
    if ( THERMO22_OK == thermo22_read_temperature ( &thermo22, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f C \r\n\n", temperature );
        if ( !thermo22_get_int_pin ( &thermo22 ) )
        {
            log_printf ( &logger, " Over temperature alert! \r\n\n" );
        }
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
