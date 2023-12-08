/*!
 * @file main.c
 * @brief Joystick 3 Click example
 *
 * # Description
 * This example demonstrates the use of the joystick 3 click board by reading
 * and displaying the raw ADC for X and Y axis, as well as the joystick angle and position
 * calculated from those ADC readings.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the raw ADC measurements for X and Y axis, and calculates the joystick angle and position
 * from those readings. The results will be displayed on the USB UART approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "joystick3.h"

static joystick3_t joystick3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    joystick3_cfg_t joystick3_cfg;  /**< Click config object. */

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
    joystick3_cfg_setup( &joystick3_cfg );
    JOYSTICK3_MAP_MIKROBUS( joystick3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == joystick3_init( &joystick3, &joystick3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t raw_x, raw_y;
    if ( JOYSTICK3_OK == joystick3_read_raw_adc ( &joystick3, &raw_x, &raw_y ) )
    {
        log_printf ( &logger, " RAW X: %u\r\n RAW Y: %u\r\n", raw_x, raw_y );
        log_printf ( &logger, " Joystick angle: %.1f degrees\r\n", joystick3_get_angle ( raw_x, raw_y ) );
        log_printf ( &logger, " Joystick position: " );
        switch ( joystick3_get_position ( raw_x, raw_y ) )
        {
            case JOYSTICK3_POSITION_NEUTRAL:
            {
                log_printf ( &logger, "NEUTRAL" );
                break;
            }
            case JOYSTICK3_POSITION_UP:
            {
                log_printf ( &logger, "UP" );
                break;
            }
            case JOYSTICK3_POSITION_UPPER_RIGHT:
            {
                log_printf ( &logger, "UPPER-RIGHT" );
                break;
            }
            case JOYSTICK3_POSITION_RIGHT:
            {
                log_printf ( &logger, "RIGHT" );
                break;
            }
            case JOYSTICK3_POSITION_LOWER_RIGHT:
            {
                log_printf ( &logger, "LOWER-RIGHT" );
                break;
            }
            case JOYSTICK3_POSITION_DOWN:
            {
                log_printf ( &logger, "DOWN" );
                break;
            }
            case JOYSTICK3_POSITION_LOWER_LEFT:
            {
                log_printf ( &logger, "LOWER-LEFT" );
                break;
            }
            case JOYSTICK3_POSITION_LEFT:
            {
                log_printf ( &logger, "LEFT" );
                break;
            }
            case JOYSTICK3_POSITION_UPPER_LEFT:
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
        Delay_ms ( 100 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
