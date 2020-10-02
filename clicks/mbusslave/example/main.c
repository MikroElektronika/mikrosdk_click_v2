/*!
 * \file 
 * \brief MBusSlave Click example
 * 
 * # Description
 * This example reads and processes data from M-Bus Slave clicks.
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
 * - mbusslave_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mbusslave.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static mbusslave_t mbusslave;
static log_t logger;

static uint8_t demo_message_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void mbusslave_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;

    rsp_size = mbusslave_generic_read( &mbusslave, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
    mbusslave_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mbusslave_cfg_setup( &cfg );
    MBUSSLAVE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusslave_init( &mbusslave, &cfg );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITER
    mbusslave_generic_write( &mbusslave, demo_message_data, 9 );
    log_printf( &logger, " >> MESSAGE SENT << \r\n" );
    Delay_ms( 2000 );
#endif 

#ifdef DEMO_APP_RECEIVER
    mbusslave_process( );
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
