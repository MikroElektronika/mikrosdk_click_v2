/*!
 * \file 
 * \brief iqrf2 Click example
 * 
 * # Description
 * This example reads and processes data from iqRF 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and makes an initial log.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - iqrf2_process ( ) - The general process of collecting the received data.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "iqrf2.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE - iqRF 2 click board\r\n"

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

// ------------------------------------------------------------------ VARIABLES

static iqrf2_t iqrf2;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void iqrf2_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    
    rsp_size = iqrf2_generic_read( &iqrf2, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
    
    if ( rsp_size > 0 )
    {  
        for ( uint8_t cnt = 0; cnt < rsp_size; cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ cnt ] );
            if ( uart_rx_buffer[ cnt ] == '\n' )
            {
                log_printf( &logger, "-----------------------------\r\n" );
            }
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    iqrf2_cfg_t cfg;

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

    iqrf2_cfg_setup( &cfg );
    IQRF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    iqrf2_init( &iqrf2, &cfg );
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- Receiver mode ----" );
#endif    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#endif   
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    iqrf2_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    iqrf2_generic_write( &iqrf2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
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
