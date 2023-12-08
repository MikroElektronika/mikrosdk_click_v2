/*!
 * \file 
 * \brief Lin Click example
 * 
 * # Description
 * This example reads and processes data from LIN clicks.
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
 * - lin_process ( ) - The general process of collecting the received data.
 * 
 * @note
 * Make sure to set the onboard Master/Slave jumpers properly and to connect and power two click 
 * boards according to LIN Specification 2.2A.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lin.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE - LIN click board\r\n"

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

// ------------------------------------------------------------------ VARIABLES

static lin_t lin;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lin_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    
    rsp_size = lin_generic_read( &lin, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
    
    if ( rsp_size > 0 )
    {  
        for ( uint8_t cnt = 0; cnt < rsp_size; cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ cnt ] );
            if ( uart_rx_buffer[ cnt ] == '\n' )
            {
                log_printf( &logger, "---------------------------\r\n" );
            }
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lin_cfg_t cfg;

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

    lin_cfg_setup( &cfg );
    LIN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lin_init( &lin, &cfg );
    Delay_ms( 100 );
    
    lin_set_enable ( &lin, 1 );
    lin_set_wake_up ( &lin, 0 );
    Delay_ms( 100 );
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
    lin_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    lin_generic_write( &lin, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#endif   
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
