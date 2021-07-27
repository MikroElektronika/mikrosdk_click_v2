/*!
 * \file 
 * \brief SingleWireCan Click example
 * 
 * # Description
 * This example demonstrate the use of Single Wire CAN click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click for the normal operation mode.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - singlewirecan_process ( ) - The general process of collecting the received data.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "singlewirecan.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

static singlewirecan_t singlewirecan;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void singlewirecan_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = singlewirecan_generic_read( &singlewirecan, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size >= strlen( TEXT_TO_SEND ) )
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
    singlewirecan_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    singlewirecan_cfg_setup( &cfg );
    SINGLEWIRECAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    singlewirecan_init( &singlewirecan, &cfg );
    Delay_ms( 100 );

    singlewirecan_set_operating_mode( &singlewirecan, SINGLEWIRECAN_OPERATING_MODE_NORMAL );
    log_info( &logger, "---- Normal Operation Mode ----" );
    Delay_ms( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    singlewirecan_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    singlewirecan_generic_write( &singlewirecan, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
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
