/*!
 * \file 
 * \brief Ble3 Click example
 * 
 * # Description
 * This example reads and processes data from BLE 3 clicks.
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
 * - ble3_process ( ) - Logs all received messages on UART, and sends the certain message back to the connected device.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ble3.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 100
#define PROCESS_PARSER_BUFFER_SIZE 100

// ------------------------------------------------------------------ VARIABLES

static char AT[ ] = "AT\r";
static char ATE1[ ] = "ATE1\r";
static char AT_UBTLN[ ] = "AT+UBTLN=\"BLE 3 Click\"\r";
static char AT_UBTDM[ ] = "AT+UBTDM=3\r";
static char AT_UBTCM[ ] = "AT+UBTCM=2\r";
static char AT_UBTPM[ ] = "AT+UBTPM=2\r";
static char ATO1[ ] = "ATO1\r";

static ble3_t ble3;
static log_t logger;
static uint8_t data_mode = 0;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static int8_t ble3_process ( void )
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
        rsp_size = ble3_generic_read( &ble3, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
               return 1;
            }
               
            if ( data_mode == 1) {
                log_printf( &logger, "%s", current_parser_buf );
                ble3_generic_write( &ble3, "Hello", 5 );
                Delay_ms( 2000 );
                ble3_generic_write( &ble3, "MikroE", 6 );
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
    ble3_cfg_t cfg;
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

    ble3_cfg_setup( &cfg );
    BLE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble3_init( &ble3, &cfg );
    
    log_printf( &logger, "Configuring the module...\n" );
    Delay_1sec( );
    
    do {
        ble3_generic_write( &ble3, AT, (uint16_t) strlen( AT ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, ATE1, (uint16_t) strlen( ATE1 ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTLN, (uint16_t) strlen( AT_UBTLN ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTDM, (uint16_t) strlen( AT_UBTDM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTCM, (uint16_t) strlen( AT_UBTCM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, AT_UBTPM, (uint16_t) strlen( AT_UBTPM ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    do {
        ble3_generic_write( &ble3, ATO1, (uint16_t) strlen( ATO1 ) );
        Delay_100ms( );
    }
    while(ble3_process(  ) != 1);
    
    data_mode = 1;
    log_printf( &logger, "The module has been configured.\n" );
}

void application_task ( void )
{
    ble3_process(  );
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
