/*!
 * @file main.c
 * @brief CapSense2 Click example
 *
 * # Description
 * This example demonstrates the use of CapSense 2 click board by reading 
 * and displaying the sensor's events.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration
 * which resets the click board and links the desired LEDs to buttons and swipe sensors.
 *
 * ## Application Task
 * Waits for an event interrupt and displays the event on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "capsense2.h"

static capsense2_t capsense2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    capsense2_cfg_t capsense2_cfg;  /**< Click config object. */

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
    capsense2_cfg_setup( &capsense2_cfg );
    CAPSENSE2_MAP_MIKROBUS( capsense2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == capsense2_init( &capsense2, &capsense2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CAPSENSE2_ERROR == capsense2_default_cfg ( &capsense2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( capsense2_get_alert_pin ( &capsense2 ) )
    {
        uint8_t button_status = 0;
        if ( CAPSENSE2_OK == capsense2_read_register ( &capsense2, CAPSENSE2_REG_BUTTON_STATUS_1, &button_status ) )
        {
            static uint8_t button_press_state = 0;
            static uint8_t swipe_state = 0;
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_UP_SLIDER )
            {
                if ( CAPSENSE2_BUTTON_STATUS_1_UP_SLIDER != swipe_state )
                {
                    log_printf ( &logger, " Swipe UP \r\n\n" );
                    swipe_state = CAPSENSE2_BUTTON_STATUS_1_UP_SLIDER;
                }
            }
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_DOWN_SLIDER )
            {
                if ( CAPSENSE2_BUTTON_STATUS_1_DOWN_SLIDER != swipe_state )
                {
                    log_printf ( &logger, " Swipe DOWN \r\n\n" );
                    swipe_state = CAPSENSE2_BUTTON_STATUS_1_DOWN_SLIDER;
                }
            }
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 )
            {
                if ( !( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 ) )
                {
                    log_printf ( &logger, " Button 1 pressed \r\n\n" );
                    button_press_state |= CAPSENSE2_BUTTON_STATUS_1_BUTTON_1;
                }
            }
            if ( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 )
            {
                if ( !( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 ) )
                {
                    log_printf ( &logger, " Button 2 pressed \r\n\n" );
                    button_press_state |= CAPSENSE2_BUTTON_STATUS_1_BUTTON_2;
                }
            }
            capsense2_clear_interrupt ( &capsense2 );
            
            // check if buttons are released
            if ( CAPSENSE2_OK == capsense2_read_register ( &capsense2, CAPSENSE2_REG_BUTTON_STATUS_1, &button_status ) )
            {
                if ( ( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 ) && 
                    !( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_1 ) )
                {
                    log_printf ( &logger, " Button 1 released \r\n\n" );
                    button_press_state &= ~CAPSENSE2_BUTTON_STATUS_1_BUTTON_1;
                }
                if ( ( button_press_state & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 ) && 
                    !( button_status & CAPSENSE2_BUTTON_STATUS_1_BUTTON_2 ) )
                {
                    log_printf ( &logger, " Button 2 released \r\n\n" );
                    button_press_state &= ~CAPSENSE2_BUTTON_STATUS_1_BUTTON_2;
                }
            }
            
            // check if swipe event is finished and display the slider position
            uint8_t slider = 0;
            if ( CAPSENSE2_OK == capsense2_read_register ( &capsense2, CAPSENSE2_REG_SLIDER_POSITION_DATA, &slider ) )
            {
                if ( slider )
                {
                    log_printf ( &logger, " Slider position: %u \r\n\n", ( uint16_t ) slider );
                }
                else
                {
                    swipe_state = 0;
                }
            }
        }
        capsense2_clear_interrupt ( &capsense2 );
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
