/*!
 * \file 
 * \brief Rs4852 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 2 Clicks.
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
 * - rs4852_process ( ) - The general process of collecting the received data.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs4852.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE - RS485 2 Click board\r\n"

// #define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITTER

// ------------------------------------------------------------------ VARIABLES

static rs4852_t rs4852;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs4852_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = rs4852_generic_read( &rs4852, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        for ( uint8_t cnt = 0; cnt < rsp_size; cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ cnt ] );
            if ( uart_rx_buffer[ cnt ] == '\n' )
            {
                log_printf( &logger, "--------------------------------\r\n" );
            }
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4852_cfg_t cfg;

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

    rs4852_cfg_setup( &cfg );
    RS4852_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4852_init( &rs4852, &cfg );
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_RECEIVER
    rs4852_set_re_pin( &rs4852, RS4852_ENABLE_RE );
    rs4852_set_de_pin( &rs4852, RS4852_DISABLE_DE );
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    rs4852_set_de_pin( &rs4852, RS4852_ENABLE_DE );
    rs4852_set_re_pin( &rs4852, RS4852_DISABLE_RE );
    log_info( &logger, "---- Transmitter mode ----" );
#endif    
    Delay_ms ( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4852_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    rs4852_generic_write( &rs4852, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
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
