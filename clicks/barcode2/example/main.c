/*!
 * \file 
 * \brief Barcode2 Click example
 * 
 * # Description
 * This example reads and processes data from Barcode 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the UART driver used for communication and another UART bus used 
 * for data logging.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the Barcode 2 Click board.
 * First, it enables scanning and waits up to 10 seconds for the barcode to be detected.
 * If the barcode or QR Code is detected, it displays its content to the USB UART.
 * After that, disables scanning for 3 seconds.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * ## Additional Function
 * - barcode2_process ( ) - The general process of collecting data the module sends.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "barcode2.h"
#include "string.h"

#define PROCESS_COUNTER 100
#define PROCESS_RX_BUFFER_SIZE 600
#define PROCESS_PARSER_BUFFER_SIZE 600

// ------------------------------------------------------------------ VARIABLES

static barcode2_t barcode2;
static log_t logger;
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void barcode2_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    // Clear parser buffer
    memset( current_parser_buf, 0, PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = barcode2_generic_read( &barcode2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size >0 )
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
            
            process_cnt = 3;
            
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
    if ( rsp_cnt > 0 )
    {
        if ( rsp_cnt > 80 )
        {
            log_printf( &logger, " QR Code:\r\n%s", current_parser_buf );
        }
        else
        {
            log_printf( &logger, " Barcode: %s", current_parser_buf );
        }
            
        log_printf( &logger, "\r\n------------------------\r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    barcode2_cfg_t cfg;

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

    barcode2_cfg_setup( &cfg );
    BARCODE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barcode2_init( &barcode2, &cfg );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    log_printf( &logger, "   Scanning enabled   \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    barcode2_enable_scaning( &barcode2, BARCODE2_ENABLE );
    barcode2_process(  );

    barcode2_enable_scaning( &barcode2, BARCODE2_DISABLE );
    log_printf( &logger, "   Scanning disabled   \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 3000 );
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
