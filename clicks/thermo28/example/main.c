/*!
 * @file main.c
 * @brief Thermo 28 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 28 click board™ 
 * by reading and displaying the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * This is an example that shows the use of a Thermo 28 click board™.
 * Reads the temperature measurement in degree Celsius and displays the results.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo28.h"

static thermo28_t thermo28;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo28_cfg_t thermo28_cfg;  /**< Click config object. */

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
    thermo28_cfg_setup( &thermo28_cfg );
    THERMO28_MAP_MIKROBUS( thermo28_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo28_init( &thermo28, &thermo28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );

    if ( THERMO28_ERROR == thermo28_default_cfg ( &thermo28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    float temperature;

    if ( THERMO28_OK == thermo28_get_temperature( &thermo28, &temperature ) )
    {
        log_printf( &logger, " Temperature [degC]: %.2f \r\n", temperature );
        Delay_ms( 1000 );
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
