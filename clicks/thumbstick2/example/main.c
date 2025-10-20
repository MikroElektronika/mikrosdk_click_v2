/*!
 * @file main.c
 * @brief Thumbstick 2 Click example
 *
 * # Description
 * This example demonstrates the use of the Thumbstick 2 Click board which 
 * features a 2-axis joystick with push button and vibration feedback. 
 * The joystick's angle and position are calculated based on raw ADC values, 
 * while the push button status controls the vibration motor through PWM output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click driver.
 *
 * ## Application Task
 * Continuously reads the raw ADC values from the joystick axes, calculates the 
 * joystick's position and angle, and logs the results. It also checks the state 
 * of the joystick push button and activates vibration feedback accordingly.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thumbstick2.h"

static thumbstick2_t thumbstick2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thumbstick2_cfg_t thumbstick2_cfg;  /**< Click config object. */

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
    thumbstick2_cfg_setup( &thumbstick2_cfg );
    THUMBSTICK2_MAP_MIKROBUS( thumbstick2_cfg, MIKROBUS_1 );
    if ( THUMBSTICK2_OK != thumbstick2_init( &thumbstick2, &thumbstick2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float angle = 0;
    uint16_t raw_x = 0;
    uint16_t raw_y = 0;
    uint8_t position = 0;
    if ( THUMBSTICK2_OK == thumbstick2_read_raw_adc ( &thumbstick2, &raw_x, &raw_y ) )
    {
        angle = thumbstick2_get_angle ( raw_x, raw_y );
        position = thumbstick2_get_position ( raw_x, raw_y );
        log_printf ( &logger, " RAW X: %u\r\n RAW Y: %u\r\n", raw_x, raw_y );
        log_printf ( &logger, " Joystick angle: %.1f degrees\r\n", angle );
        log_printf ( &logger, " Joystick position: " );
        switch ( position )
        {
            case THUMBSTICK2_POSITION_NEUTRAL:
            {
                log_printf ( &logger, "NEUTRAL" );
                break;
            }
            case THUMBSTICK2_POSITION_UP:
            {
                log_printf ( &logger, "UP" );
                break;
            }
            case THUMBSTICK2_POSITION_UPPER_LEFT:
            {
                log_printf ( &logger, "UPPER-LEFT" );
                break;
            }
            case THUMBSTICK2_POSITION_LEFT:
            {
                log_printf ( &logger, "LEFT" );
                break;
            }
            case THUMBSTICK2_POSITION_LOWER_LEFT:
            {
                log_printf ( &logger, "LOWER-LEFT" );
                break;
            }
            case THUMBSTICK2_POSITION_DOWN:
            {
                log_printf ( &logger, "DOWN" );
                break;
            }
            case THUMBSTICK2_POSITION_LOWER_RIGHT:
            {
                log_printf ( &logger, "LOWER-RIGHT" );
                break;
            }
            case THUMBSTICK2_POSITION_RIGHT:
            {
                log_printf ( &logger, "RIGHT" );
                break;
            }
            case THUMBSTICK2_POSITION_UPPER_RIGHT:
            {
                log_printf ( &logger, "UPPER-RIGHT" );
                break;
            }
            default:
            {
                log_printf ( &logger, "UNKNOWN" );
                break;
            }
        }
        log_printf ( &logger, "\r\n" );
        if ( thumbstick2_get_sw_pin ( &thumbstick2 ) )
        {
            log_printf ( &logger, " Button: Idle\r\n" );
            log_printf ( &logger, " Vibro: Idle\r\n\n" );
            thumbstick2_set_duty_cycle ( &thumbstick2, THUMBSTICK2_PWM_MIN_DUTY );
        }
        else
        {
            log_printf ( &logger, " Button: Active\r\n" );
            log_printf ( &logger, " Vibro: Active\r\n\n" );
            thumbstick2_set_duty_cycle ( &thumbstick2, THUMBSTICK2_PWM_MAX_DUTY );
        }
        Delay_ms ( 100 );
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
