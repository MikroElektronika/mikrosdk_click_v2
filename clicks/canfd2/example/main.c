/*!
 * \file 
 * \brief CanFd2 Click example
 * 
 * # Description
 * This example reads and processes data from CAN FD 2 clicks.
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
 * - canfd2_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "canfd2.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static canfd2_t canfd2;
static log_t logger;

static uint8_t demo_message_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void canfd2_process ( void )
{
    int16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = canfd2_generic_read( &canfd2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
    canfd2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    canfd2_cfg_setup( &cfg );
    CANFD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd2_init( &canfd2, &cfg );

    Delay_ms( 300 );
    
    log_printf( &logger,  "-------------------\r\n" );
    log_printf( &logger,  "   CAN FD 2 click  \r\n" );
    log_printf( &logger,  "-------------------\r\n" );
    log_printf( &logger,  "--- Initialized ---\r\n" );
    log_printf( &logger,  "-------------------\r\n" );

    
    #ifdef DEMO_APP_RECEIVER

        canfd2_set_mode( &canfd2, CANFD2_OP_MODE_RECEIVE_ONLY );
        log_printf( &logger,  "   RECEIVER MODE   \r\n" );
        log_printf( &logger,  "-------------------\r\n" );

    #endif
    #ifdef DEMO_APP_TRANSMITER

        canfd2_set_mode( &canfd2, CANFD2_OP_MODE_NORMAL );
        log_printf( &logger,  "  TRANSMITER MODE  \r\n" );
        log_printf( &logger,  "-------------------\r\n" );

    #endif
    
    Delay_ms( 100 );
}

void application_task ( void )
{
    #ifdef DEMO_APP_RECEIVER

        // RECEIVER - UART polling
        canfd2_process( );

    #endif
    #ifdef DEMO_APP_TRANSMITER

        // TRANSMITER - TX each 2 sec
        canfd2_generic_write( &canfd2, &demo_message_data[ 0 ], 8 );
        Delay_ms( 3000 );

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
