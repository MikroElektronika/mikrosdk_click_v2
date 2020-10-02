/*!
 * \file 
 * \brief SamlTouch Click example
 * 
 * # Description
 * This example reads and processes data from SAML Touch clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - samltouch_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "samltouch.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 2000
#define PROCESS_PARSER_BUFFER_SIZE 2000

// ------------------------------------------------------------------ VARIABLES

static samltouch_t samltouch;
static log_t logger;

samltouch_state_t saml_touch_status;

static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
static char current_parser_buffer[ PROCESS_PARSER_BUFFER_SIZE ];

static uint8_t flag_1;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void samltouch_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    uint16_t check_buf_cnt;
    
    // Clear RX buffer
    memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    // Clear Parser buffer
    memset( current_parser_buffer, 0, PROCESS_PARSER_BUFFER_SIZE );

    rsp_size = samltouch_generic_read( &samltouch, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

    if ( rsp_size > 0 )
    {  
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
        {
            if ( ( uart_rx_buffer[ check_buf_cnt ] == 0x55 ) && ( flag_1 == 0 ) )
           {
                flag_1 = 1;
           }
           if ( flag_1 == 1 )
           {
                current_parser_buffer[ rsp_cnt++ ] = uart_rx_buffer[ check_buf_cnt ];
           }
           if ( ( uart_rx_buffer[ check_buf_cnt ] == 0xAA ) && ( ( rsp_cnt ) > 70 ) )
           {
                flag_1 = 2;
                rsp_cnt = 0;
                
                return;
           }
           Delay_ms( 10 );
        }
    } 
    Delay_ms( 100 );
}

void parser_application ( char *rsp )
{
    samltouch_process( );

    if ( flag_1 == 2 )
    {
        samltouch_parser( rsp, &saml_touch_status );

        if ( saml_touch_status.button2 == 1 )
        {
            log_printf( &logger, "Button 2 is pressed. \r\n" );
        }
        else if ( saml_touch_status.button1 == 1 )
        {
            log_printf( &logger, "Button 1 is pressed.\r\n" );
        }
        
        if ( saml_touch_status.sw_pos != 0 )
        {
            log_printf( &logger, "Slider position is  %d \r\n", saml_touch_status.sw_pos );
    
        }
        flag_1 = 0;
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    samltouch_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    samltouch_cfg_setup( &cfg );
    SAMLTOUCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    samltouch_init( &samltouch, &cfg );
    
    Delay_ms( 500 );
}

void application_task ( void )
{
    parser_application( current_parser_buffer );
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
