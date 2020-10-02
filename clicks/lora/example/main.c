/*!
 * \file 
 * \brief LoRa Click example
 * 
 * # Description
 * This example reads and processes data from LoRa clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and LoRa init.
 * 
 * ## Application Task  
 * The transceiver sends one by one byte in UART which is for the work of the lora,
 * the Receiver mode, receives one byte and logs it on usbuart. Receiver mode is default mode.
 * 
 * ## Additional Function
 * - lora_process ( ) - The general process of collecting presponce that sends a module.
 * - bool is_digit ( char c ) - Chek if char c is digit 
 * - hex_to_int ( char* origin, uint8_t* result ) - Convert hexadecimal to int value.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lora.h"
#include "string.h"
#include "conversions.h"

#define PROCESS_COUNTER 3
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSCEIVER

static lora_t lora;
static log_t logger;

uint8_t cnt;
uint8_t send_data;
int8_t  int_data;
uint8_t rx_state;
uint8_t tx_state;

char send_hex[ 50 ];
char tmp_txt[ 50 ];
uint8_t send_message[ 8 ] = { 'M', 'i', 'k', 'r', 'o', 'E', ' ', 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lora_process ( void )
{
    int16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while ( process_cnt != 0 )
    {
        rsp_size = lora_generic_read( &lora, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != - 1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                lora_put_char( &lora, uart_rx_buffer[ check_buf_cnt ] );
                lora_isr_process( &lora );
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

bool is_digit ( char c )
{
    if ( c >= '0' && c <= '9' )
    {
        return true;
    }

    return false;
}

void hex_to_int ( char* origin, uint8_t* result )
{
    uint8_t len = strlen( origin );
    uint8_t idx, ptr, factor;

    if ( len > 0 )
    {
         *result = 0;
         factor = 1;

         for ( idx = len - 1; idx >= 0; idx-- )
         {
               if ( is_digit( *( origin + idx ) ) )
               {
                   *result += ( *( origin + idx ) - '0' ) * factor;
               }
               else
               {
                    if ( *( origin + idx ) >= 'A' && *( origin + idx ) <= 'Z' )
                    {
                        ptr = ( *( origin + idx ) - 'A' ) + 10;
                    }
                    else
                    {
                        return;
                    }
                    *result += ( ptr * factor );
                }
                factor *= 16;
          }
     }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void lora_cbk( char* response )
{

}

void application_init ( void )
{
    log_cfg_t log_cfg;
    lora_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lora_cfg_setup( &cfg );
    LORA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lora_init( &lora, &cfg );

    lora_default_cfg( &lora, 0, &lora_cbk );

    lora_cmd( &lora, LORA_CMD_SYS_GET_VER, &tmp_txt[ 0 ] );

    lora_cmd( &lora, LORA_CMD_MAC_PAUSE,  &tmp_txt[ 0 ] );
    log_printf( &logger, "mac pause\r\n" );
    for ( cnt = 0; cnt < 10; cnt++ )
    {
        log_printf( &logger, "%c", tmp_txt[ cnt ] );
    }

    log_printf( &logger, "\r\n" );

    lora_cmd( &lora, LORA_CMD_RADIO_SET_WDT, &tmp_txt[ 0 ] );

    log_printf( &logger, "radio set wdt 0\r\n" );
    log_printf( &logger, "%s\r\n", &tmp_txt[ 0 ] );
}

void application_task ( void )
{
    char *ptr;
    lora_process( );
    
    #ifdef DEMO_APP_RECEIVER
        rx_state = lora_rx( &lora, LORA_ARG_0, &tmp_txt[ 0 ] );
        if ( rx_state == 0 )
        {
            tmp_txt[ 12 ] = 0;
            ptr = ( char* )&int_data;
            hex_to_int( &tmp_txt[ 10 ], ptr );

            log_printf( &logger, "%c", int_data  );
            log_printf( &logger, "\r\n");
        }
    #endif
    
    #ifdef DEMO_APP_TRANSCEIVER
        for ( cnt = 0; cnt < 7; cnt++ )
        {
            send_data = send_message[ cnt ] ;
            int8_to_hex( send_data, send_hex );
            tx_state = lora_tx( &lora, &send_hex[ 0 ] );
            if ( tx_state == 0 )
            {
                log_printf( &logger, "  Response : %s\r\n", &tmp_txt[ 0 ] );
            }
            Delay_ms( 500 );
        }
    #endif
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
