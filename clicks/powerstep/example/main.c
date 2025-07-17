/*!
 * @file main.c
 * @brief Power Step Click Example.
 *
 * # Description
 * This example demonstrates the use of the Power Step Click board by driving the 
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
#include "powerstep.h"

static powerstep_t powerstep;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    powerstep_cfg_t powerstep_cfg;  /**< Click config object. */

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
    powerstep_cfg_setup( &powerstep_cfg );
    POWERSTEP_MAP_MIKROBUS( powerstep_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powerstep_init( &powerstep, &powerstep_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    powerstep_reset_device ( &powerstep );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 100 steps clockwise, speed: slow\r\n\n" );
    powerstep_set_direction ( &powerstep, POWERSTEP_DIR_CW );
    powerstep_drive_motor ( &powerstep, 100, POWERSTEP_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 300 steps clockwise, speed: medium\r\n\n" );
    powerstep_set_direction ( &powerstep, POWERSTEP_DIR_CW );
    powerstep_drive_motor ( &powerstep, 300, POWERSTEP_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 steps counter-clockwise, speed: fast\r\n\n" );
    powerstep_set_direction ( &powerstep, POWERSTEP_DIR_CCW );
    powerstep_drive_motor ( &powerstep, 400, POWERSTEP_SPEED_FAST );
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
