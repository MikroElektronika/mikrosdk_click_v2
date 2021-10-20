/*!
 * \file 
 * \brief 3gSara Click example
 * 
 * # Description
 * This example reads and processes data from 3G SARA clicks.
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
 * - c3gsara_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3gsara.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_CURRENT_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static c3gsara_t c3gsara;
static log_t logger;

#define C3GSARA_AT_COMMAND      "AT"
#define C3GSARA_ATE0_COMMAND    "ATE0"
#define C3GSARA_AT_IFC_COMMAND  "AT+IFC=2,2"
#define C3GSARA_AT_CMGF_COMMAND "AT+CMGF=1"
#define C3GSARA_ATH_COMMAND     "ATH"

static char current_rx_buf[ PROCESS_CURRENT_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void c3gsara_process ( void )
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
        rsp_size = c3gsara_generic_read( &c3gsara, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
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
    c3gsara_cfg_t cfg;

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

    c3gsara_cfg_setup( &cfg );
    C3GSARA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3gsara_init( &c3gsara, &cfg );

    c3gsara_module_power( &c3gsara, true );

    c3gsara_send_command( &c3gsara, C3GSARA_AT_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_ATE0_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_IFC_COMMAND ); 
    c3gsara_process( );
    c3gsara_send_command( &c3gsara, C3GSARA_AT_CMGF_COMMAND ); 
    c3gsara_process( );
}

void application_task ( void )
{
    c3gsara_process( );
    
    if ( send_data_cnt == 5 )
    {
        c3gsara_send_command( &c3gsara, C3GSARA_ATH_COMMAND );
        c3gsara_process( );
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
