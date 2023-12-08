 /*!
 * \file 
 * \brief Microwave2 Click example
 * 
 * # Description
 * This application is an accurate and reliable short to medium range motion detection.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the click board for communication.
 * 
 * ## Application Task  
 * Data sent from the click board is captured and different actions are applied.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "microwave2.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static microwave2_t microwave2;
static log_t logger;
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void microwave2_parser ( char * buffer ) 
{
    for ( uint16_t cnt = 0; cnt < sizeof( buffer ); cnt++ ) 
    {
        if ( buffer[ cnt ] == '@' ) 
        {
            if ( buffer[ cnt+1 ] == 'C' ) {
                log_printf( &logger, "Approaching \r\n" );
            }
            if ( buffer[ cnt+1 ] == 'L' ) {
                log_printf( &logger, "Moving away \r\n" );
            }
            if ( buffer[ cnt+1 ] == 'N' ) {
                log_printf( &logger, "No movement \r\n");
            }
        }
    }
}

static void microwave2_process ( void )
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
        rsp_size = microwave2_generic_read( &microwave2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            Delay_10ms( );
        }
    }
    microwave2_parser(current_parser_buf);
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    microwave2_cfg_t cfg;

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

    microwave2_cfg_setup( &cfg );
    MICROWAVE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    microwave2_init( &microwave2, &cfg );
}

void application_task ( void )
{
    microwave2_process();
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
