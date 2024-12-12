/*!
 * @file main.c
 * @brief Rotary Switch Click example
 *
 * # Description
 * This example demonstrates the use of Rotary Switch Click board by reading
 * and displaying the switch position on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the switch position every 20ms and displays it on the USB UART on position change.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rotaryswitch.h"

static rotaryswitch_t rotaryswitch;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryswitch_cfg_t rotaryswitch_cfg;  /**< Click config object. */

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
    rotaryswitch_cfg_setup( &rotaryswitch_cfg );
    ROTARYSWITCH_MAP_MIKROBUS( rotaryswitch_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rotaryswitch_init( &rotaryswitch, &rotaryswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYSWITCH_ERROR == rotaryswitch_default_cfg ( &rotaryswitch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t old_position = 0xFF;
    uint8_t position = 0;
    if ( ( ROTARYSWITCH_OK == rotaryswitch_get_position ( &rotaryswitch, &position ) ) && 
         ( position != old_position ) )
    {
        Delay_ms ( 20 );
        // Double-check for debouncing
        if ( ( ROTARYSWITCH_OK == rotaryswitch_get_position ( &rotaryswitch, &position ) ) && 
             ( position != old_position ) )
        {
            old_position = position;
            log_printf ( &logger, " Switch position: %.1X\r\n", ( uint16_t ) position );
        }
    }
    Delay_ms ( 20 );
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
