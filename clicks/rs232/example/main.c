/*!
 * \file 
 * \brief Rs232 Click example
 * 
 * # Description
 * This example reads and processes data from RS232 Clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Depending on the selected mode (receiver/transmitter) this function reads/sends an appropriate message.
 * All data is displayed on USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs232.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define RS232_TRANSMITTER
// #define RS232_RECEIVER

// ------------------------------------------------------------------ VARIABLES

static rs232_t rs232;
static log_t logger;

static int32_t rsp_size;
static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
static char message[ ] = "MikroE";

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs232_cfg_t cfg;

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

    rs232_cfg_setup( &cfg );
    RS232_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232_init( &rs232, &cfg );
    
    Delay_ms ( 100 );
#ifdef RS232_RECEIVER
    log_printf( &logger, " ** RS232 Receiver **\r\n" );
#endif
    
#ifdef RS232_TRANSMITTER
    log_printf( &logger, " ** RS232 Transmitter **\r\n" );
#endif
}

void application_task ( void )
{    
#ifdef RS232_RECEIVER
    rsp_size = rs232_generic_read( &rs232, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size == strlen( message ) )
    {  
        log_printf( &logger, "Message received: %s", uart_rx_buffer );
        log_printf( &logger, "\r\n-------------------------\r\n" );
        memset( uart_rx_buffer, 0, rsp_size );
    }  
    Delay_ms ( 100 );
#endif
    
#ifdef RS232_TRANSMITTER
    rs232_generic_write( &rs232, message, strlen( message ) );
    log_printf( &logger, "Message sent: %s", message );
    log_printf( &logger, "\r\n-------------------------\r\n" );
    Delay_ms ( 1000 );
#endif
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
