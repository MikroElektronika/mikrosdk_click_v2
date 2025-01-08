/*!
 * \file 
 * \brief Barcode Click example
 * 
 * # Description
 * This example reads and processes data from Barcode Clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - barcode_process( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "barcode.h"
#include "string.h"

#define PROCESS_COUNTER 2000
#define PROCESS_RX_BUFFER_SIZE 300

// ------------------------------------------------------------------ VARIABLES

static barcode_t barcode;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void barcode_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;

    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint16_t process_cnt = PROCESS_COUNTER;

    while( process_cnt > 0 )
    {
        rsp_size = barcode_generic_read( &barcode, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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

            log_printf( &logger, "%s", uart_rx_buffer );

            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;

            // Process delay 
            Delay_ms ( 1 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    barcode_cfg_t cfg;

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
    log_info( &logger, "--->  BarCode Click Init  <---" );

    //  Click initialization.

    barcode_cfg_setup( &cfg );
    BARCODE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barcode_init( &barcode, &cfg );

    Delay_ms ( 500 );
}

void application_task ( void )
{
    barcode_enable_scaning( &barcode, BARCODE_LOGIC_ON );
    barcode_process( );
    barcode_enable_scaning( &barcode, BARCODE_LOGIC_OFF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
