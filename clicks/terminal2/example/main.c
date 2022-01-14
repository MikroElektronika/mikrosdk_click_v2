/*!
 * @file main.c
 * @brief Terminal 2 Click Example.
 *
 * # Description
 * This example demonstates the use of Terminal 2 click board by toggling all its pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and sets all pins to low logic state.
 *
 * ## Application Task
 * Toggles all pins from mikroBUS one by one in the span of 1 second between each pin toggle.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "terminal2.h"

static terminal2_t terminal2;   /**< Terminal 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    terminal2_cfg_t terminal2_cfg;  /**< Click config object. */

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
    terminal2_cfg_setup( &terminal2_cfg );
    TERMINAL2_MAP_MIKROBUS( terminal2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == terminal2_init( &terminal2, &terminal2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    terminal2_set_all_pins_low ( &terminal2 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    /**< Array of pins object addresses. */
    static digital_out_t *pin_addr[ 12 ] =
    {
        &terminal2.mosi,    // 0 MOSI
        &terminal2.miso,    // 1 MISO
        &terminal2.sck,     // 2 SCK
        &terminal2.cs,      // 3 CS
        &terminal2.rst,     // 4 RST
        &terminal2.an,      // 5 AN
        &terminal2.pwm,     // 6 PWM
        &terminal2.int_pin, // 7 INT
        &terminal2.tx_pin,  // 8 TX
        &terminal2.rx_pin,  // 9 RX
        &terminal2.scl,     // 10 SCL
        &terminal2.sda      // 11 SDA
    };
    static uint8_t pin_num = 0;
    log_printf( &logger, " Toggling pin: %u\r\n", ( uint16_t ) pin_num );
    terminal2_toggle_pin ( pin_addr[ pin_num ] );
    Delay_ms ( 1000 );
    terminal2_toggle_pin ( pin_addr[ pin_num ] );
    
    pin_num++;
    if ( 12 == pin_num )
    {
        pin_num = 0;
    }
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
