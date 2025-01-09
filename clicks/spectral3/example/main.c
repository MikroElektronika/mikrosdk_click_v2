/*!
 * \file 
 * \brief Spectral3 Click example
 * 
 * # Description
 * This example reads and processes data from Spectral 3 Clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the sensor.
 * 
 * ## Application Task  
 * Reads the values of all 6 channels and parses it to the USB UART each second.
 * 
 * ## Additional Function
 * - spectral3_process ( ) - The general process of collecting the sensor responses.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spectral3.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 200
#define PROCESS_PARSER_BUFFER_SIZE 400

#define SPECTRAL3_CMD_DATA      "ATDATA"
#define SPECTRAL3_CMD_AT        "AT" 
#define SPECTRAL3_CMD_GAIN      "ATGAIN=2"
#define SPECTRAL3_CMD_MODE      "ATTCSMD=2"

// ------------------------------------------------------------------ VARIABLES

static spectral3_t spectral3;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void spectral3_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = spectral3_generic_read( &spectral3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

static void parser_application ( )
{  
    uint16_t read_data[ 6 ];

    spectral3_send_command( &spectral3, SPECTRAL3_CMD_DATA );
    spectral3_process( );

    spectral3_get_data( current_parser_buf, read_data );
 
    log_printf( &logger, "-- R value: %d \r\n", read_data[ 0 ] );   
    log_printf( &logger, "-- S value: %d \r\n", read_data[ 1 ] );
    log_printf( &logger, "-- T value: %d \r\n", read_data[ 2 ] );
    log_printf( &logger, "-- U value: %d \r\n", read_data[ 3 ] );
    log_printf( &logger, "-- V value: %d \r\n", read_data[ 4 ] );
    log_printf( &logger, "-- W value: %d \r\n", read_data[ 5 ] );
    log_printf( &logger, "-----------------\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral3_cfg_t cfg;

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

    spectral3_cfg_setup( &cfg );
    SPECTRAL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral3_init( &spectral3, &cfg );

    spectral3_module_reset( &spectral3 );
    Delay_ms ( 500 );
    
    log_printf( &logger, "Configuring the sensor...\r\n" );
    spectral3_send_command( &spectral3, SPECTRAL3_CMD_AT );
    spectral3_process( );
    spectral3_send_command( &spectral3, SPECTRAL3_CMD_GAIN );
    spectral3_process( );
    spectral3_send_command( &spectral3, SPECTRAL3_CMD_MODE );
    spectral3_process( );
    log_printf( &logger, "The sensor has been configured!\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    parser_application( );
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
