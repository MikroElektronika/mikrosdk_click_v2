/*!
 * @file main.c
 * @brief XPRO-Adapter Click Example.
 *
 * # Description
 * This example demonstates the use of XPRO-Adapter Click board by toggling all its pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Toggles all pins from mikroBUS one by one in the span of 1 second between each pin toggle.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "xproadapter.h"

#ifndef MIKROBUS_POSITION_XPROADAPTER
    #define MIKROBUS_POSITION_XPROADAPTER MIKROBUS_1
#endif

static xproadapter_t xproadapter;   /**< XPRO-Adapter Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xproadapter_cfg_t xproadapter_cfg;  /**< Click config object. */

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
    xproadapter_cfg_setup( &xproadapter_cfg );
    XPROADAPTER_MAP_MIKROBUS( xproadapter_cfg, MIKROBUS_POSITION_XPROADAPTER );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == xproadapter_init( &xproadapter, &xproadapter_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    /**< Array of pins object addresses. */
    static digital_out_t *pin_addr[ 12 ] =
    {
        &xproadapter.mosi,    // 0 MOSI
        &xproadapter.miso,    // 1 MISO
        &xproadapter.sck,     // 2 SCK
        &xproadapter.cs,      // 3 CS
        &xproadapter.rst,     // 4 RST
        &xproadapter.an,      // 5 AN
        &xproadapter.pwm,     // 6 PWM
        &xproadapter.int_pin, // 7 INT
        &xproadapter.rx_pin,  // 8 RX
        &xproadapter.tx_pin,  // 9 TX
        &xproadapter.scl,     // 10 SCL
        &xproadapter.sda      // 11 SDA
    };
    static uint8_t pin_num = 0;
    log_printf( &logger, " Toggling pin: %u\r\n", ( uint16_t ) pin_num );
    xproadapter_toggle_pin ( pin_addr[ pin_num ] );
    Delay_ms ( 1000 );
    xproadapter_toggle_pin ( pin_addr[ pin_num ] );
    
    pin_num++;
    if ( 12 == pin_num )
    {
        pin_num = 0;
    }
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
