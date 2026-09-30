/*!
 * @file main.c
 * @brief Stepper 32 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Stepper 32 Click board by driving the 
 * motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 steps and then counter-clockwise for 200 steps
 * with 2 seconds delay on driving mode change. All data is being logged on the USB UART
 * where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper32.h"

#ifndef MIKROBUS_POSITION_STEPPER32
    #define MIKROBUS_POSITION_STEPPER32 MIKROBUS_1
#endif

static stepper32_t stepper32;   /**< Stepper 32 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper32_cfg_t stepper32_cfg;  /**< Click config object. */

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
    stepper32_cfg_setup( &stepper32_cfg );
    STEPPER32_MAP_MIKROBUS( stepper32_cfg, MIKROBUS_POSITION_STEPPER32 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == stepper32_init( &stepper32, &stepper32_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Move 200 steps clockwise, speed: medium\r\n\n" );
    stepper32_set_direction ( &stepper32, STEPPER32_DIR_CW );
    stepper32_drive_motor ( &stepper32, 200, STEPPER32_SPEED_MEDIUM );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 steps counter-clockwise, speed: fast\r\n\n" );
    stepper32_set_direction ( &stepper32, STEPPER32_DIR_CCW );
    stepper32_drive_motor ( &stepper32, 200, STEPPER32_SPEED_FAST );
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
