/*!
 * @file main.c
 * @brief Pressure 22 Click example
 *
 * # Description
 * This library contains API for Pressure 22 Click driver.
 * The demo application reads and calculate pressure and temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Pressure 22 Click board™.
 * The demo application reads and displays the Pressure [mBar] 
 * and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure22.h"

static pressure22_t pressure22;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure22_cfg_t pressure22_cfg;  /**< Click config object. */

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
    pressure22_cfg_setup( &pressure22_cfg );
    PRESSURE22_MAP_MIKROBUS( pressure22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pressure22_init( &pressure22, &pressure22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE22_ERROR == pressure22_default_cfg ( &pressure22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ____________________ \r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{   
    static float temperature, pressure;
    if ( PRESSURE22_OK == pressure22_get_measurement_data( &pressure22, &temperature, &pressure ) )
    {
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " _______________________ \r\n" );
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
