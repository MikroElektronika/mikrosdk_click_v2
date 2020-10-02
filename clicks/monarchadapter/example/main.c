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
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - monarchadapter_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "monarchadapter.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define MONARCH_CMD_AT   "AT"
#define MONARCH_CMD_ATI  "ATI"
#define MONARCH_CMD_ATI1 "ATI1"

// ------------------------------------------------------------------ VARIABLES

static monarchadapter_t monarchadapter;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void monarchadapter_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;

    rsp_size = monarchadapter_generic_read( &monarchadapter, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
        log_printf( &logger, "%s \r\n", uart_rx_buffer );

        // Clear RX buffer
        memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
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

    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_AT );
    Delay_ms( 3000 );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI );
    Delay_ms( 3000 );
    monarchadapter_process( );
}

void application_task ( void )
{
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI1 );
    Delay_ms( 5000 );
    monarchadapter_process( );
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
