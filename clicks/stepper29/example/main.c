/*!
 * @file main.c
 * @brief Stepper 29 Click example
 *
 * # Description
 * This example demonstrates the use of the Stepper 29 Click board by driving
 * the motor in both directions for a desired number of steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor clockwise for 200 full steps and then counter-clockwise
 * for 200 half steps and 400 quarter steps with a 1 second delay on driving
 * mode change. Also monitors the output current which is set by the on-board
 * potentiometer. All data is being logged on the USB UART where you can track
 * the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper29.h"

#ifndef MIKROBUS_POSITION_STEPPER29
    #define MIKROBUS_POSITION_STEPPER29 MIKROBUS_1
#endif

static stepper29_t stepper29;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper29_cfg_t stepper29_cfg;  /**< Click config object. */

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
    stepper29_cfg_setup( &stepper29_cfg );
    STEPPER29_MAP_MIKROBUS( stepper29_cfg, MIKROBUS_POSITION_STEPPER29 );
    if ( I2C_MASTER_ERROR == stepper29_init( &stepper29, &stepper29_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPPER29_ERROR == stepper29_default_cfg ( &stepper29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    log_printf ( &logger, " Move 200 full steps clockwise, speed: slow\r\n" );
    if ( STEPPER29_OK == stepper29_get_out_current ( &stepper29, &current ) ) 
    {
        log_printf( &logger, " Output current : %.1f A\r\n\n", current );
    }
    stepper29_set_direction ( &stepper29, STEPPER29_DIR_CW );
    stepper29_set_step_mode ( &stepper29, STEPPER29_MODE_FULL_STEP );
    stepper29_drive_motor ( &stepper29, 200, STEPPER29_SPEED_SLOW );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 200 half steps counter-clockwise, speed: medium\r\n" );
    if ( STEPPER29_OK == stepper29_get_out_current ( &stepper29, &current ) ) 
    {
        log_printf( &logger, " Output current : %.1f A\r\n\n", current );
    }
    stepper29_set_direction ( &stepper29, STEPPER29_DIR_CCW );
    stepper29_set_step_mode ( &stepper29, STEPPER29_MODE_HALF_STEP_TYPE_A );
    stepper29_drive_motor ( &stepper29, 200, STEPPER29_SPEED_MEDIUM );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Move 400 quarter steps counter-clockwise, speed: fast\r\n" );
    if ( STEPPER29_OK == stepper29_get_out_current ( &stepper29, &current ) ) 
    {
        log_printf( &logger, " Output current : %.1f A\r\n\n", current );
    }
    stepper29_set_direction ( &stepper29, STEPPER29_DIR_CCW );
    stepper29_set_step_mode ( &stepper29, STEPPER29_MODE_QUARTER_STEP );
    stepper29_drive_motor ( &stepper29, 400, STEPPER29_SPEED_FAST );
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
