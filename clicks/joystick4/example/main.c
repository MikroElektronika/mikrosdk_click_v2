/*!
 * @file main.c
 * @brief Joystick 4 Click example
 *
 * # Description
 * This example demonstrates the use of the Joystick 4 Click board by reading
 * and displaying the joystick position.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for the input change interrupt, reads the input pins mask, extracts
 * the joystick position from those readings, and displays it on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "joystick4.h"

static joystick4_t joystick4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    joystick4_cfg_t joystick4_cfg;  /**< Click config object. */

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
    joystick4_cfg_setup( &joystick4_cfg );
    JOYSTICK4_MAP_MIKROBUS( joystick4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == joystick4_init( &joystick4, &joystick4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( JOYSTICK4_ERROR == joystick4_default_cfg ( &joystick4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    if ( JOYSTICK4_PIN_STATE_HIGH == joystick4_get_int_pin ( &joystick4 ) )
    {
        log_printf ( &logger, " Joystick position: IDLE\r\n\n" );
    }
}

void application_task ( void ) 
{
    uint8_t pin_mask = 0;
    if ( JOYSTICK4_PIN_STATE_LOW == joystick4_get_int_pin ( &joystick4 ) )
    {
        if ( JOYSTICK4_OK == joystick4_get_pins ( &joystick4, &pin_mask ) )
        {
            log_printf ( &logger, " Joystick position: " );
            switch ( joystick4_get_position ( pin_mask ) )
            {
                case JOYSTICK4_POSITION_IDLE:
                {
                    log_printf ( &logger, "IDLE" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER:
                {
                    log_printf ( &logger, "CENTER" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_UP:
                {
                    log_printf ( &logger, "CENTER-UP" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_RIGHT:
                {
                    log_printf ( &logger, "CENTER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_DOWN:
                {
                    log_printf ( &logger, "CENTER-DOWN" );
                    break;
                }
                case JOYSTICK4_POSITION_CENTER_LEFT:
                {
                    log_printf ( &logger, "CENTER-LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_UP:
                {
                    log_printf ( &logger, "UP" );
                    break;
                }
                case JOYSTICK4_POSITION_UPPER_RIGHT:
                {
                    log_printf ( &logger, "UPPER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_RIGHT:
                {
                    log_printf ( &logger, "RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_LOWER_RIGHT:
                {
                    log_printf ( &logger, "LOWER-RIGHT" );
                    break;
                }
                case JOYSTICK4_POSITION_DOWN:
                {
                    log_printf ( &logger, "DOWN" );
                    break;
                }
                case JOYSTICK4_POSITION_LOWER_LEFT:
                {
                    log_printf ( &logger, "LOWER-LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_LEFT:
                {
                    log_printf ( &logger, "LEFT" );
                    break;
                }
                case JOYSTICK4_POSITION_UPPER_LEFT:
                {
                    log_printf ( &logger, "UPPER-LEFT" );
                    break;
                }
                default:
                {
                    log_printf ( &logger, "UNKNOWN" );
                    break;
                }
            }
            log_printf ( &logger, "\r\n\n" );
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
