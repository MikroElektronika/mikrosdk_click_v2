/*!
 * @file main.c
 * @brief PAC1720 Click example
 *
 * # Description
 * This example demonstrates the use of PAC1720 click board by reading the voltage, 
 * current, and power from both available channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the voltage, current, and power from both channels and displays 
 * the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pac1720.h"

static pac1720_t pac1720;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pac1720_cfg_t pac1720_cfg;  /**< Click config object. */

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
    pac1720_cfg_setup( &pac1720_cfg );
    PAC1720_MAP_MIKROBUS( pac1720_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pac1720_init( &pac1720, &pac1720_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PAC1720_ERROR == pac1720_default_cfg ( &pac1720 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0, current = 0, power = 0;
    
    if ( PAC1720_OK == pac1720_get_measurements ( &pac1720, PAC1720_CHANNEL_1, &voltage, &current, &power ) )
    {
        log_printf( &logger, " Channel 1:\r\n" );
        log_printf( &logger, " U: %.3fV, I: %.3fA, P: %.3fW\r\n", voltage, current, power );
    }
    
    if ( PAC1720_OK == pac1720_get_measurements ( &pac1720, PAC1720_CHANNEL_2, &voltage, &current, &power ) )
    {
        log_printf( &logger, " Channel 2:\r\n" );
        log_printf( &logger, " U: %.3fV, I: %.3fA, P: %.3fW\r\n\n", voltage, current, power  );
    }
    
    Delay_ms( 1000 );
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
