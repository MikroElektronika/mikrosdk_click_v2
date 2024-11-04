/*!
 * \file 
 * \brief Stspin233 Click example
 * 
 * # Description
 * This application is motor driver.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and configures the Click board.
 * 
 * ## Application Task  
 * This example demonstrates the use of STSPIN233 Click board, by running the motor clockwise and counter clockwise.
 * All results will be displayed on USB UART.
 * 
 * *note:* 
 * For all other commands that you can use to control your engine, 
 * see the firmware documentation. We used an 8 pole motor for the test.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stspin233.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 500
// ------------------------------------------------------------------ VARIABLES

static stspin233_t stspin233;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void stspin233_process ( void )
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
        rsp_size = stspin233_generic_read( &stspin233, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            Delay_100ms( );
        }
    }
}
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin233_cfg_t cfg;

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

    stspin233_cfg_setup( &cfg );
    STSPIN233_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin233_init( &stspin233, &cfg );

    stspin233_default_cfg( &stspin233 );
}

void application_task ( void )
{
    log_printf( &logger, ">>> START MOTOR\r\n" );
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_START_MOTOR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Set clockwise direction\r\n" );
    stspin233_send_double_cmd( &stspin233, STSPIN233_CMD_DIR_MOTOR, STSPIN233_CW_DIR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> Set counter clockwise direction\r\n" );
    stspin233_send_double_cmd( &stspin233, STSPIN233_CMD_DIR_MOTOR, STSPIN233_CCW_DIR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, ">>> STOP MOTOR\r\n" );
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_STOP_MOTOR );
    stspin233_process( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    stspin233_send_single_cmd( &stspin233, STSPIN233_CMD_STATUS );
    stspin233_process( );
    log_printf( &logger, ">>> STATUS: %.5s\r\n", &current_parser_buf[ 9 ] );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------------------\r\n" );
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
