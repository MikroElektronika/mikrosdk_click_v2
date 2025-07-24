/*!
 * @file main.c
 * @brief Stepper 27 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Stepper 27 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the device.
 *
 * ## Application Task
 * Drives the motor clockwise for 100 slow steps and 300 medium speed steps and
 * then counter-clockwise for 400 fast steps with a 1 second delay on driving mode change. 
 * All data is being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper27.h"

static stepper27_t stepper27;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper27_cfg_t stepper27_cfg;  /**< Click config object. */

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
    stepper27_cfg_setup( &stepper27_cfg );
    STEPPER27_MAP_MIKROBUS( stepper27_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper27_init( &stepper27, &stepper27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    stepper27_reset_device ( &stepper27 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 100 steps clockwise, speed: slow\r\n\n" );
    stepper27_set_direction ( &stepper27, STEPPER27_DIR_CW );
    stepper27_drive_motor ( &stepper27, 100, STEPPER27_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 300 steps clockwise, speed: medium\r\n\n" );
    stepper27_set_direction ( &stepper27, STEPPER27_DIR_CW );
    stepper27_drive_motor ( &stepper27, 300, STEPPER27_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 steps counter-clockwise, speed: fast\r\n\n" );
    stepper27_set_direction ( &stepper27, STEPPER27_DIR_CCW );
    stepper27_drive_motor ( &stepper27, 400, STEPPER27_SPEED_FAST );
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
