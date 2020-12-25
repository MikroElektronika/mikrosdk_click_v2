/*!
 * \file 
 * \brief Gsm Click example
 * 
 * # Description
 * This example reads and processes data from GSM clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, power on module and sends few command for the default module configuration.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - gsm_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gsm.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static gsm_t gsm;
static log_t logger;

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void gsm_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = gsm_generic_read( &gsm, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
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
    gsm_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gsm_cfg_setup( &cfg );
    GSM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsm_init( &gsm, &cfg );

    gsm_process(  );

    gsm_send_command( &gsm, GSM_SINGLE_CMD_AT );
    gsm_process(  );
    
    gsm_send_command( &gsm, GSM_SINGLE_CMD_AT );
    gsm_process(  );

    gsm_send_command( &gsm, GSM_SINGLE_CMD_AT );
    gsm_process(  );

    gsm_send_command( &gsm, GSM_SINGLE_CMD_ATE0 );
    gsm_process(  );

    gsm_send_command( &gsm, "AT+IFC=2,2" );
    gsm_process(  );

    gsm_send_command( &gsm, "AT+CMGF=1" );

    Delay_ms( 2000 );
}

void application_task ( void )
{
    gsm_process( );
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
