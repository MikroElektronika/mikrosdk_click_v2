/*!
 * @file main.c
 * @brief USB UART ISO Click Example.
 *
 * # Description
 * This example demonstrates the use of USB UART ISO click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Any data which the host PC sends via UART Terminal
 * will be sent over USB to the click board and then it will be read and 
 * echoed back by the MCU to the PC where the terminal program will display it.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbuartiso.h"

static usbuartiso_t usbuartiso;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuartiso_cfg_t usbuartiso_cfg;  /**< Click config object. */

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
    usbuartiso_cfg_setup( &usbuartiso_cfg );
    USBUARTISO_MAP_MIKROBUS( usbuartiso_cfg, MIKROBUS_1 );
    if ( UART_ERROR == usbuartiso_init( &usbuartiso, &usbuartiso_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    usbuartiso_default_cfg ( &usbuartiso );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    char rx_data = 0;
    if ( usbuartiso_generic_read ( &usbuartiso, &rx_data, 1 ) )
    {
        if ( usbuartiso_generic_write ( &usbuartiso, &rx_data, 1 ) )
        {
            log_printf( &logger, "%c", rx_data );
        }
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
