/*!
 * \file 
 * \brief Rs4855 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 5 Clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the selected mode.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - rs4855_process ( ) - The general process of collecting the received data.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs4855.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

static rs4855_t rs4855;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs4855_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = rs4855_generic_read( &rs4855, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size >= strlen( TEXT_TO_SEND ) )
    {  
        log_printf( &logger, "Received data: " );
        
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ check_buf_cnt ] );
        }
    }
    Delay_ms ( 100 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4855_cfg_t cfg;

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

    rs4855_cfg_setup( &cfg );
    RS4855_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4855_init( &rs4855, &cfg );

    Delay_ms ( 100 );

#ifdef DEMO_APP_RECEIVER
    rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_LOW );
    rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_LOW );
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    rs4855_set_re_state( &rs4855, RS4855_PIN_STATE_HIGH );
    rs4855_set_de_state( &rs4855, RS4855_PIN_STATE_HIGH );
    log_info( &logger, "---- Transmitter mode ----" );
#endif    
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4855_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs4855_generic_write( &rs4855, TEXT_TO_SEND, 8 );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif    
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
