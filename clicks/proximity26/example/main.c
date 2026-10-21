/*!
 * @file main.c
 * @brief Proximity 26 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 26 Click board by reading and 
 * displaying the proximity data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the proximity data and displays the results on the USB UART every 200ms.
 * The proximity data is a relative value, the higher the value the closer the detected object.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity26.h"

#ifndef MIKROBUS_POSITION_PROXIMITY26
    #define MIKROBUS_POSITION_PROXIMITY26 MIKROBUS_1
#endif

static proximity26_t proximity26;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity26_cfg_t proximity26_cfg;  /**< Click config object. */

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
    proximity26_cfg_setup( &proximity26_cfg );
    PROXIMITY26_MAP_MIKROBUS( proximity26_cfg, MIKROBUS_POSITION_PROXIMITY26 );
    if ( I2C_MASTER_ERROR == proximity26_init( &proximity26, &proximity26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY26_ERROR == proximity26_default_cfg ( &proximity26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t ps_data = 0;
    if ( PROXIMITY26_OK == proximity26_read_proximity ( &proximity26, &ps_data ) )
    {
        log_printf ( &logger, " PS data: %u\r\n\n", ps_data );
    }
    else
    {
        log_printf ( &logger, " Failed to read PS data\r\n\n" );
    }
    Delay_ms ( 200 );
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
