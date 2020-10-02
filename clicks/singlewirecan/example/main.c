/*!
 * \file 
 * \brief SingleWireCan Click example
 * 
 * # Description
 * This example demonstrate sending a data by using one Single Wire CAN click
 * and print recived data using the other Single Wire CAN click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - UART,
 * performs an operating mode and sets CS and RST pins as output.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the One Wire CAN click board.
 * This application task adjusted on Transmiter Mode, writes message data via UART every 3 seconds.
 * And another clicks task, adjusted on Reciver Mode, read and represent result on the Usart Terminal.
 * 
 * ## Additional Function
 * - singlewirecan_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "singlewirecan.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static singlewirecan_t singlewirecan;
static log_t logger;

static char demo_message_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void singlewirecan_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    while( process_cnt != 0 )
    {
        rsp_size = singlewirecan_generic_read( &singlewirecan, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            log_printf( &logger, " TX Data: %s", uart_rx_buffer );
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    singlewirecan_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    singlewirecan_cfg_setup( &cfg );
    SINGLEWIRECAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlewirecan_init( &singlewirecan, &cfg );

    singlewirecan_default_cfg( &singlewirecan );
    log_printf( &logger, "  Set Normal Op. Mode \r\n" );
}

void application_task ( void )
{
    #ifdef DEMO_APP_TRANSMITER
        singlewirecan_generic_write( &singlewirecan, &demo_message_data[ 0 ], strlen( demo_message_data ) );
        log_printf( &logger, "Sending message\r\n" );
        log_printf( &logger, "\r\n" );
    #endif

    #ifdef DEMO_APP_RECEIVER    
        singlewirecan_process(  );
        log_printf( &logger, "----------------------\r\n" );
        log_printf( &logger, "\r\n" );
    #endif
    Delay_ms( 3000 );
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
