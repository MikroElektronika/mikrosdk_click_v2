/*!
 * \file 
 * \brief UsbUart3 Click example
 * 
 * # Description
 * This example reads and processes data from USB UART 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads data and echos it back to device and logs it to board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "usbuart3.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES


static usbuart3_t usbuart3;
static log_t logger;

static int32_t rsp_size;
static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    usbuart3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    usbuart3_cfg_setup( &cfg );
    USBUART3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    usbuart3_init( &usbuart3, &cfg );
    
    usbuart3_reset( &usbuart3 );
}

void application_task ( void )
{
    rsp_size = usbuart3_generic_read( &usbuart3, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        usbuart3_generic_write( &usbuart3, uart_rx_buffer, rsp_size );
        log_printf( &logger, "%s", uart_rx_buffer );
        memset( uart_rx_buffer, 0, rsp_size );
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
