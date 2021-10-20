/*!
 * \file 
 * \brief BtAudio Click example
 * 
 * # Description
 * This example reads and processes data from BT Audio clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board.
 * 
 * ## Application Task  
 * Checks if there's any command received, then parses it and performs adequate actions.
 * 
 * ## Additional Function
 * - btaudio_process ( ) - Logs all the received messages on UART. Also checks if there's 
 * any command received in data mode, if so, parses it and performs adequate actions.
 * 
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the click board must be paired in order to exchange messages
 * with each other. So make sure to pair your device with the click board and
 * connect to it using the Serial Bluetooth Terminal application, then you will be able 
 * to send commands listed below.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "btaudio.h"
#include "string.h"
#include "generic_pointer.h"

#define RESPONSE_CMD                "CMD"
#define RESPONSE_END                "END"
#define RESPONSE_AOK                "AOK"
#define RESPONSE_ERR                "ERR"
#define RESPONSE_NULL               0

// Commands list
#define COMMAND_VOLUME_UP           "volume up"
#define COMMAND_VOLUME_DOWN         "volume down"
#define COMMAND_NEXT                "next"
#define COMMAND_PREVIOUS            "previous"
#define COMMAND_PLAY                "play"
#define COMMAND_PAUSE               "pause"

#define PROCESS_COUNTER             50
#define PROCESS_RX_BUFFER_SIZE      600
#define PROCESS_PARSER_BUFFER_SIZE  600

// ------------------------------------------------------------------ VARIABLES

static btaudio_t btaudio;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static uint8_t parse_data_command ( char * command )
{
    if ( strstr( command, COMMAND_VOLUME_UP ) )
    {
        btaudio_set_cmd_mode( &btaudio, 0 );
        Delay_ms( 100 );
        btaudio_increase_volume( &btaudio );
        Delay_ms( 100 );
        btaudio_set_cmd_mode( &btaudio, 1 );
    }
    else if ( strstr( command, COMMAND_VOLUME_DOWN ) )
    {
        btaudio_set_cmd_mode( &btaudio, 0 );
        Delay_ms( 100 );
        btaudio_decrease_volume( &btaudio );
        Delay_ms( 100 );
        btaudio_set_cmd_mode( &btaudio, 1 );
    }
    else if ( strstr( command, COMMAND_PLAY ) || 
              strstr( command, COMMAND_PAUSE ) )
    {
        btaudio_set_cmd_mode( &btaudio, 0 );
        Delay_ms( 100 );
        btaudio_pause_play_track( &btaudio );
        Delay_ms( 100 );
        btaudio_set_cmd_mode( &btaudio, 1 );
    }
    else if ( strstr( command, COMMAND_NEXT ) )
    {
        btaudio_set_cmd_mode( &btaudio, 0 );
        Delay_ms( 100 );
        btaudio_next_track( &btaudio );
        Delay_ms( 100 );
        btaudio_set_cmd_mode( &btaudio, 1 );
    }
    else if ( strstr( command, COMMAND_PREVIOUS ) )
    {
        btaudio_set_cmd_mode( &btaudio, 0 );
        Delay_ms( 100 );
        btaudio_previous_track( &btaudio );
        Delay_ms( 100 );
        btaudio_set_cmd_mode( &btaudio, 1 );
    }
    else
    {
        return 0; 
    }
    
    return 1;
}

static void btaudio_process ( char * __generic response )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;   
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0, PROCESS_PARSER_BUFFER_SIZE );
    Delay_100ms( );
    
    while( process_cnt != 0 )
    {
        rsp_size = btaudio_generic_read( &btaudio, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            if ( strstr( current_parser_buf, RESPONSE_ERR ) )
            {
                return;
            }
            
            if ( strstr( current_parser_buf, response )     ||
                 strstr( current_parser_buf, RESPONSE_CMD ) || 
                 strstr( current_parser_buf, RESPONSE_END ) ||
                 parse_data_command( uart_rx_buffer ) )
            {
                process_cnt = 3;
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
    
    if ( rsp_cnt > 0 )
    {
        log_printf( &logger, "%s", current_parser_buf );
        log_printf( &logger, "--------------------\r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    btaudio_cfg_t cfg;

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

    btaudio_cfg_setup( &cfg );
    BTAUDIO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    btaudio_init( &btaudio, &cfg );
    Delay_ms( 1000 );
    
    log_printf( &logger, "Power ON\r\n" );
    btaudio_set_power_on( &btaudio );
    btaudio_process( RESPONSE_NULL );
    
    log_printf( &logger, "Factory reset\r\n" );
    btaudio_set_factory_defaults( &btaudio );
    btaudio_process( RESPONSE_NULL );
    
    log_printf( &logger, "Set device name\r\n" );
    btaudio_set_device_name( &btaudio, "BT Audio click" );
    btaudio_reset( &btaudio );
    btaudio_process( RESPONSE_AOK );
    
    log_printf( &logger, "Set data mode\r\n" );
    btaudio_set_cmd_mode( &btaudio, 1 );
    btaudio_process( RESPONSE_NULL );
}

void application_task ( void )
{
    btaudio_process( RESPONSE_NULL );
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
