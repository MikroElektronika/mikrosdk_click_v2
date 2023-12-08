/*!
 * @file main.c
 * @brief Stepper 9 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 9 click board by driving the 
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
#include "stepper9.h"

static stepper9_t stepper9;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper9_cfg_t stepper9_cfg;  /**< Click config object. */

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
    stepper9_cfg_setup( &stepper9_cfg );
    STEPPER9_MAP_MIKROBUS( stepper9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper9_init( &stepper9, &stepper9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER9_ERROR == stepper9_default_cfg ( &stepper9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise \r\n\n" );
    stepper9_set_step_mode ( &stepper9, STEPPER9_MODE_FULL_STEP );
    stepper9_set_direction ( &stepper9, STEPPER9_DIR_CW );
    stepper9_drive_motor ( &stepper9, 200, STEPPER9_SPEED_FAST );
    Delay_ms ( 2000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper9_set_step_mode ( &stepper9, STEPPER9_MODE_QUARTER_STEP );
    stepper9_set_direction ( &stepper9, STEPPER9_DIR_CCW );
    stepper9_drive_motor ( &stepper9, 400, STEPPER9_SPEED_VERY_FAST );
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
