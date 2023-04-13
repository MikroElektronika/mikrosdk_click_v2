/*!
 * @file main.c
 * @brief Cap Touch 6 Click Example.
 *
 * # Description
 * This example demonstrates the use of Cap Touch 6 click board by reading and displaying
 * the touch and proximity events.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the touch and proximity event pins state and displays them on the USB UART on changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "captouch6.h"

static captouch6_t captouch6;   /**< Cap Touch 6 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    captouch6_cfg_t captouch6_cfg;  /**< Click config object. */

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
    captouch6_cfg_setup( &captouch6_cfg );
    CAPTOUCH6_MAP_MIKROBUS( captouch6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == captouch6_init( &captouch6, &captouch6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t old_touch_state = 0, old_prox_state = 0;
    uint8_t touch_state = captouch6_get_tout_pin ( &captouch6 );
    uint8_t prox_state = captouch6_get_pout_pin ( &captouch6 );
    if ( ( old_touch_state != touch_state ) || ( old_prox_state != prox_state ) )
    {
        log_printf( &logger, " Touch: %s\r\n", ( char * ) ( !touch_state ? "detected" : "idle" ) );
        log_printf( &logger, " Proximity: %s\r\n\n", ( char * ) ( !prox_state ? "detected" : "idle" ) );
        old_touch_state = touch_state;
        old_prox_state = prox_state;
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
