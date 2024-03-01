/*!
 * @file main.c
 * @brief Stepper 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Stepper 3 click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Drives the motor clockwise for 64 full steps and then counter-clockiwse for 128 half
 * steps with 2 seconds delay before changing the direction. All data is being logged on
 * the USB UART where you can track the program flow.
 *
 * @note
 * Step Motor 5v [MIKROE-1530] is a fully compatible stepper motor for this click board:
 * https://www.mikroe.com/step-motor-5v
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper3.h"

static stepper3_t stepper3;   /**< Stepper 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper3_cfg_t stepper3_cfg;  /**< Click config object. */

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
    stepper3_cfg_setup( &stepper3_cfg );
    STEPPER3_MAP_MIKROBUS( stepper3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper3_init( &stepper3, &stepper3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 64 full steps clockwise \r\n\n" );
    stepper3_set_step_mode ( &stepper3, STEPPER3_MODE_FULL_STEP );
    stepper3_set_direction ( &stepper3, STEPPER3_DIR_CW );
    stepper3_drive_motor ( &stepper3, 64, STEPPER3_SPEED_FAST );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 128 half steps counter-clockwise \r\n\n" );
    stepper3_set_step_mode ( &stepper3, STEPPER3_MODE_HALF_STEP );
    stepper3_set_direction ( &stepper3, STEPPER3_DIR_CCW );
    stepper3_drive_motor ( &stepper3, 128, STEPPER3_SPEED_VERY_FAST );
    Delay_ms ( 2000 );
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
