/*!
 * @file main.c
 * @brief PROTO Click Example.
 *
 * # Description
 * This example demonstates the use of PROTO Click board by toggling all its pins.
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
#include "proto.h"

#ifndef MIKROBUS_POSITION_PROTO
    #define MIKROBUS_POSITION_PROTO MIKROBUS_1
#endif

static proto_t proto;   /**< PROTO Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proto_cfg_t proto_cfg;  /**< Click config object. */

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
    proto_cfg_setup( &proto_cfg );
    PROTO_MAP_MIKROBUS( proto_cfg, MIKROBUS_POSITION_PROTO );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == proto_init( &proto, &proto_cfg ) ) 
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
        &proto.mosi,    // 0 MOSI
        &proto.miso,    // 1 MISO
        &proto.sck,     // 2 SCK
        &proto.cs,      // 3 CS
        &proto.rst,     // 4 RST
        &proto.an,      // 5 AN
        &proto.pwm,     // 6 PWM
        &proto.int_pin, // 7 INT
        &proto.rx_pin,  // 8 RX
        &proto.tx_pin,  // 9 TX
        &proto.scl,     // 10 SCL
        &proto.sda      // 11 SDA
    };
    static uint8_t pin_num = 0;
    log_printf( &logger, " Toggling pin: %u\r\n", ( uint16_t ) pin_num );
    proto_toggle_pin ( pin_addr[ pin_num ] );
    Delay_ms ( 1000 );
    proto_toggle_pin ( pin_addr[ pin_num ] );
    
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
