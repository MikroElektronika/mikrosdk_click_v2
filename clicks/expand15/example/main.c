/*!
 * @file main.c
 * @brief Expand 15 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 15 Click board by setting and reading 
 * the ports state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets 
 * half of the port 0 and port 1 pins as output ( P00, P02, P04, P06, P10, P12, P14 and P16) and the 
 * half of the port 0 and port 1 pins as inputs ( P01, P03, P05, P07, P11, P13, P15 and P17).
 *
 * ## Application Task
 * Sets the state of the output pins of one port and then reads the status of input pins of that port
 * and displays the results on the USB UART approximately 2 seconds.
 *
 * @note
 * In order for this example to work as intended it is necessary to connect the input and output pins 
 * eg. P00 and P01, P02 and P03 etc. Floating input pins will be shown as a high state.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "expand15.h"

static expand15_t expand15;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand15_cfg_t expand15_cfg;  /**< Click config object. */

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
    expand15_cfg_setup( &expand15_cfg );
    EXPAND15_MAP_MIKROBUS( expand15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand15_init( &expand15, &expand15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND15_ERROR == expand15_default_cfg ( &expand15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - \r\n" );
    
}

void application_task ( void ) 
{
    uint8_t output_pin_state;
    uint8_t input_pin_state;
    
    // Setting port0 output pin ( P00, P02, P04 and P06 ) to high
    output_pin_state = EXPAND15_PIN_00_MASK | EXPAND15_PIN_02_MASK | EXPAND15_PIN_04_MASK | EXPAND15_PIN_06_MASK;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_0, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port0
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_0, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS HIGH \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P01 : %c |", ( ( input_pin_state & EXPAND15_PIN_01_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P03 : %c |", ( ( input_pin_state & EXPAND15_PIN_03_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P05 : %c |", ( ( input_pin_state & EXPAND15_PIN_05_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P07 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_07_MASK ) ? 'H' : 'L' ) );
    Delay_ms ( 500 );
    
    // Setting port0 output pin ( P00, P02, P04 and P06 ) to low
    output_pin_state = EXPAND15_ALL_PINS_OFF;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_0, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port0
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_0, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS LOW \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P01 : %c |", ( ( input_pin_state & EXPAND15_PIN_01_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P03 : %c |", ( ( input_pin_state & EXPAND15_PIN_03_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P05 : %c |", ( ( input_pin_state & EXPAND15_PIN_05_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P07 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_07_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Setting port1 output pin ( P10, P12, P14 and P01 ) to high
    output_pin_state = EXPAND15_PIN_10_MASK | EXPAND15_PIN_12_MASK | EXPAND15_PIN_14_MASK | EXPAND15_PIN_16_MASK;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_1, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port1
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_1, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS HIGH \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P11 : %c |", ( ( input_pin_state & EXPAND15_PIN_11_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P13 : %c |", ( ( input_pin_state & EXPAND15_PIN_13_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P15 : %c |", ( ( input_pin_state & EXPAND15_PIN_15_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P17 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_17_MASK ) ? 'H' : 'L' ) );
    Delay_ms ( 500 );
    
    // Setting port1 output pin ( P10, P12, P14 and P16 ) to low
    output_pin_state = EXPAND15_ALL_PINS_OFF;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_1, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port1
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_1, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS LOW \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P11 : %c |", ( ( input_pin_state & EXPAND15_PIN_11_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P13 : %c |", ( ( input_pin_state & EXPAND15_PIN_13_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P15 : %c |", ( ( input_pin_state & EXPAND15_PIN_15_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P17 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_17_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - \r\n" );
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
