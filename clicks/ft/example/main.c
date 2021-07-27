/*!
 * \file 
 * \brief Ft Click example
 * 
 * # Description
 * This example reads and processes data from FT clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize driver init.
 * 
 * ## Application Task  
 * RX mode : Reads and logs new receive data.
 * TX mode : sends (MikroE) data every 1 seconds.
 * 
 * ## Additional Function
 * - ft_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ft.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static ft_t ft;
static log_t logger;

static char MIKROE_DATA_BUF[ 7 ] = "MikroE";
static uint8_t MIKROE_DATA_BUF_LEN = 6;
static uint8_t MIKROE_DATA_QUEUE = 1;
static uint8_t rsp_data_buf[ 256 ];
static uint8_t rsp_data_num = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void ft_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;  
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = ft_generic_read( &ft, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                ft_isr_parser( &ft, uart_rx_buffer[ check_buf_cnt ] ); 
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
    ft_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    ft_cfg_setup( &cfg );
    FT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ft_init( &ft, &cfg );

    #ifdef DEMO_APP_RECEIVER
        log_printf( &logger, "---------------------------\r\n" );
        log_printf( &logger, "--> CURRENT MODE [ RX ] <--\r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    #endif

    #ifdef DEMO_APP_TRANSMITER
        log_printf( &logger, "---------------------------\r\n" );
        log_printf( &logger, "--> CURRENT MODE [ TX ] <--\r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    #endif
}

void application_task ( void )
{
    #ifdef DEMO_APP_RECEIVER
        ft_process(  );
        if ( ft_get_data_status( &ft ) == FT_NEW_DATA_AVAILABLE )
        {
            ft_process(  );
            rsp_data_num = ft_get_data( &ft, &rsp_data_buf[ 0 ] );
            if( rsp_data_num != 0 )
            {
                log_printf( &logger, "---------------------------\r\n" );
                log_printf( &logger, "--> READ: %s\r\n", rsp_data_buf );
                log_printf( &logger, "---------------------------\r\n" );
            }
        }
    #endif

    #ifdef DEMO_APP_TRANSMITER
        log_printf( &logger, "--------------------------\r\n" );
        log_printf( &logger, "-->  SEND MIKROE DATA  <--\r\n" );
        log_printf( &logger, "--------------------------\r\n" );
        ft_send_package( &ft, &MIKROE_DATA_BUF[ 0 ], MIKROE_DATA_BUF_LEN, MIKROE_DATA_QUEUE );
        Delay_ms( 1000 );
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
