/*!
 * \file 
 * \brief BLE4 Click example
 * 
 * # Description
 * This example reads and processes data from BLE 4 Clicks.
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
 * - ble4_process ( ) - Logs all received messages on UART, and sends the certain message back to the connected device.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ble4.h"
#include "string.h"

#define PROCESS_COUNTER 5
#define PROCESS_RX_BUFFER_SIZE 100
#define PROCESS_PARSER_BUFFER_SIZE 100

// ------------------------------------------------------------------ VARIABLES

static ble4_t ble4;
static log_t logger;
static uint8_t data_mode = 0;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static int8_t ble4_process ( void )
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
        rsp_size = ble4_generic_read( &ble4, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            if (strstr(current_parser_buf, "ERROR")) {
               return -1;
            }
               
            if (strstr(current_parser_buf, "OK")) {
               log_printf( &logger, "%s", current_parser_buf );
               Delay_100ms( );
               return 1;
            }
               
            if ( data_mode == 1) {
                log_printf( &logger, "%s", current_parser_buf );
                uart_write( &ble4.uart, "Hello", 5 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                uart_write( &ble4.uart, "BLE4", 4 );
            }
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms ( 100 );
        }
    }
    
    return 0;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble4_cfg_t cfg;

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

    ble4_cfg_setup( &cfg );
    BLE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble4_init( &ble4, &cfg );

    ble4_reset( &ble4 );
    Delay_1sec( );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    ble4_set_dsr_pin( &ble4, 1 );
    Delay_ms ( 20 );

    do {
        ble4_set_echo_cmd( &ble4, 1 );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_set_local_name_cmd( &ble4, "BLE 4 Click" );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_connectability_en_cmd( &ble4, BLE4_GAP_CONNECTABLE_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_discoverability_en_cmd( &ble4, BLE4_GAP_GENERAL_DISCOVERABLE_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    do {
        ble4_enter_mode_cmd( &ble4, BLE4_DATA_MODE );
        Delay_100ms( );
    }
    while( ble4_process( ) != 1 );
    
    ble4_set_dsr_pin( &ble4, 0 );
    Delay_ms ( 20 );
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}

void application_task ( void )
{
    ble4_process( );
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
