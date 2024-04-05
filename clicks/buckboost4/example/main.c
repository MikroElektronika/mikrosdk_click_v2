/*!
 * @file main.c
 * @brief Buck-Boost 4 Click example
 *
 * # Description
 * This example demonstrates the use of the Buck-Boost 4 Click board™.
 * This driver provides functions for device configurations and for the output voltage setting.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application sets the desired output voltage 
 * by cycling through a couple of voltage values.
 * Results are sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buckboost4.h"

static buckboost4_t buckboost4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buckboost4_cfg_t buckboost4_cfg;  /**< Click config object. */

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
    buckboost4_cfg_setup( &buckboost4_cfg );
    BUCKBOOST4_MAP_MIKROBUS( buckboost4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buckboost4_init( &buckboost4, &buckboost4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCKBOOST4_ERROR == buckboost4_default_cfg ( &buckboost4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "____________\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    for ( uint8_t vout = 1; vout < 21; vout++ )
    {
        if ( BUCKBOOST4_OK == buckboost4_set_vout( &buckboost4, ( float ) vout ) )
        {
            log_printf( &logger, " Vout: %dV\r\n", ( uint16_t ) vout );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
    log_printf( &logger, "____________\r\n" );
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
