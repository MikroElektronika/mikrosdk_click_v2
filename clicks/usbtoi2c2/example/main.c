/*!
 * @file main.c
 * @brief USBtoI2C2 Click example
 *
 * # Description
 * This example demonstrates the use of USB to I2C 2 Click by echoing back all
 * the received messages.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Any data which the host PC sends to the Virtual COM Port (for example, typed into the terminal 
 * window in UART Terminal) will be sent over USB to the Click board and then it will be read and 
 * echoed back by the MCU to the PC where the terminal program will display it.
 * 
 * @note 
 * Make sure to download and install appropriate VCP drivers on the host PC.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbtoi2c2.h"

static usbtoi2c2_t usbtoi2c2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbtoi2c2_cfg_t usbtoi2c2_cfg;  /**< Click config object. */

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
    usbtoi2c2_cfg_setup( &usbtoi2c2_cfg );
    USBTOI2C2_MAP_MIKROBUS( usbtoi2c2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == usbtoi2c2_init( &usbtoi2c2, &usbtoi2c2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBTOI2C2_ERROR == usbtoi2c2_default_cfg ( &usbtoi2c2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t rx_data = 0;
    if ( USBTOI2C2_OK == usbtoi2c2_read_data ( &usbtoi2c2, &rx_data, 1 ) )
    {
        if ( USBTOI2C2_OK == usbtoi2c2_write_data ( &usbtoi2c2, &rx_data, 1 ) )
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
