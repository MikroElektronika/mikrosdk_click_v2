/*!
 * @file main.c
 * @brief Color 12 Click example
 *
 * # Description
 * This library contains API for the Color 12 Click driver.
 * The demo application sets sensor configuration 
 * and reads and displays RGB/IR measurement results.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Color 12 Click board™.
 * Reads and displays the results of the RGB/IR measurements.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color12.h"

static color12_t color12;
static log_t logger;
static uint16_t color_data;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color12_cfg_t color12_cfg;  /**< Click config object. */

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
    color12_cfg_setup( &color12_cfg );
    COLOR12_MAP_MIKROBUS( color12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color12_init( &color12, &color12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR12_ERROR == color12_default_cfg ( &color12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_RED, &color_data ) )
    {
        log_printf( &logger, " Red : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_GREEN, &color_data ) )
    {
        log_printf( &logger, " Green : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_BLUE, &color_data ) )
    {
        log_printf( &logger, " Blue : %u\r\n", color_data );
    }
    
    if ( COLOR12_OK == color12_get_color_data( &color12, COLOR12_DATA_IR, &color_data ) )
    {
        log_printf( &logger, " IR : %u\r\n", color_data );
    }
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms( 1000 );
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
