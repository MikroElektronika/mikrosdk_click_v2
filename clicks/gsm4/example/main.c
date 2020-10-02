/*!
 * \file 
 * \brief Gsm4 Click example
 * 
 * # Description
 * This example reads and processes data from GSM 4 clicks.
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
 * - gsm4_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * *note:* 
 *  - Echo must be turned off for succefull parsing. ( ATE0 )
 *  - UART polling works much better with HFC enabled.
 *  - In case of usage of other MCUs Timer initialization must be adjusted according to your MCU.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gsm4.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static gsm4_t gsm4;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void gsm4_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = gsm4_generic_read( &gsm4, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
    gsm4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gsm4_cfg_setup( &cfg );
    GSM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsm4_init( &gsm4, &cfg );

    gsm4_module_power( &gsm4 );

    gsm4_process(  );
    
    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_AT );
    gsm4_process(  );

    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_AT );
    gsm4_process(  );

    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_AT );
    gsm4_process(  );

    gsm4_send_command( &gsm4, GSM4_SINGLE_CMD_ATE0 );
    gsm4_process(  );

    gsm4_send_command( &gsm4, "AT+IFC=2,2" );
    gsm4_process(  );

    gsm4_send_command( &gsm4, "AT+CMGF=1" );
    gsm4_process(  );

    Delay_ms( 2000 );
}

void application_task ( void )
{
    gsm4_process(  );
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
