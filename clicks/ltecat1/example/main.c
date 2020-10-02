/*!
 * \file 
 * \brief LteCat1 Click example
 * 
 * # Description
 * This example reads and processes data from LTE Cat.1 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - ltecat1_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ltecat1.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define LTECAT1_AT          "AT"
#define LTECAT1_ATE         "ATE0"
#define LTECAT1_AT_CMGF     "AT+CMGF=1"
#define LTECAT1_ATI         "ATI"
#define LTECAT1_AT_CREG     "AT+CREG=1"
#define LTECAT1_ATH         "ATH"

// ------------------------------------------------------------------ VARIABLES

static ltecat1_t ltecat1;
static log_t logger;

static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS 

static void ltecat1_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;

    rsp_size = ltecat1_generic_read( &ltecat1, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
        log_printf( &logger, "%s\r\n", uart_rx_buffer );
        
        // Clear RX buffer
        memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    } 
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ltecat1_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ltecat1_cfg_setup( &cfg );
    LTECAT1_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ltecat1_init( &ltecat1, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "  LTE Cat. 1 Click   \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
    
    Delay_ms( 100 );

    ltecat1_module_power( &ltecat1, 1 );

    ltecat1_send_command( &ltecat1, LTECAT1_AT );
    Delay_ms(500);
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT );
    Delay_ms(500);
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT );
    Delay_ms(500);
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_ATE );
    Delay_ms(500);
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT_CREG );
    Delay_ms(500);
    ltecat1_process( );
    Delay_ms( 2000 );

    ltecat1_send_command( &ltecat1, LTECAT1_ATI );
    Delay_ms(500);
    ltecat1_process( );
    Delay_ms( 1000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT_CREG );
    Delay_ms(500);
    ltecat1_process( );
    Delay_ms( 1000 );
}

void application_task ( void )
{   
    ltecat1_process( );
    if ( send_data_cnt == 5 )
    {
       ltecat1_send_command( &ltecat1, LTECAT1_ATH );
       Delay_ms( 500 );
       ltecat1_process( );
       send_data_cnt = 0;
    }
    send_data_cnt++;
    Delay_ms( 1000 );
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
