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
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - usbuart3_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "usbuart3.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

#define MESSAGE_TO_BE_SENT  "--- MikroE ---\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static usbuart3_t usbuart3;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void usbuart3_process ( void )
{
    uint16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    while( process_cnt != 0 )
    {
        rsp_size = usbuart3_generic_read( &usbuart3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            log_printf( &logger, "%s \r\n", uart_rx_buffer );
            
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
    usbuart3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    usbuart3_cfg_setup( &cfg );
    USBUART3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    usbuart3_init( &usbuart3, &cfg );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    usbuart3_process( );
#endif

#ifdef DEMO_APP_TRANSMITER
    usbuart3_send_command( &usbuart3, MESSAGE_TO_BE_SENT );
    usbuart3_process( );
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
