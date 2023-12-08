/*!
 * @file main.c
 * @brief RS485 5V Click Example.
 *
 * # Description
 * This example reads and processes data from RS485 5V clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wake-up module.
 *
 * ## Application Task
 * Reads the received data and parses it.
 *
 * ## Additional Function
 * - static void rs4855v_clear_current_rsp_buf ( void ) - The general process of clearing buffer.
 * - static void rs4855v_process ( void ) - The general process of collecting the received data.
 * @author Stefan Ilic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs4855v.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 100
#define PROCESS_PARSER_BUFFER_SIZE 100

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITTER

static rs4855v_t rs4855v;
static log_t logger;

static char current_rsp_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

unsigned char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void rs4855v_clear_current_rsp_buf ( void ) {
    memset( current_rsp_buf, 0, PROCESS_PARSER_BUFFER_SIZE );
}

static void rs4855v_process ( void ) {
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;

    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    // Clear parser buffer
    memset( current_rsp_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 

    while( process_cnt != 0 ) {
        rsp_size = rs4855v_generic_read( &rs4855v, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 ) {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ ) {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE ) {
                strncat( current_rsp_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    log_cfg_t log_cfg;
    rs4855v_cfg_t cfg;

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

    //  Click initialization.

    rs4855v_cfg_setup( &cfg );
    RS4855V_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs4855v_init( &rs4855v, &cfg );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Send data:    \r\n" );
    log_printf( &logger, "      MikroE      \r\n" );
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Transmit data   \r\n" );
    Delay_ms( 1000 );

#endif
    
#ifdef DEMO_APP_RECEIVER 
    log_printf( &logger, "------------------\r\n" );

    log_printf( &logger, "   Receive data  \r\n" );
    Delay_ms( 2000 );
#endif
        
    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void ) {  
#ifdef DEMO_APP_RECEIVER 
    
    rs4855v_process( );
    if ( current_rsp_buf > 0 ) {
        log_printf( &logger, "%s", current_rsp_buf );
        rs4855v_clear_current_rsp_buf( );
    }
    
#endif 

#ifdef DEMO_APP_TRANSMITTER
      
    rs4855v_send_command( &rs4855v, &demo_message[ 0 ] );
    log_printf( &logger, "\t%s",  &demo_message[ 0 ] );
    Delay_ms( 2000 );
    log_printf( &logger, "------------------\r\n" ); 
    
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
