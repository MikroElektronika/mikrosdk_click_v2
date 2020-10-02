/*!
 * \file 
 * \brief Ble8 Click example
 * 
 * # Description
 * This example reads and processes data from BLE 8 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART serial interface, UART interrupt,
 * and executes a module reset. Allows user to enter command mode.
 * 
 * ## Application Task  
 * This function has two segments.
 * First segment allows user to enter a commands, for using function from driver
 * ( those with AT command ). Second ( default ) segment allows user to comunicate with 
 * other bluetooth devices - by sending data to the ANNA-B112 module.
 * 
 * ## Additional Function
 * - ble8_process ( ) - The general process of collecting presponce that sends a module.
 * - get_rsp - Catches the response bytes and sets flag when the response was ready.
 * - log_rsp - Allows user to see and check the response on the serial terminal.
 * 
 * *note:* 
 * <pre>
 * For using AT commands swich to COMMAND_MODE
 * The all possible commands, module configuration and specification can be found in the 
 * related documents:
 *     [1] ANNA-B112 System Integration Manual, document number UBX-18009821 
 *     [2] u-blox Short Range AT Commands Manual, document number UBX-14044127 
 *     [3] ANNA-B112 Getting Started Guide, document number UBX-18020387 
 *     [4] ANNA-B112 Declaration of Conformity, document number UBX-18058993
 * </pre>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ble8.h"
#include "string.h"

#define PROCESS_COUNTER             10
#define PROCESS_RX_BUFFER_SIZE      500

#define RSP_TERM_CHAR               10
#define CMD_TERM_CHAR               13

// ------------------------------------------------------------------ VARIABLES

//#define COMMAND_MODE

static ble8_t ble8;
static log_t logger;

uint8_t response[ 256 ];
uint8_t rsp_idx;
uint8_t rsp_check;
uint8_t log_check;
uint8_t start_timer;
uint16_t timer_cnt;
uint8_t prev_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void ble8_process ( void )
{
    int16_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    
    while( process_cnt != 0 )
    {
        rsp_size = ble8_generic_read( &ble8, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                ble8_uart_isr( &ble8, uart_rx_buffer[ check_buf_cnt ] ) ;
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

void get_rsp ( uint8_t *rsp_dat )
{
    response[ rsp_idx ] = *rsp_dat;

    if ( ( response[ rsp_idx ] == RSP_TERM_CHAR) || ( rsp_idx == 150 ) )
    {
        start_timer = 0;
        log_check = BLE8_RSP_READY;
    }
    else
    {
        start_timer = 1;
    }
    
    rsp_idx++;
}

void log_rsp ( )
{
    if ( ( log_check == BLE8_RSP_READY ) || ( timer_cnt == 20000 ) )
    {
        char log_ptr[ 256 ];
        uint8_t rx_cnt = 0;
        uint8_t rx_idx = 0;
        
        timer_cnt = 0;
        start_timer = 0;

        while ( rx_idx < rsp_idx )
        {
            if ( ( prev_data == CMD_TERM_CHAR ) && ( response[ rx_idx ] != RSP_TERM_CHAR ) && ( response[ rx_idx ] != CMD_TERM_CHAR ) )
            {
                log_ptr[ rx_cnt ] = RSP_TERM_CHAR;
                rx_cnt++;
                log_ptr[ rx_cnt ] = response[ rx_idx ];
            }
            else
            {
                log_ptr[ rx_cnt ] = response[ rx_idx ];
            }

            prev_data = response[ rx_idx ];
            rx_idx++;
            rx_cnt++;
        }

        rsp_idx = 0;
        rsp_check = 1;
        log_check = BLE8_RSP_NOT_READY;
        
        log_ptr[ rx_cnt ] = BLE8_END_BUFF;
        log_printf( &logger, "%s", log_ptr );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble8_cfg_setup( &cfg );
    BLE8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble8_init( &ble8, &cfg );

    ble8_response_handler_set( &ble8, &get_rsp );
    Delay_ms( 200 );

    ble8_reset( &ble8 );
    Delay_ms( 2000 );

    rsp_idx = 0;
    rsp_check = 1;
    start_timer = 0;
    timer_cnt = 0;
    prev_data = 0;
    log_check = BLE8_RSP_NOT_READY;

    #ifdef COMMAND_MODE
        log_printf( &logger, "COMMAND MODE ENTERING...\r\n" );

        ble8_set_dsr_pin( &ble8, 1 );
        Delay_ms( 20 );
        ble8_set_dsr_pin( &ble8, 0 );
        Delay_ms( 20 );

        ble8_set_echo_cmd( &ble8, BLE8_ECHO_OFF );
        ble8_process( );
        log_rsp( );
        Delay_ms( 100 );
    #else
        log_printf( &logger, "DEFAULT MODE ENTERING...\r\n" );
    #endif
}

void application_task ( void )
{
    ble8_process( );

    if ( start_timer == 1 )
    {
        timer_cnt++;
    }

    log_rsp( );
    Delay_us( 1 );
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
