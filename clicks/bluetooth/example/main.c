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
 * Initialization driver enables - UART,
 * enable interrupts routine, enter command mode, set device name,
 * set extended status string, set operating mode, set auth,
 * and set security pin code also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Bluetooth click board.
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - bluetooth_process ( ) - The general process of collecting responce that sends a module.
 * - bluetooth_parser ( uint8_t input_data ) - Function for parsing data.
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

#define PROCESS_COUNTER 5
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

static bluetooth_t bluetooth;
static log_t logger;

uint8_t cmd_mode;
uint8_t data_ready;

uint8_t DEVICE_NAME_DATA[ 20 ] = { 'B', 'l', 'u', 'e', 't', 'o', 'o', 't', 'h', 'C', 'l', 'i', 'c', 'k' };
uint8_t EXTENDED_STRING_DATA[ 10 ] = { 'S', 'l', 'a', 'v', 'e' };
uint8_t PIN_CODE_DATA[ 10 ] = { '1', '2', '3', '4' };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void bluetooth_parser ( uint8_t input_data )
{
    if ( cmd_mode )
    {
        switch ( bluetooth.bt_state )
        {
            case  0:
            {
                bluetooth.response = 0;

                if ( input_data == 'C' )
                    bluetooth.bt_state = 1;

                if ( input_data == 'A' )
                    bluetooth.bt_state = 11;

                if ( input_data == 'E' )
                    bluetooth.bt_state = 31;
                break;
            }
            case  1:
            {
                if ( input_data == 'M' )
                    bluetooth.bt_state = 2;
                else if ( input_data == 'O' )
                    bluetooth.bt_state = 22;
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case  2:
            {
                if ( input_data == 'D' )
                {
                    bluetooth.response = BLUETOOTH_CMD;
                    bluetooth.bt_state = 40;
                }
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case 11:
            {
                if ( input_data == 'O' )
                    bluetooth.bt_state = 12;
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case 12:
            {
                if ( input_data == 'K' )
                {
                    bluetooth.response = BLUETOOTH_AOK;
                    bluetooth.bt_state = 40;
                }
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case 22:
            {
                if ( input_data == 'N' )
                    bluetooth.bt_state = 23;
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case 23:
            {
                if ( input_data == 'N' )
                {
                    bluetooth.response = BLUETOOTH_CONN; 
                    bluetooth.response_finished = 1;
                    bluetooth.response_id = bluetooth.response;
                }

                bluetooth.bt_state = 0;
                break;
            }
            case 31:
            {
                if ( input_data == 'N' )
                    bluetooth.bt_state = 32;
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case 32:
            {
                if ( input_data == 'D' )
                {
                    bluetooth.response = BLUETOOTH_DONE;
                    bluetooth.bt_state = 40;
                }
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case 40:
            {
                if ( input_data == 13 )
                    bluetooth.bt_state = 41;
                else
                    bluetooth.bt_state = 0;
                break;
            }
            case 41:
            {
                if ( input_data == 10 )
                {
                    bluetooth.response_finished = 1;
                    bluetooth.response_id = bluetooth.response;
                }

                bluetooth.bt_state = 0;
                break;
            }
            default:
            {
                bluetooth.bt_state = 0;
                break;
            }
        }
    }
    else
    {
        if ( input_data == 13 )
        {
            bluetooth.driver_buffer[ bluetooth.buffer_cnt ] = 0;
            data_ready = 1;

            log_printf( &logger, " * Interrupt: * \r\n" );
            log_printf( &logger, "%s\r\n", bluetooth.driver_buffer );
        }
        else
        {
            bluetooth.driver_buffer[ bluetooth.buffer_cnt ] = input_data;
            bluetooth.buffer_cnt++;
        }
    }
}

static void bluetooth_process ( void )
{
    int16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;  
    uint8_t process_cnt = PROCESS_COUNTER;
    
    
    while( process_cnt != 0 )
    {
        rsp_size = bluetooth_generic_read( &bluetooth, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                bluetooth_parser( uart_rx_buffer[ check_buf_cnt ] ); 
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    bluetooth_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    bluetooth_cfg_setup( &cfg );
    BLUETOOTH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bluetooth_init( &bluetooth, &cfg );

    cmd_mode = 1;
    data_ready = 0;

    Delay_ms( 500 );

    do
    {    
        bluetooth_enter_command_mode( &bluetooth );
        Delay_ms( 500 );
        log_printf( &logger, " --- Command mode --- \r\n" );
        bluetooth_process(  );
    }
    while ( bluetooth_get_response( &bluetooth ) != BLUETOOTH_CMD );

    do
    {
        bluetooth_set_device_name( &bluetooth, &DEVICE_NAME_DATA[ 0 ] );
        Delay_ms( 500 );
        log_printf( &logger, " --- Device name --- \r\n" );
        bluetooth_process(  );
    }
    while ( bluetooth_get_response( &bluetooth ) != BLUETOOTH_AOK );

    do
    {
        bluetooth_set_extended_status_string( &bluetooth, &EXTENDED_STRING_DATA[ 0 ] );
        Delay_ms( 500 );
        log_printf( &logger, " --- Status string --- \r\n" );
        bluetooth_process(  );
    }
    while ( bluetooth_get_response( &bluetooth ) != BLUETOOTH_AOK );

    do
    {
        bluetooth_set_operating_mode( &bluetooth, 0 );
        Delay_ms( 500 );
        log_printf( &logger, " --- Operating mode --- \r\n" );
        bluetooth_process(  );
    }
    while ( bluetooth_get_response( &bluetooth ) != BLUETOOTH_AOK );

    do
    {
        bluetooth_set_authentication( &bluetooth, 1 );
        Delay_ms( 500 );
        log_printf( &logger, " --- Authentication --- \r\n" );
        bluetooth_process(  );
    }
    while ( bluetooth_get_response( &bluetooth ) != BLUETOOTH_AOK );

    do
    {
        bluetooth_set_security_pin_code( &bluetooth, &PIN_CODE_DATA[ 0 ] );
        Delay_ms( 500 );
        log_printf( &logger, " --- Pin code --- \r\n" );
        bluetooth_process(  );
    }
    while ( bluetooth_get_response( &bluetooth ) != BLUETOOTH_AOK );

    cmd_mode = 0;
    data_ready = 0;
}

void application_task ( void )
{
    bluetooth.buffer_cnt = 0;

    memset( bluetooth.driver_buffer, 0, 255 );
    
    log_printf( &logger, " * Waiting for message. * \r\n" );
    Delay_ms ( 1000 );

    while ( !data_ready )
    {
        bluetooth_process(  );
        Delay_ms ( 1000 );
    }

    data_ready = 0;

    bluetooth.buffer_cnt = 0;
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
