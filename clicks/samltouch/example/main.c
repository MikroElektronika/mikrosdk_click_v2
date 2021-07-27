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
 * - samltouch_process ( ) - The general process of collecting data the module sends.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "samltouch.h"
#include "string.h"

#define PROCESS_RX_BUFFER_SIZE 1000
#define PROCESS_BUFFER_SIZE 80

// ------------------------------------------------------------------ VARIABLES

static samltouch_t samltouch;
static log_t logger;

samltouch_state_t saml_touch_status;

static char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
static char current_parser_buffer[ PROCESS_BUFFER_SIZE ];

static uint8_t flag_1 = 0;
static uint8_t flag_2 = 0;
static uint16_t wait_cnt = 0;
static uint16_t button1_cnt = 0;
static uint16_t button2_cnt = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void samltouch_process ( void )
{
    int32_t rsp_size;
    uint16_t check_buf_cnt;
    
    // Clear RX buffer
    memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    // Clear Parser buffer
    memset( current_parser_buffer, 0, PROCESS_BUFFER_SIZE );
    
    rsp_size = samltouch_generic_read( &samltouch, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
    
    if ( rsp_size > 0 )
    {  
        for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ ) {
            if ( uart_rx_buffer[check_buf_cnt] == SAMLTOUCH_START_FRAME && ( (check_buf_cnt + 76) <= rsp_size ) ) {
                memcpy( current_parser_buffer, &uart_rx_buffer[check_buf_cnt], 76 );
                if ( current_parser_buffer[ 10 ] == 1 ) 
                {
                    button1_cnt++;
                }
                if ( current_parser_buffer[ 20 ] == 1 ) 
                {
                    button2_cnt++;
                }
                flag_1 = 1;
                break;
            }
        }
    }
}

void parser_application ( )
{
    samltouch_process( );

    if ( flag_1 == 1 )
    {
        samltouch_parser( current_parser_buffer, &saml_touch_status );
        
        flag_2 = 0;
        
        if ( saml_touch_status.button2 == 1 && button2_cnt > 2 )
        {
            log_printf( &logger, "\r\n Button 2 is pressed. \r\n" );
            flag_2 = 1;
            wait_cnt = 0;
            button2_cnt = 2;
        }
        
        if ( saml_touch_status.button1 == 1 && button1_cnt > 2 )
        {
            log_printf( &logger, "\r\n Button 1 is pressed. \r\n" );
            flag_2 = 1;
            wait_cnt = 0;
            button1_cnt = 2;
        }
        
        if ( saml_touch_status.sw_state == 1 && saml_touch_status.sw_pos != 0 )
        {
            log_printf( &logger, "\r\n Slider position is  %u \r\n", (uint16_t) saml_touch_status.sw_pos );
            flag_2 = 1;
            wait_cnt = 0;
        }
        flag_1 = 0;
    }
     
    if ( flag_2 == 1 ) 
    {
        Delay_100ms( );
    }
    else 
    {
        if ( wait_cnt++%50 == 0 )
        {
            log_printf( &logger, "\r\n Waiting for an event: \r\n" );
            button1_cnt = 0;
            button2_cnt = 0;
        }
        log_printf( &logger, "." );
        Delay_100ms( );
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
    parser_application( );
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
