/*!
 * \file 
 * \brief AnyNet3g Click example
 * 
 * # Description
 * This example reads and processes data from AnyNet 3G clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - anynet3g_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "anynet3g.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static anynet3g_t anynet3g;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void anynet3g_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = anynet3g_generic_read( &anynet3g, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            log_printf( &logger, "%s", uart_rx_buffer );

            // Storages data in parser buffer
            rsp_cnt += rsp_size;
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
    anynet3g_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 56000;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    anynet3g_cfg_setup( &cfg );
    ANYNET3G_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    anynet3g_init( &anynet3g, &cfg );

    Delay_ms( 1000 );
    anynet3g_process(  );
    
    anynet3g_send_command( &anynet3g, ANYNET3G_SINGLE_CMD_AT );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_AWSVER );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_QCCID );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_AWSSTATE );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_AWSPUBOPEN );
    anynet3g_process(  );

    anynet3g_send_command( &anynet3g, AT_PUBLISH_SET );
    anynet3g_process(  );

    Delay_ms( 2000 );
}

void application_task ( void )
{
    anynet3g_process(  );
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
