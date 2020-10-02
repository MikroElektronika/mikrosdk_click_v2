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
 * - uartmux_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
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
#define PROCESS_RSP_BUFFER_SIZE 1000

#define TEXT_TO_SEND  "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static uartmux_t uartmux;
static log_t logger;

static uartmux_channel_t channel;

static char current_rsp_buf[ PROCESS_RSP_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void uartmux_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    channel.state_a = UARTMUX_STATE_A_CHANNEL_1;
    channel.state_b = UARTMUX_STATE_B_CHANNEL_1;

    // Clear rsp buffer
    memset( current_rsp_buf, 0 , PROCESS_RSP_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = uartmux_generic_read( &uartmux, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE, &channel );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            
            // Storages data in rsp buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_RSP_BUFFER_SIZE )
            {
                strncat( current_rsp_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uartmux_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
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
    uartmux_process( );

    channel.state_a = UARTMUX_STATE_A_CHANNEL_1;
    channel.state_b = UARTMUX_STATE_B_CHANNEL_1;

    if ( send_data_cnt == 2 )
    {
        uartmux_send_command( &uartmux, TEXT_TO_SEND, &channel );
        uartmux_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
#endif
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
