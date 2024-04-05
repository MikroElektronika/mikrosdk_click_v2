/*!
 * @file main.c
 * @brief Diff Press 3 Click Example.
 *
 * # Description
 * This library contains API for the Diff Press 3 Click driver.
 * This demo application shows an example of 
 * differential pressure and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C and ADC module and log UART.
 *
 * ## Application Task
 * This example demonstrates the use of the Diff Press 3 Click board™.
 * The demo application measures and display the Differential Pressure [kPa]
 * and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "diffpress3.h"

static diffpress3_t diffpress3;   /**< Diff Press 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress3_cfg_t diffpress3_cfg;  /**< Click config object. */

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
    diffpress3_cfg_setup( &diffpress3_cfg );
    DIFFPRESS3_MAP_MIKROBUS( diffpress3_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress3_init( &diffpress3, &diffpress3_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    float pressure, temperature;
    if ( DIFFPRESS3_OK == diffpress3_get_pressure( &diffpress3, &pressure ) )
    {
        log_printf( &logger, " Diff Pressure: %.3f [kPa]\r\n", pressure );
        Delay_ms ( 100 );
    }
    if ( DIFFPRESS3_OK == diffpress3_get_temperature( &diffpress3, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f [C]\r\n", temperature );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "---------------------\r\n" );
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
