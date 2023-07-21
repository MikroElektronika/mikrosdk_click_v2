/*!
 * @file main.c
 * @brief IR Gesture 3 Click example
 *
 * # Description
 * This example demonstrates the use of IR Gesture 3 click board by processing
 * the incoming gestures and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and processes all the incoming gestures and displays them on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irgesture3.h"

static irgesture3_t irgesture3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgesture3_cfg_t irgesture3_cfg;  /**< Click config object. */

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
    irgesture3_cfg_setup( &irgesture3_cfg );
    IRGESTURE3_MAP_MIKROBUS( irgesture3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgesture3_init( &irgesture3, &irgesture3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGESTURE3_ERROR == irgesture3_default_cfg ( &irgesture3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t gesture = 0;
    if ( IRGESTURE3_OK == irgesture3_get_gesture ( &irgesture3, &gesture ) )
    {
        log_printf( &logger, "\r\n Gesture: " );
        switch ( gesture )
        {
            case IRGESTURE3_GESTURE_CLICK:
            {
                log_printf( &logger, "CLICK\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_UP:
            {
                log_printf( &logger, "SWIPE UP\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_DOWN:
            {
                log_printf( &logger, "SWIPE DOWN\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_LEFT:
            {
                log_printf( &logger, "SWIPE LEFT\r\n" );
                break;
            }
            case IRGESTURE3_GESTURE_SWIPE_RIGHT:
            {
                log_printf( &logger, "SWIPE RIGHT\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, "UNKNOWN\r\n" );
                break;
            }
        }
    }
    else
    {
        log_printf( &logger, "\r\n No gesture detected!\r\n" );
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
