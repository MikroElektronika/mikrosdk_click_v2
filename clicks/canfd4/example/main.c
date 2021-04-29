/*!
 * \file 
 * \brief CanFd4 Click example
 * 
 * # Description
 * This example reads and processes data from CAN FD 4 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the click board.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - canfd4_process ( ) - The general process of collecting the received data.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "canfd4.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

static canfd4_t canfd4;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void canfd4_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = canfd4_generic_read( &canfd4, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 6 )
    {  
        log_printf( &logger, "Received data: " );
        
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ check_buf_cnt ] );
        }
    }
    Delay_ms( 100 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    canfd4_cfg_setup( &cfg );
    CANFD4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd4_init( &canfd4, &cfg );

    canfd4_set_dev_mode ( &canfd4, CANFD4_NORMAL_MODE );
    Delay_ms( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    canfd4_process( );
#endif
#ifdef DEMO_APP_TRANSMITTER
    canfd4_generic_write( &canfd4, TEXT_TO_SEND, 8 );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms( 2000 );
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
