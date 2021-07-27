/*!
 * @file main.c
 * @brief LR 2 Click Example.
 *
 * # Description
 * This example reads and processes data from LR 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and LR 2 init.
 * 
 * ## Application Task  
 * Transmitter mode - sends one by one byte sequence of the desired message each second and 
 * checks if it is sent successfully.
 * Receiver mode - displays all the received characters on USB UART.
 * 
 * ## Additional Functions
 * - lr2_process ( ) - The general process of collecting data the module sends.
 * - bool is_digit ( char c ) - Checks if input is a digit 
 * - hex_to_int ( char* origin, uint8_t* result ) - Converts hexadecimal to int value.
 *
 * @author Stefan Ilic
 *
 */


#include "board.h"
#include "log.h"
#include "lr2.h"
#include "string.h"
#include "conversions.h"

#define PROCESS_COUNTER 5
#define PROCESS_RX_BUFFER_SIZE 300

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITTER

static lr2_t lr2;
static log_t logger;

uint8_t cnt;
uint8_t send_data;
int8_t  int_data;
uint8_t rx_state;
uint8_t tx_state;

char send_hex[ 50 ];
char tmp_txt[ 50 ];
uint8_t send_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lr2_process ( void ) {
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while ( process_cnt != 0 ) {
        rsp_size = lr2_generic_read( &lr2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 ) {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ ) {
                lr2_put_char( &lr2, uart_rx_buffer[ check_buf_cnt ] );
                lr2_isr_process( &lr2 );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } else {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

bool is_digit ( char c ) {
    if ( c >= '0' && c <= '9' ) {
        return true;
    }

    return false;
}

void hex_to_int ( char* origin, uint8_t* result ) {
    uint8_t len = strlen( origin );
    uint8_t idx, ptr, factor;

    if ( len > 0 ) {
        *result = 0;
        factor = 1;

        for ( idx = len - 1; idx >= 0; idx-- ) {
            if ( is_digit( *( origin + idx ) ) ) {
                *result += ( *( origin + idx ) - '0' ) * factor;
               } else {
                    if ( *( origin + idx ) >= 'A' && *( origin + idx ) <= 'Z' ) {
                        
                        ptr = ( *( origin + idx ) - 'A' ) + 10;
                        
                    } else {
                        return;
                    }
                    *result += ( ptr * factor );
                }
                factor *= 16;
          }
     }
}

void lr2_cbk( char* response ) {
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    log_cfg_t log_cfg;
    lr2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lr2_cfg_setup( &cfg );
    LR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr2_init( &lr2, &cfg );

    lr2_default_cfg( &lr2, 0, &lr2_cbk );

    lr2_cmd( &lr2, LR2_CMD_SYS_GET_VER, &tmp_txt[ 0 ] );

    lr2_cmd( &lr2, LR2_CMD_MAC_PAUSE,  &tmp_txt[ 0 ] );
    log_printf( &logger, "mac pause\r\n" );
    for ( cnt = 0; cnt < 10; cnt++ ) {
        log_printf( &logger, "%c", tmp_txt[ cnt ] );
    }

    log_printf( &logger, "\r\n" );

    lr2_cmd( &lr2, LR2_CMD_RADIO_SET_WDT, &tmp_txt[ 0 ] );

    log_printf( &logger, "radio set wdt 0\r\n" );
    log_printf( &logger, "%s\r\n", &tmp_txt[ 0 ] );
}

void application_task ( void ) {
    char *ptr;
    lr2_process( );
    
#ifdef DEMO_APP_RECEIVER
    rx_state = lr2_rx( &lr2, LR2_ARG_0, &tmp_txt[ 0 ] );
    if ( rx_state == 0 ) {
        tmp_txt[ 12 ] = 0;
        ptr = ( char* )&int_data;
        hex_to_int( &tmp_txt[ 10 ], ptr );

        log_printf( &logger, "%c", int_data  );
    }
#endif

#ifdef DEMO_APP_TRANSMITTER
    for ( cnt = 0; cnt < 9; cnt++ ) {
        send_data = send_message[ cnt ] ;
        int8_to_hex( send_data, send_hex );
        tx_state = lr2_tx( &lr2, &send_hex[ 0 ] );
        if ( tx_state == 0 ) {
            log_printf( &logger, "  Response : %s\r\n", &tmp_txt[ 0 ] );
        }
        Delay_ms( 1000 );
    }
#endif
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
