/*!
 * @file main.c
 * @brief Expand 17 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 17 Click board by setting and reading 
 * the ports state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets 
 * half of pins as output ( IO5, IO6, IO7 and IO8 ) and the 
 * half of the pins as inputs ( IO1, IO2, IO3 and IO4 ).
 *
 * ## Application Task
 * Sets the state of the output pins and then reads the status of the input pins
 * and displays the results on the USB UART approximately every 2 seconds.
 *
 * @note
 * In order for this example to work as intended it is necessary to connect the input and output pins 
 * eg. IO1 and IO5, IO2 and IO6 etc. Floating input pins will be shown as a high state.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "expand17.h"

static expand17_t expand17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand17_cfg_t expand17_cfg;  /**< Click config object. */

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
    expand17_cfg_setup( &expand17_cfg );
    EXPAND17_MAP_MIKROBUS( expand17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand17_init( &expand17, &expand17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND17_ERROR == expand17_default_cfg ( &expand17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t input_state = 0;

    log_printf( &logger, " Setting output pins state: HIGH \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_set_output_state( &expand17, EXPAND17_NO_IO_PIN_MASK, EXPAND17_IO_5_PIN_MASK | 
                                          EXPAND17_IO_6_PIN_MASK | EXPAND17_IO_7_PIN_MASK | 
                                          EXPAND17_IO_8_PIN_MASK );

    log_printf( &logger, " State of input pins: \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_get_input_state( &expand17, &input_state );
    if ( input_state & EXPAND17_IO_1_PIN_MASK )
    {
        log_printf( &logger, " IO1 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO1 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_2_PIN_MASK )
    {
        log_printf( &logger, " IO2 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO2 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_3_PIN_MASK )
    {
        log_printf( &logger, " IO3 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO3 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_4_PIN_MASK )
    {
        log_printf( &logger, " IO4 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO4 - LOW \r\n" );
    }
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Setting output pins state: LOW \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_set_output_state( &expand17, EXPAND17_IO_5_PIN_MASK | EXPAND17_IO_6_PIN_MASK | 
                                          EXPAND17_IO_7_PIN_MASK | EXPAND17_IO_8_PIN_MASK, 
                                          EXPAND17_NO_IO_PIN_MASK );

    log_printf( &logger, " State of input pins: \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_get_input_state( &expand17, &input_state );
    if ( input_state & EXPAND17_IO_1_PIN_MASK )
    {
        log_printf( &logger, " IO1 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO1 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_2_PIN_MASK )
    {
        log_printf( &logger, " IO2 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO2 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_3_PIN_MASK )
    {
        log_printf( &logger, " IO3 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO3 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_4_PIN_MASK )
    {
        log_printf( &logger, " IO4 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO4 - LOW \r\n" );
    }
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
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
