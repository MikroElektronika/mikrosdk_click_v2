/*!
 * @file main.c
 * @brief Stepper 17 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 17 click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockiwse for 400 quarter
 * steps with 2 seconds delay before changing the direction. All data is being logged on
 * the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper17.h"

static stepper17_t stepper17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper17_cfg_t stepper17_cfg;  /**< Click config object. */

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
    stepper17_cfg_setup( &stepper17_cfg );
    STEPPER17_MAP_MIKROBUS( stepper17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper17_init( &stepper17, &stepper17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER17_ERROR == stepper17_default_cfg ( &stepper17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise \r\n\n" );
    stepper17_set_step_mode ( &stepper17, STEPPER17_MODE_FULL_STEP );
    stepper17_set_direction ( &stepper17, STEPPER17_DIR_CW );
    stepper17_drive_motor ( &stepper17, 200, STEPPER17_SPEED_FAST );
    Delay_ms ( 2000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper17_set_step_mode ( &stepper17, STEPPER17_MODE_QUARTER_STEP );
    stepper17_set_direction ( &stepper17, STEPPER17_DIR_CCW );
    stepper17_drive_motor ( &stepper17, 400, STEPPER17_SPEED_FAST );
    Delay_ms ( 2000 );
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
