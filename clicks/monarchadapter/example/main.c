/*!
 * \file 
 * \brief MonarchAdapter Click example
 * 
 * # Description
 * This example reads and processes data from Monarch Adapter clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and checks the module firmware revision.
 * 
 * ## Application Task  
 * Checks EPS Network Registration Status (+CEREG) every 3 seconds.
 * 
 * ## Additional Function
 * - monarchadapter_process ( ) - The general process of collecting data the module sends.
 * 
 * @note
 * Monarch GO and Monarch GO-GPS are certified for use on the Verizon network (LTE band 13) 
 * with roadmap for global band support. Monarch module is not delivered as part of 
 * the Click board package. For more information about module features please read 
 * Monarch GO module specification.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "monarchadapter.h"
#include "string.h"

#define PROCESS_COUNTER 50
#define PROCESS_RX_BUFFER_SIZE 600
#define PROCESS_PARSER_BUFFER_SIZE 600

#define MONARCH_CMD_AT    "AT"
#define MONARCH_CMD_ATE1  "ATE1"
#define MONARCH_CMD_ATI   "ATI"
#define MONARCH_CMD_ATI1  "ATI1"
#define MONARCH_CMD_CEREG "AT+CEREG?"

// ------------------------------------------------------------------ VARIABLES

static monarchadapter_t monarchadapter;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void monarchadapter_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;   
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = monarchadapter_generic_read( &monarchadapter, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            process_cnt = 3;
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
    
    if ( rsp_cnt > 0 )
    {
        log_printf( &logger, "%s", current_parser_buf );
        log_printf( &logger, "-----------------------------------\r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    monarchadapter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    monarchadapter_cfg_setup( &cfg );
    MONARCHADAPTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    monarchadapter_init( &monarchadapter, &cfg );

    monarchadapter_power_on( &monarchadapter );
    
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_AT );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATE1 );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI1 );
    monarchadapter_process( );
}

void application_task ( void )
{
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_CEREG );
    monarchadapter_process( );
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
