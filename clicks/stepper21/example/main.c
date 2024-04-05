/*!
 * @file main.c
 * @brief Stepper 21 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 21 click board by driving the 
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
#include "stepper21.h"

static stepper21_t stepper21;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper21_cfg_t stepper21_cfg;  /**< Click config object. */

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
    stepper21_cfg_setup( &stepper21_cfg );
    STEPPER21_MAP_MIKROBUS( stepper21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepper21_init( &stepper21, &stepper21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER21_ERROR == stepper21_default_cfg ( &stepper21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 full steps clockwise \r\n\n" );
    stepper21_set_step_mode ( &stepper21, STEPPER21_MODE_FULL_STEP );
    stepper21_set_direction ( &stepper21, STEPPER21_DIR_CW );
    stepper21_drive_motor ( &stepper21, 200, STEPPER21_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 400 quarter steps counter-clockwise \r\n\n" );
    stepper21_set_step_mode ( &stepper21, STEPPER21_MODE_QUARTER_STEP );
    stepper21_set_direction ( &stepper21, STEPPER21_DIR_CCW );
    stepper21_drive_motor ( &stepper21, 400, STEPPER21_SPEED_VERY_FAST );
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
