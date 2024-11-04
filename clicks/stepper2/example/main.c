/*!
 * @file main.c
 * @brief Stepper 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Stepper 2 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 64 steps and then counter-clockiwse for 32 steps
 * with 2 seconds delay before changing the direction. All data is being logged on
 * the USB UART where you can track the program flow.
 *
 * @note
 * Step Motor 5v [MIKROE-1530] is a compatible stepper motor for this Click board:
 * https://www.mikroe.com/step-motor-5v
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper2.h"

static stepper2_t stepper2;   /**< Stepper 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper2_cfg_t stepper2_cfg;  /**< Click config object. */

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
    stepper2_cfg_setup( &stepper2_cfg );
    STEPPER2_MAP_MIKROBUS( stepper2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper2_init( &stepper2, &stepper2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepper2_default_cfg ( &stepper2 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 64 steps clockwise\r\n\n" );
    stepper2_set_direction ( &stepper2, STEPPER2_DIR_CW );
    stepper2_drive_motor ( &stepper2, 64, STEPPER2_SPEED_VERY_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 32 steps counter-clockwise\r\n\n" );
    stepper2_set_direction ( &stepper2, STEPPER2_DIR_CCW );
    stepper2_drive_motor ( &stepper2, 32, STEPPER2_SPEED_FAST );
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
