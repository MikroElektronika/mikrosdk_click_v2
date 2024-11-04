/*!
 * @file main.c
 * @brief Stepper 7 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 7 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockiwse for 200 half
 * steps and 800 1/8th steps with 2 seconds delay on driving mode change. All data is
 * being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper7.h"

static stepper7_t stepper7;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper7_cfg_t stepper7_cfg;  /**< Click config object. */

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
    stepper7_cfg_setup( &stepper7_cfg );
    STEPPER7_MAP_MIKROBUS( stepper7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == stepper7_init( &stepper7, &stepper7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER7_ERROR == stepper7_default_cfg ( &stepper7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n\n" );
    stepper7_set_direction ( &stepper7, STEPPER7_DIR_CW );
    stepper7_set_step_mode ( &stepper7, STEPPER7_MODE_FULL_STEP );
    stepper7_drive_motor ( &stepper7, 200, STEPPER7_SPEED_SLOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n\n" );
    stepper7_set_direction ( &stepper7, STEPPER7_DIR_CCW );
    stepper7_set_step_mode ( &stepper7, STEPPER7_MODE_HALF_STEP );
    stepper7_drive_motor ( &stepper7, 200, STEPPER7_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 800 1/8th steps counter-clockwise, speed: fast\r\n\n" );
    stepper7_set_direction ( &stepper7, STEPPER7_DIR_CCW );
    stepper7_set_step_mode ( &stepper7, STEPPER7_MODE_1_OVER_8_STEP );
    stepper7_drive_motor ( &stepper7, 800, STEPPER7_SPEED_FAST );
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
