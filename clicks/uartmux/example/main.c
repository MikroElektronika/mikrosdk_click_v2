/*!
 * \file 
 * \brief UartMux Click example
 * 
 * # Description
 * This example reads and processes data from UART Mux clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - uartmux_process ( ) - The general process of collecting response
 *                                   from module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uartmux.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND  "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITER

static uartmux_t uartmux;
static log_t logger;

static uartmux_channel_t channel;

static int32_t rsp_size;
static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void uartmux_process ( void )
{
    rsp_size = uartmux_generic_read( &uartmux, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE, &channel );

    if ( rsp_size > 0 )
    {  
        for ( int32_t cnt = 0; cnt < rsp_size; cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ cnt ] );
        }
    }  
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uartmux_cfg_t cfg;

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

    uartmux_cfg_setup( &cfg );
    UARTMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uartmux_init( &uartmux, &cfg );

    uartmux_set_inhibit_communication( &uartmux, UARTMUX_PIN_STATE_LOW );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    uartmux_process( );
#endif

#ifdef DEMO_APP_TRANSMITER
    channel.state_a = UARTMUX_STATE_A_CHANNEL_1;
    channel.state_b = UARTMUX_STATE_B_CHANNEL_1;

    uartmux_generic_write( &uartmux, TEXT_TO_SEND, strlen( TEXT_TO_SEND ), &channel );
    Delay_ms( 2000 );
#endif
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
