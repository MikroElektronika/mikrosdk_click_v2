/*!
 * \file 
 * \brief Spectral Click example
 * 
 * # Description
 * This example reads and processes data from Spectral clicks.
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
 * - spectral_process ( ) - The general process of collecting the sensor responses.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spectral.h"
#include "string.h"

#define PROCESS_COUNTER             10
#define PROCESS_RX_BUFFER_SIZE      200
#define PROCESS_PARSER_BUFFER_SIZE  400

#define SPECTRAL_CMD_DATA           "ATDATA"
#define SPECTRAL_CMD_AT             "AT" 
#define SPECTRAL_CMD_GAIN           "ATGAIN=2"
#define SPECTRAL_CMD_MODE           "ATTCSMD=2"

// ------------------------------------------------------------------ VARIABLES

static spectral_t spectral;
static log_t logger;

static uint8_t current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void spectral_process ( void )
{
    int32_t rsp_size = 0;
    uint16_t rsp_cnt = 0;
    
    uint8_t uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt = 0;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0, PROCESS_PARSER_BUFFER_SIZE ); 
    
    while ( process_cnt )
    {
        rsp_size = spectral_uart_read( &spectral, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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

void parser_application ( )
{
    uint16_t read_data[ 6 ] = { 0 };
    spectral_send_command( &spectral, SPECTRAL_CMD_DATA );
    spectral_process( );
    
    spectral_get_data( current_parser_buf, read_data );
    
    log_printf( &logger, "-- X value: %d\r\n", read_data[ 0 ] );    
    log_printf( &logger, "-- Y value: %d\r\n", read_data[ 1 ] );  
    log_printf( &logger, "-- Z value: %d\r\n", read_data[ 2 ] ); 
    log_printf( &logger, "-- NIR value: %d\r\n", read_data[ 3 ] );
    log_printf( &logger, "-- D value: %d\r\n", read_data[ 4 ] );
    log_printf( &logger, "-- C value: %d\r\n", read_data[ 5 ] );
    log_printf( &logger, "-----------------\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral_cfg_t cfg;

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

    // Click initialization.
    spectral_cfg_setup( &cfg );
    SPECTRAL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral_init( &spectral, &cfg );

    spectral_module_reset( &spectral );
    Delay_ms( 500 );

    log_printf( &logger, "Configuring the sensor...\r\n" );
    spectral_send_command( &spectral, SPECTRAL_CMD_AT );
    spectral_process( );
    spectral_send_command( &spectral, SPECTRAL_CMD_GAIN );
    spectral_process( );
    spectral_send_command( &spectral, SPECTRAL_CMD_MODE );
    spectral_process( );
    log_printf( &logger, "The sensor has been configured!\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    parser_application( );  
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
