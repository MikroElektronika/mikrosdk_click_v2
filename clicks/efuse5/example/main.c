/*!
 * @file main.c
 * @brief eFuse 5 Click example
 *
 * # Description
 * This library contains API for the eFuse 5 Click driver.
 * This driver provides the functions to set the current limiting conditions 
 * to provide the threshold of the fault conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the eFuse 5 Click board™.
 * In this example, the app sets the current limit to 600 mA for 10 seconds 
 * and then sets the current limit to 1200 mA for the next 10 seconds
 * to protect the electrical circuit against excessive current.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "efuse5.h"

static efuse5_t efuse5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse5_cfg_t efuse5_cfg;  /**< Click config object. */

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
    efuse5_cfg_setup( &efuse5_cfg );
    EFUSE5_MAP_MIKROBUS( efuse5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == efuse5_init( &efuse5, &efuse5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE5_ERROR == efuse5_default_cfg( &efuse5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
}

void application_task ( void ) 
{
    if ( EFUSE5_OK == efuse5_set_current_limit( &efuse5, EFUSE5_CURRENT_LIMIT_600_mA ) )
    {
        log_printf( &logger, "  Current limit:  600 mA   \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    Delay_ms( 10000 );
    
    if ( EFUSE5_OK == efuse5_set_current_limit( &efuse5, EFUSE5_CURRENT_LIMIT_1200_mA ) )
    {
        log_printf( &logger, "  Current limit: 1200 mA   \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    Delay_ms( 10000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
