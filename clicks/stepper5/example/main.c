/*!
 * @file main.c
 * @brief Stepper 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Stepper 5 click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
 * steps and 400 quarter steps with 2 seconds delay on driving mode change. All data is
 * being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper5.h"

static stepper5_t stepper5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper5_cfg_t stepper5_cfg;  /**< Click config object. */

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
    stepper5_cfg_setup( &stepper5_cfg );
    STEPPER5_MAP_MIKROBUS( stepper5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == stepper5_init( &stepper5, &stepper5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER5_ERROR == stepper5_default_cfg ( &stepper5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper5_set_direction ( &stepper5, STEPPER5_DIR_CW );
    stepper5_set_step_res ( &stepper5, STEPPER5_MRES_FULLSTEP );
    stepper5_drive_motor ( &stepper5, 200, STEPPER5_SPEED_SLOW );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper5_set_direction ( &stepper5, STEPPER5_DIR_CCW );
    stepper5_set_step_res ( &stepper5, STEPPER5_MRES_2 );
    stepper5_drive_motor ( &stepper5, 200, STEPPER5_SPEED_MEDIUM );
    Delay_ms ( 2000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper5_set_direction ( &stepper5, STEPPER5_DIR_CCW );
    stepper5_set_step_res ( &stepper5, STEPPER5_MRES_4 );
    stepper5_drive_motor ( &stepper5, 400, STEPPER5_SPEED_FAST );
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
