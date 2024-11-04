/*!
 * @file main.c
 * @brief LDCTouch Click example
 *
 * # Description
 * This example demonstrates the use of LDC Touch Click board by configuring 
 * the buttons to trigger on finger press, and reading the buttons state in the loop.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the buttons to be active on finger press.
 *
 * ## Application Task
 * Waits for the button active event interrupt and then reads and displays the buttons
 * state and their raw data on the USB UART every 200ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ldctouch.h"

static ldctouch_t ldctouch;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldctouch_cfg_t ldctouch_cfg;  /**< Click config object. */

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
    ldctouch_cfg_setup( &ldctouch_cfg );
    LDCTOUCH_MAP_MIKROBUS( ldctouch_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ldctouch_init( &ldctouch, &ldctouch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LDCTOUCH_ERROR == ldctouch_default_cfg ( &ldctouch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static bool button_active = true;
    if ( !ldctouch_get_int_pin ( &ldctouch ) )
    {
        ldctouch_data_t button_data;
        if ( LDCTOUCH_OK == ldctouch_get_data ( &ldctouch, &button_data ) )
        {
            button_active = true;
            log_printf ( &logger, " Active button: -" ); 
            for ( uint8_t cnt = 0; cnt < 4; cnt++ )
            {
                if ( button_data.out_state & ( 1 << cnt ) )
                {
                    log_printf ( &logger, " %u - ", ( uint16_t ) cnt ); 
                }
            }
            log_printf ( &logger, "\r\n Button 0 raw data: %d\r\n", button_data.ch0_raw_button );
            log_printf ( &logger, " Button 1 raw data: %d\r\n", button_data.ch1_raw_button );
            log_printf ( &logger, " Button 2 raw data: %d\r\n", button_data.ch2_raw_button );
            log_printf ( &logger, " Button 3 raw data: %d\r\n\n", button_data.ch3_raw_button );
            Delay_ms ( 200 );
        }
    }
    else
    {
        if ( button_active )
        {
            button_active = false;
            log_printf ( &logger, " Active button: - none -\r\n" ); 
        }
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
