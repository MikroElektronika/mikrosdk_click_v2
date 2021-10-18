/*!
 * \file 
 * \brief Bluetooth Click example
 * 
 * # Description
 * This example reads and processes data from Bluetooth clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - bluetooth_process ( ) - Logs all received messages on UART, and sends the certain message back to the connected device.
 * 
 * *note:* 
 * Before starting to use this click, it must be paired with other device.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "bluetooth.h"
#include "string.h"

#define PROCESS_COUNTER 20
#define PROCESS_RX_BUFFER_SIZE 100
#define PROCESS_PARSER_BUFFER_SIZE 100

// ------------------------------------------------------------------ VARIABLES

static bluetooth_t bluetooth;
static log_t logger;

uint8_t DEVICE_NAME_DATA[ 20 ] = { 'B', 'l', 'u', 'e', 't', 'o', 'o', 't', 'h', 'C', 'l', 'i', 'c', 'k' };
uint8_t EXTENDED_STRING_DATA[ 10 ] = { 'S', 'l', 'a', 'v', 'e' };
uint8_t PIN_CODE_DATA[ 10 ] = { '1', '2', '3', '4' };
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static int8_t bluetooth_process ( char * response )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear current buffer
    memset( current_parser_buf, 0, PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = bluetooth_generic_read( &bluetooth, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            // Storages data in current buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
            
            log_printf( &logger, "%s", current_parser_buf );
            
            if ( strstr( current_parser_buf, "ERR" ) ) {
               Delay_100ms( );
               return -1;
            }
            
            if ( strstr( current_parser_buf, response ) ) {
               Delay_100ms( );
               return 1;
            }
               
            if ( strstr( current_parser_buf, "Hello" ) ) {
                bluetooth_generic_write( &bluetooth, "MikroE\r\n", 8 );
                Delay_100ms( );
            }
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
    
    return 0;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    bluetooth_cfg_t cfg;

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

    bluetooth_cfg_setup( &cfg );
    BLUETOOTH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bluetooth_init( &bluetooth, &cfg );

    Delay_ms( 500 );
   
    log_printf( &logger, "Configuring the module...\n" );
    
    do
    {    
        log_printf( &logger, " --- Command mode --- \r\n" );
        bluetooth_enter_command_mode( &bluetooth );
    }
    while( bluetooth_process( "CMD" ) != 1 );
    
    do
    {
        log_printf( &logger, " --- Device name --- \r\n" );
        bluetooth_set_device_name( &bluetooth, &DEVICE_NAME_DATA[ 0 ] );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Status string --- \r\n" );
        bluetooth_set_extended_status_string( &bluetooth, &EXTENDED_STRING_DATA[ 0 ] );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Operating mode --- \r\n" );
        bluetooth_set_operating_mode( &bluetooth, 0 );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Authentication --- \r\n" );
        bluetooth_set_authentication( &bluetooth, 1 );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Pin code --- \r\n" );
        bluetooth_set_security_pin_code( &bluetooth, &PIN_CODE_DATA[ 0 ] );
    }
    while( bluetooth_process( "AOK" ) != 1 );

    do
    {
        log_printf( &logger, " --- Exit command mode --- \r\n" );
        bluetooth_exit_command_mode( &bluetooth );
    }
    while( bluetooth_process( "END" ) != 1 );
    
    log_printf( &logger, "The module has been configured.\n" );
}

void application_task ( void )
{
    bluetooth_process( "AOK" );
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
