/*!
 * \file 
 * \brief 4gLte Click example
 * 
 * # Description
 * This example reads and processes data from 4G LTE clicks.
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
 * - c4glte_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c4glte.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_CURRENT_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static c4glte_t c4glte;
static log_t logger;

#define C4GLTE_AT      "AT" 
#define C4GLTE_ATE1    "ATE1" 
#define C4GLTE_AT_IFC  "AT+IFC=2,2" 
#define C4GLTE_AT_CMGF "AT+CMGF=1" 
#define C4GLTE_ATH     "ATH"

static char current_rx_buf[ PROCESS_CURRENT_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void c4glte_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear current buffer
    memset( current_rx_buf, 0 , PROCESS_CURRENT_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = c4glte_generic_read( &c4glte, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            // Storages data in current buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_CURRENT_BUFFER_SIZE )
            {
                strncat( current_rx_buf, uart_rx_buffer, rsp_size );
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
    log_printf( &logger, "%s", current_rx_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4glte_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c4glte_cfg_setup( &cfg );
    C4GLTE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4glte_init( &c4glte, &cfg );

    c4glte_module_power( &c4glte, C4GLTE_MODULE_POWER_ON );

    // MODULE INIT
    
    c4glte_send_command( &c4glte, C4GLTE_AT );
    c4glte_process( );
    c4glte_send_command( &c4glte, C4GLTE_ATE1 );
    c4glte_process( );
    c4glte_send_command( &c4glte, C4GLTE_AT_IFC );
    c4glte_process( );
    c4glte_send_command( &c4glte, C4GLTE_AT_CMGF );
    c4glte_process( ); 
}

void application_task ( void )
{
    c4glte_process( ); 

    if ( send_data_cnt == 5 )
    {
        c4glte_send_command ( &c4glte, C4GLTE_ATH );
        c4glte_process( ); 
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
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
