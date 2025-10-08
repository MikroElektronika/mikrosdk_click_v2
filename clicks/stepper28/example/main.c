/*!
 * @file main.c
 * @brief Stepper 28 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 28 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockwise for 200 half
 * steps and 400 quarter steps with a 1 second delay on driving mode change. All data is
 * being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper28.h"

static stepper28_t stepper28;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper28_cfg_t stepper28_cfg;  /**< Click config object. */

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
    stepper28_cfg_setup( &stepper28_cfg );
    STEPPER28_MAP_MIKROBUS( stepper28_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper28_init( &stepper28, &stepper28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER28_ERROR == stepper28_default_cfg ( &stepper28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper28_set_direction ( &stepper28, STEPPER28_DIR_CW );
    stepper28_set_step_mode ( &stepper28, STEPPER28_MODE_FULL_STEP );
    stepper28_drive_motor ( &stepper28, 200, STEPPER28_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper28_set_direction ( &stepper28, STEPPER28_DIR_CCW );
    stepper28_set_step_mode ( &stepper28, STEPPER28_MODE_HALF_STEP_TYPE_A );
    stepper28_drive_motor ( &stepper28, 200, STEPPER28_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n\n" );
    stepper28_set_direction ( &stepper28, STEPPER28_DIR_CCW );
    stepper28_set_step_mode ( &stepper28, STEPPER28_MODE_QUARTER_STEP );
    stepper28_drive_motor ( &stepper28, 400, STEPPER28_SPEED_FAST );
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
