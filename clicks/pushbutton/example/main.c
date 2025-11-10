/*!
 * @file main.c
 * @brief Push Button Click example
 *
 * # Description
 * This example demonstrates the use of the Push Button Click board 
 * by reading the output and interrupt pin states. The OUT pin state 
 * is logged whenever it changes, and if the output remains active 
 * longer than the timeout period, it is automatically cleared.
 * If the button is pressed and held longer than 8 seconds, 
 * the output shuts down.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the log interface and the Push Button Click driver.
 *
 * ## Application Task
 * Monitors the OUT pin state, logs changes, resets the timeout 
 * counter when the button is pressed, and clears the output after 
 * a timeout period or if the button is pressed longer than 8 seconds.
 *
 * @note
 * The timeout period in this example is set to approximately 10 seconds,
 * and button press longer than 8 seconds will also shut down the output.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pushbutton.h"

static pushbutton_t pushbutton;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pushbutton_cfg_t pushbutton_cfg;  /**< Click config object. */

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
    pushbutton_cfg_setup( &pushbutton_cfg );
    PUSHBUTTON_MAP_MIKROBUS( pushbutton_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == pushbutton_init( &pushbutton, &pushbutton_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint32_t time_cnt = 0;
    static uint8_t out_state_old = 0xFF;
    uint8_t out_state = pushbutton_get_out_pin ( &pushbutton );
    if ( out_state_old != out_state )
    {
        log_printf( &logger, " OUT state: %u\r\n", ( uint16_t ) out_state );
        out_state_old = out_state;
        time_cnt = 0;
    }
    if ( out_state_old && ( time_cnt > 10000 ) )
    {
        log_printf( &logger, " TIMEOUT: clearing output\r\n" );
        pushbutton_clear_output ( &pushbutton );
    }
    if ( !pushbutton_get_int_pin ( &pushbutton ) )
    {
        time_cnt = 0;
    }
    Delay_ms ( 1 );
    time_cnt++;
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
