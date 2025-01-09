/*!
 * \file 
 * \brief Rs4854 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 4 Clicks.
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
 * - rs4854_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs4854.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

static uint8_t transmit_msg[] = "MikroE\r\n";

// ------------------------------------------------------------------ VARIABLES

// #define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static rs4854_t rs4854;
static log_t logger;

static uint8_t send_data_cnt = 8; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs4854_process ( void )
{
    int32_t rsp_size;
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    
    rsp_size = rs4854_generic_read( &rs4854, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
    
    if ( rsp_size > 0 )
    {  
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            log_printf( &logger, "%c", uart_rx_buffer[ check_buf_cnt ] );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4854_cfg_t cfg;

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

    rs4854_cfg_setup( &cfg );
    RS4854_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4854_init( &rs4854, &cfg );
    
#ifdef DEMO_APP_RECEIVER
    rs4854_re_pin_set( &rs4854, RS4854_PIN_STATE_LOW );
    rs4854_de_pin_set( &rs4854, RS4854_PIN_STATE_LOW );
#endif

#ifdef DEMO_APP_TRANSMITER
    rs4854_re_pin_set( &rs4854, RS4854_PIN_STATE_HIGH );
    rs4854_de_pin_set( &rs4854, RS4854_PIN_STATE_HIGH );
#endif  
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4854_process( );
#endif    

#ifdef DEMO_APP_TRANSMITER

    rs4854_generic_write( &rs4854, &transmit_msg[ 0 ], 8 );
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
