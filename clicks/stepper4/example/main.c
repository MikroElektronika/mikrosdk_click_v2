/*!
 * @file main.c
 * @brief Stepper 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Stepper 4 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 steps and then counter-clockiwse for 100 steps with
 * 2 seconds delay before changing the direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper4.h"

static stepper4_t stepper4;   /**< Stepper 4 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper4_cfg_t stepper4_cfg;  /**< Click config object. */

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
    stepper4_cfg_setup( &stepper4_cfg );
    STEPPER4_MAP_MIKROBUS( stepper4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper4_init( &stepper4, &stepper4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    stepper4_default_cfg ( &stepper4 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 steps clockwise \r\n\n" );
    stepper4_set_direction ( &stepper4, STEPPER4_DIR_CW );
    stepper4_drive_motor ( &stepper4, 200, STEPPER4_SPEED_FAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf ( &logger, " Move 100 steps counter-clockwise \r\n\n" );
    stepper4_set_direction ( &stepper4, STEPPER4_DIR_CCW );
    stepper4_drive_motor ( &stepper4, 100, STEPPER4_SPEED_FAST );
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
