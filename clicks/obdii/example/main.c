/*!
 * \file 
 * \brief Obdii Click example
 * 
 * # Description
 * This example reads and processes data from OBDII clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and reset module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - obdii_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "obdii.h"
#include "string.h"
#include "stdlib.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static obdii_t obdii;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
uint16_t rpm;

#define OBDII_AUTOMODE "ATSP0"
#define RPM_CMD        "010C"

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void obdii_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = obdii_generic_read( &obdii, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == '>' ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 0;
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
    log_printf( &logger, " %s \r\n ", current_parser_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    obdii_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    obdii_cfg_setup( &cfg );
    OBDII_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    obdii_init( &obdii, &cfg );
    obdii_send_command( &obdii, OBDII_AUTOMODE );
    obdii_process( );

    log_printf( &logger, "OBD II initialized \r\n" );
}

void application_task ( void )
{
    uint8_t tmp[ 25 ];

    obdii_send_command( &obdii, RPM_CMD );
    Delay_ms( 100 );
    obdii_process( );
        

    memcpy( &tmp[0], &current_parser_buf[11], 4 );
    tmp[5] = 0;
    rpm = xtoi( &tmp[0] );
    rpm = rpm / 4;

    log_printf( &logger, "Current RPM : %d\r\n", rpm );

    Delay_ms( 1000 );

    obdii_process( );
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
