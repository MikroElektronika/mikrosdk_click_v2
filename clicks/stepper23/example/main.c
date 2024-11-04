/*!
 * @file main.c
 * @brief Stepper 23 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 23 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
 * steps and 400 quarter steps with a 1 second delay on driving mode change. All data is
 * being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper23.h"

static stepper23_t stepper23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper23_cfg_t stepper23_cfg;  /**< Click config object. */

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
    stepper23_cfg_setup( &stepper23_cfg );
    STEPPER23_MAP_MIKROBUS( stepper23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper23_init( &stepper23, &stepper23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER23_ERROR == stepper23_default_cfg ( &stepper23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper23_set_direction ( &stepper23, STEPPER23_DIR_CW );
    stepper23_set_step_mode ( &stepper23, STEPPER23_MODE_FULL_STEP );
    stepper23_drive_motor ( &stepper23, 200, STEPPER23_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper23_set_direction ( &stepper23, STEPPER23_DIR_CCW );
    stepper23_set_step_mode ( &stepper23, STEPPER23_MODE_HALF_STEP_TYPE_A );
    stepper23_drive_motor ( &stepper23, 200, STEPPER23_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper23_set_direction ( &stepper23, STEPPER23_DIR_CCW );
    stepper23_set_step_mode ( &stepper23, STEPPER23_MODE_QUARTER_STEP );
    stepper23_drive_motor ( &stepper23, 400, STEPPER23_SPEED_FAST );
    Delay_ms ( 1000 );
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
