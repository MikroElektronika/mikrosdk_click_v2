/*!
 * @file main.c
 * @brief 1-Wire Switch Click Example.
 *
 * # Description
 * This library contains API for 1-Wire Switch Click driver. 
 * The library initializes and defines the 1-Wire bus drivers to 
 * write and read data for state programmable I/O, 
 * as well as the default configuration.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs default configuration and sets 
 * the PIO A to OFF and PIO B to ON state.
 *
 * ## Application Task
 * This example demonstrates the use of the 1-Wire Switch Click board by changing the PIO A state, 
 * which is controlling the LED, every time the state of PIO B changes. 
 * Change on the PIO B happens when the button is pushed.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "c1wireswitch.h"

static c1wireswitch_t c1wireswitch;
static log_t logger;
static uint8_t state = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1wireswitch_cfg_t c1wireswitch_cfg;  /**< Click config object. */

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
    c1wireswitch_cfg_setup( &c1wireswitch_cfg );
    C1WIRESWITCH_MAP_MIKROBUS( c1wireswitch_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == c1wireswitch_init( &c1wireswitch, &c1wireswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1WIRESWITCH_ERROR == c1wireswitch_default_cfg ( &c1wireswitch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_OFF, C1WIRESWITCH_PIOB_ON );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t pio_a = 0;
    uint8_t pio_b = 0;
    
    c1wireswitch_get_pio_state( &c1wireswitch, &pio_a, &pio_b );
    
    if ( pio_b == C1WIRESWITCH_PIOB_OFF )
    {
        if ( state == 0 )
        {
            c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_ON, C1WIRESWITCH_PIOB_ON );
            log_printf( &logger, " Button is pressed, LED is ON. \r\n " );
            state = 1;
        }
        else
        {
            c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_OFF, C1WIRESWITCH_PIOB_ON );
            log_printf( &logger, " Button is pressed, LED is OFF. \r\n " );
            state = 0;
        }
        Delay_ms( 100 );
    }
    Delay_ms( 100 );
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
