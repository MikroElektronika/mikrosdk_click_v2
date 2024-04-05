/*!
 * @file main.c
 * @brief FTDI Click Example.
 *
 * # Description
 * This example demonstrates the use of FTDI click by echoing back all the received messages.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Any data which the host PC sends to the Virtual COM Port (for example, typed into the terminal 
 * window in UART Terminal) will be sent over USB to the click board and then it will be read and 
 * echoed back by the MCU to the PC where the terminal program will display it. The data will also
 * be displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ftdi.h"

static ftdi_t ftdi;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ftdi_cfg_t ftdi_cfg;  /**< Click config object. */

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
    ftdi_cfg_setup( &ftdi_cfg );
    FTDI_MAP_MIKROBUS( ftdi_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ftdi_init( &ftdi, &ftdi_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t rx_data = 0;
    if ( ftdi_generic_read ( &ftdi, &rx_data, 1 ) > 0 )
    {
        ftdi_generic_write ( &ftdi, &rx_data, 1 );
        log_printf( &logger, "%c", rx_data );
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
