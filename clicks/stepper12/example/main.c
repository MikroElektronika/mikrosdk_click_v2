/*!
 * @file main.c
 * @brief Stepper 12 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 12 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
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
#include "stepper12.h"

static stepper12_t stepper12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper12_cfg_t stepper12_cfg;  /**< Click config object. */

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
    stepper12_cfg_setup( &stepper12_cfg );
    STEPPER12_MAP_MIKROBUS( stepper12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper12_init( &stepper12, &stepper12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER12_ERROR == stepper12_default_cfg ( &stepper12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise \r\n\n" );
    stepper12_set_step_mode ( &stepper12, STEPPER12_MODE_FULL_STEP );
    stepper12_set_direction ( &stepper12, STEPPER12_DIR_CW );
    stepper12_drive_motor ( &stepper12, 200, STEPPER12_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper12_set_step_mode ( &stepper12, STEPPER12_MODE_QUARTER_STEP );
    stepper12_set_direction ( &stepper12, STEPPER12_DIR_CCW );
    stepper12_drive_motor ( &stepper12, 400, STEPPER12_SPEED_FAST );
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
