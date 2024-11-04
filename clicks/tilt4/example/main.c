/*!
 * @file main.c
 * @brief Tilt 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of Tilt 4 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and USB UART logger.
 *
 * ## Application Task
 * As soon as the tilt switch state changes, it displays a corresponding message on the USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "tilt4.h"

static tilt4_t tilt4;   /**< Tilt 4 Click driver object. */
static log_t logger;    /**< Logger object. */

static uint8_t tilt4_switch_state = TILT4_SWITCH_OFF;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tilt4_cfg_t tilt4_cfg;  /**< Click config object. */

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
    tilt4_cfg_setup( &tilt4_cfg );
    TILT4_MAP_MIKROBUS( tilt4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt4_init( &tilt4, &tilt4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t state = tilt4_read_int_state ( &tilt4 );
    if ( tilt4_switch_state != state )
    {
        tilt4_switch_state = state;
        
        if ( TILT4_SWITCH_ON == tilt4_switch_state )
        {
            log_printf( &logger, " Tilt switch ON!\r\n\n" );
            tilt4_set_led_state( &tilt4, TILT4_PIN_STATE_HIGH );
        }
        else
        {
            log_printf( &logger, " Tilt switch OFF!\r\n\n" );
            tilt4_set_led_state( &tilt4, TILT4_PIN_STATE_LOW );
        }
        Delay_ms ( 500 );
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
