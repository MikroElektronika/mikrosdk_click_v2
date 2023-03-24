/*!
 * @file main.c
 * @brief USB UART 5 Click Example.
 *
 * # Description
 * This example reads and processes data from USB UART 5 Click board™.
 * The library initializes and defines the UART bus drivers 
 * to transmit or receive data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver, wake-up module, and performs the default configuration.
 *
 * ## Application Task
 * Any data which the host PC sends via HidUartExample 
 * will be sent over USB to the click board and then it will be read and 
 * echoed back by the MCU to the PC where the terminal program will display it.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @note 
 * Make sure to download and install 
 * CP2110/4 Software package for Windows/Mac/Linux on the host PC.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbuart5.h"

static usbuart5_t usbuart5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart5_cfg_t usbuart5_cfg;  /**< Click config object. */

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
    usbuart5_cfg_setup( &usbuart5_cfg );
    USBUART5_MAP_MIKROBUS( usbuart5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == usbuart5_init( &usbuart5, &usbuart5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    usbuart5_default_cfg ( &usbuart5 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    char rx_data = 0;
    if ( usbuart5_generic_read ( &usbuart5, &rx_data, 1 ) )
    {
        if ( usbuart5_generic_write ( &usbuart5, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
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
