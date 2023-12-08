/*!
 * @file main.c
 * @brief Stepper 20 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 20 click board by driving the 
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
#include "stepper20.h"

static stepper20_t stepper20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper20_cfg_t stepper20_cfg;  /**< Click config object. */

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
    stepper20_cfg_setup( &stepper20_cfg );
    STEPPER20_MAP_MIKROBUS( stepper20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper20_init( &stepper20, &stepper20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER20_ERROR == stepper20_default_cfg ( &stepper20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise \r\n\n" );
    stepper20_set_step_mode ( &stepper20, STEPPER20_MODE_FULL_STEP );
    stepper20_set_direction ( &stepper20, STEPPER20_DIR_CW );
    stepper20_drive_motor ( &stepper20, 200, STEPPER20_SPEED_FAST );
    Delay_ms ( 2000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper20_set_step_mode ( &stepper20, STEPPER20_MODE_QUARTER_STEP );
    stepper20_set_direction ( &stepper20, STEPPER20_DIR_CCW );
    stepper20_drive_motor ( &stepper20, 400, STEPPER20_SPEED_VERY_FAST );
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
