/*!
 * \file 
 * \brief MBusMaster Click example
 * 
 * # Description
 * This example reads and processes data from M-Bus Master clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - mbusmaster_process ( ) - The general process of collecting the received data.
 * 
 * @note 
 * - M-Bus master communication works at 36v.
 * - This Click acts only as 'master', therefore it must be connected to appropriate 'slave'.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mbusmaster.h"

#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE - M-Bus Master Click board\r\n"

// #define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITTER

// ------------------------------------------------------------------ VARIABLES

static mbusmaster_t mbusmaster;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void mbusmaster_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = mbusmaster_generic_read( &mbusmaster, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
    mbusmaster_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    mbusmaster_cfg_setup( &cfg );
    MBUSMASTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusmaster_init( &mbusmaster, &cfg );
    Delay_ms ( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    mbusmaster_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITTER
    mbusmaster_generic_write( &mbusmaster, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
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
