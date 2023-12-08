/*!
 * @file main.c
 * @brief IR Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the IR Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - GPIO and Log. 
 * 
 * ## Application Task
 * This example contains two parts :
 * - Transmitter mode - Sends data using NEC protocol.
 * - Receiver mode - Reads data that is been sent using NEC protocol and 
 *                   displaying it on the UART terminal.
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ir.h"

static ir_t ir;
static log_t logger;

uint8_t tx_data[ 8 ] = { 'M', 'i', 'k', 'r', 'o', 'E', '\r', '\n' };

#define IR_TRANSMITTER_MODE 

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ir_cfg_t ir_cfg;    /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    ir_cfg_setup( &ir_cfg );
    IR_MAP_MIKROBUS( ir_cfg, MIKROBUS_1 );
    err_t error_flag = ir_init( &ir, &ir_cfg );
    if ( ( UART_ERROR == error_flag ) || ( PWM_ERROR == error_flag ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    
    #ifdef IR_TRANSMITTER_MODE
        log_printf( &logger, "-  Transmitter mode   - \r\n" );
    #else
        log_printf( &logger, "-    Receiver mode    - \r\n" );
    #endif
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
}

void application_task ( void ) 
{
    #ifdef IR_TRANSMITTER_MODE
        log_printf( &logger, " Sending message." );
        
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            ir_nec_send_command( &ir, 0x00, tx_data[ cnt ] );
            log_printf( &logger, "." );
            Delay_ms( 50 );
        }
        
        log_printf( &logger, "\r\n Message sent! \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - \r\n" );
        Delay_ms( 500 );
    #else
        uint8_t arr;
        char rx_data;
        
        err_t err_flag = ir_nec_read_command ( &ir, &arr, &rx_data );
        
        if ( IR_OK == err_flag )
        {
            log_printf( &logger, "%c", rx_data );
        }
        else
        {
            log_printf( &logger, "Read ERROR! \r\n" );
        }
        Delay_ms( 50 );
    #endif
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
