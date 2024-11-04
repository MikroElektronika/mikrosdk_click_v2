/*!
 * @file main.c
 * @brief Stepper 13 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 13 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockwise for 200 half
 * steps and 400 quarter steps with 2 seconds delay on driving mode change. All data is
 * being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper13.h"

static stepper13_t stepper13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper13_cfg_t stepper13_cfg;  /**< Click config object. */

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
    stepper13_cfg_setup( &stepper13_cfg );
    STEPPER13_MAP_MIKROBUS( stepper13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper13_init( &stepper13, &stepper13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER13_ERROR == stepper13_default_cfg ( &stepper13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_FULL_STEP );
    stepper13_drive_motor ( &stepper13, 200, STEPPER13_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CCW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_HALF_STEP );
    stepper13_drive_motor ( &stepper13, 200, STEPPER13_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper13_set_direction ( &stepper13, STEPPER13_DIR_CCW );
    stepper13_set_step_mode ( &stepper13, STEPPER13_MODE_QUARTER_STEP );
    stepper13_drive_motor ( &stepper13, 400, STEPPER13_SPEED_FAST );
    Delay_ms ( 1000 );
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
