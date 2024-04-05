/*!
 * \file 
 * \brief Rs4856 Click example
 * 
 * # Description
 * This example reads and processes data from RS485 6 clicks.
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
 * - rs4856_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs4856.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

#define TEXT_TO_SEND  "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITER

static rs4856_t rs4856;
static log_t logger;

static char current_rsp_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0;
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs4856_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_rsp_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = rs4856_generic_read( &rs4856, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
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
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_rsp_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms ( 100 );
        }
    }
    
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rs4856_cfg_t cfg;

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

    rs4856_cfg_setup( &cfg );
    RS4856_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4856_init( &rs4856, &cfg );

#ifdef DEMO_APP_RECEIVER
    rs4856_re_pin_set( &rs4856, RS4856_PIN_STATE_LOW );
    rs4856_de_pin_set( &rs4856, RS4856_PIN_STATE_LOW );
#endif

#ifdef DEMO_APP_TRANSMITER
    rs4856_re_pin_set( &rs4856, RS4856_PIN_STATE_HIGH );
    rs4856_de_pin_set( &rs4856, RS4856_PIN_STATE_HIGH );
#endif  
    log_info( &logger, " Start sending info" );  
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    rs4856_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    rs4856_process( );
    
    if ( send_data_cnt == 5 )
    {
        rs4856_send_command( &rs4856, TEXT_TO_SEND );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
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
