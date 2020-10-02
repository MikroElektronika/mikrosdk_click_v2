/*!
 * \file 
 * \brief MBusRf4 Click example
 * 
 * # Description
 * This example reads and processes data from M-BUS RF 4 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, reads basic information and checks communication
 * 
 * ## Application Task  
 *  In the RX mode it is waiting to receive data from another module...
 *  In the TX mode sends the data packet....
 * 
 * ## Additional Function
 * - mbusrf4_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mbusrf4.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static mbusrf4_t mbusrf4;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

uint8_t tx_buffer[ 20 ] = 
{ 
    0x44, 0x12, 0x34, 0x56, 0x78,
    0x9A, 0xBC, 0xDF, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x87
};

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void mbusrf4_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt; 
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = mbusrf4_generic_read( &mbusrf4, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                log_printf( &logger, "0x%x  ", uart_rx_buffer[ check_buf_cnt ] );
                Delay_ms( 10 );
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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusrf4_cfg_t cfg;

    uint8_t payload_buff[ 20 ] = { 0 };

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mbusrf4_cfg_setup( &cfg );
    MBUSRF4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusrf4_init( &mbusrf4, &cfg );

    mbusrf4_process( );

    //Command SET mode
    payload_buff[ 0 ] = MBUSRF4_SET_VALUE_IN_EEPROM_MEMORY;
    payload_buff[ 1 ] = MBUSRF4_EEPARAM_WMBUS_MODE_S2_SHORT_PREAMBLE;

    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_SET_MODE, 2, &payload_buff[ 0 ] );
    mbusrf4_process( );
    Delay_ms( 1500 );
    
    // Reads FW version
    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_GET_FW_VERSION, 0, &payload_buff[ 0 ] );

    log_printf( &logger, "\r\n------ FW Version ------ \r\n" );
    mbusrf4_process( );
    log_printf( &logger, " ------------------------ \r\n" );

    Delay_ms( 3000 );

    // Read EEPROM parameter
    payload_buff[ 0 ] = MBUSRF4_EEADDR_WMBUS_C_FIELD;
    payload_buff[ 1 ] = 0x01;
    
    mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_EEPROM_READ, 2, payload_buff );
    
    log_printf( &logger, " ------ EEPROM READ ------ \r\n" );
    mbusrf4_process( );
    log_printf( &logger, " ------------------------- \r\n" );

    Delay_ms( 3000 );
}

void application_task ( void )
{
    // RX App mode
    #ifdef DEMO_APP_RECEIVER
   
       log_printf ( &logger, "----- NEW - RX DATA ---- \r\n" );
       mbusrf4_process(  );
       log_printf ( &logger, " ------------------------ \r\n" );
       Delay_ms( 1500 );

    #endif
    
    // TX App Mode
    #ifdef DEMO_APP_TRANSMITER
    
        mbusrf4_send_command( &mbusrf4, MBUSRF4_CMD_TX_MSG, 18, &tx_buffer[ 0 ] );
        log_printf ( &logger, " ----- SEND - TX DATA ---- \r\n" );
        mbusrf4_process(  );
        log_printf ( &logger, " ------------------------ \r\n" );
        
        Delay_ms( 1500 );

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
