/*!
 * \file 
 * \brief Rs485Isolator2 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 Isolator 2 clicks.
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
 * - rs485isolator2_process ( ) - The general process of collecting the received data.
 * 
 * @note
 * Wire connection guide : Driver(Master)       Slave
 *                                     Y   ->   A
 *                                     Z   ->   B
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs485isolator2.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

static rs485isolator2_t rs485isolator2;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs485isolator2_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = rs485isolator2_generic_read( &rs485isolator2, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
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
    rs485isolator2_cfg_t cfg;

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

    rs485isolator2_cfg_setup( &cfg );
    RS485ISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs485isolator2_init( &rs485isolator2, &cfg );
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_RECEIVER
    rs485isolator2_set_re_pin( &rs485isolator2, RS485ISOLATOR2_ENABLE_RE );
    rs485isolator2_set_de_pin( &rs485isolator2, RS485ISOLATOR2_DISABLE_DE );
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator2_set_de_pin( &rs485isolator2, RS485ISOLATOR2_ENABLE_DE );
    rs485isolator2_set_re_pin( &rs485isolator2, RS485ISOLATOR2_DISABLE_RE );
    log_info( &logger, "---- Transmitter mode ----" );
#endif    
    Delay_ms ( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs485isolator2_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs485isolator2_generic_write( &rs485isolator2, TEXT_TO_SEND, 8 );
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
