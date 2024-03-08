/*!
 * @file main.c
 * @brief Stepper 14 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 14 click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockwise for 400 half
 * steps with a 2 seconds delay on driving mode change. All data is being logged on the
 * USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper14.h"

static stepper14_t stepper14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper14_cfg_t stepper14_cfg;  /**< Click config object. */

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
    stepper14_cfg_setup( &stepper14_cfg );
    STEPPER14_MAP_MIKROBUS( stepper14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper14_init( &stepper14, &stepper14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER14_ERROR == stepper14_default_cfg ( &stepper14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: medium\r\n\n" );
    stepper14_set_direction ( &stepper14, STEPPER14_DIR_CW );
    stepper14_set_step_mode ( &stepper14, STEPPER14_MODE_FULL_STEP );
    stepper14_drive_motor ( &stepper14, 200, STEPPER14_SPEED_MEDIUM );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 400 half steps counter-clockwise, speed: fast\r\n\n" );
    stepper14_set_direction ( &stepper14, STEPPER14_DIR_CCW );
    stepper14_set_step_mode ( &stepper14, STEPPER14_MODE_HALF_STEP );
    stepper14_drive_motor ( &stepper14, 400, STEPPER14_SPEED_FAST );
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
