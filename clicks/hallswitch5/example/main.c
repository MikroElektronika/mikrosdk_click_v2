/*!
 * @file main.c
 * @brief Hall Switch 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Hall Switch 5 Click board by initializing
 * the device and detecting changes in rotational direction and speed. It logs the 
 * direction (Clockwise or Counter-Clockwise) and speed in Hertz every second.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Hall Switch 5 Click driver.
 *
 * ## Application Task
 * Reads the direction and speed pins periodically, logs the rotational direction 
 * and calculates the speed in Hz, which is displayed every second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallswitch5.h"

static hallswitch5_t hallswitch5;   /**< Hall Switch 5 Click driver object. */
static log_t logger;                /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallswitch5_cfg_t hallswitch5_cfg;  /**< Click config object. */

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
    hallswitch5_cfg_setup( &hallswitch5_cfg );
    HALLSWITCH5_MAP_MIKROBUS( hallswitch5_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hallswitch5_init( &hallswitch5, &hallswitch5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t direction_old = 0xFF;
    static uint8_t speed_old = HALLSWITCH5_PIN_LOW;
    static uint8_t num_toggles = 0;
    static uint32_t period_ms = 0;
    uint8_t direction = hallswitch5_get_dir_pin ( &hallswitch5 );
    uint8_t speed = hallswitch5_get_speed_pin ( &hallswitch5 );
    if ( direction != direction_old )
    {
        direction_old = direction;
        log_printf ( &logger, " Direction: %s\r\n", 
                    ( char * ) ( ( direction == HALLSWITCH5_DIR_CW ) ? "CW" : "CCW" ) );
    }
    if ( speed_old != speed )
    {
        speed_old = speed;
        num_toggles++;
    }
    if ( ++period_ms > 1000 )
    {
        log_printf ( &logger, " Speed: %.1f Hz\r\n", ( float ) num_toggles / 2 );
        num_toggles = 0;
        period_ms = 0;
    }
    Delay_1ms ( );
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
