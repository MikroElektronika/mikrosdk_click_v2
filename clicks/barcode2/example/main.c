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
 * Initializes UART driver used for communication
 * and another UART bus used for data logging.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the Barcode 2 Click board.
 * Barcode 2 Click starts scanning every 3 seconds.
 * When the barcode is detected, program enters interrupt routine
 * and displays a scanned barcode or QRcode data.
 * Then disables scanning also in an interval of 3 seconds.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * ## Additional Function
 * - barcode2_process ( ) - The general process of collecting presponce 
 *                          that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "barcode2.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static barcode2_t barcode2;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void barcode2_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;

    while( process_cnt != 0 )
    {
        rsp_size = barcode2_generic_read( &barcode2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }

            log_printf( &logger, " %s \r\n", uart_rx_buffer );
            Delay_ms( 100 );
            
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
    barcode2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    barcode2_cfg_setup( &cfg );
    BARCODE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barcode2_init( &barcode2, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Scan barcodes:   \r\n" );
    barcode2_enable_scaning( &barcode2, BARCODE2_ENABLE );
    barcode2_process(  );
    Delay_ms( 3000 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Scanning is off   \r\n" );
    barcode2_enable_scaning( &barcode2, BARCODE2_DISABLE );
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
