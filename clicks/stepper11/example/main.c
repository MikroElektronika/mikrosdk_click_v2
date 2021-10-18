/*!
 * @file main.c
 * @brief Stepper11 Click example
 *
 * # Description
 * This example showcases the device's ability to control the motor.
 * It initializes the device for control and moves the motor in two 
 * directions in a variety of resolutions for 360 degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules(I2C, UART) and additional pins
 * for control of device. Then sets default configuration that enables
 * device for motor control.
 *
 * ## Application Task
 * Firstly it rotates motor in CW direction for 360 degrees in FULL step 
 * resolution. Then changes direction in CCW and rotates backwards 360 degrees
 * in 2 different step resolutions (Quarter and 1/16) in 180 degrees each.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper11.h"

static stepper11_t stepper11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper11_cfg_t stepper11_cfg;  /**< Click config object. */

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
    stepper11_cfg_setup( &stepper11_cfg );
    STEPPER11_MAP_MIKROBUS( stepper11_cfg, MIKROBUS_1 );
    err_t init_flag = stepper11_init( &stepper11, &stepper11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    stepper11_default_cfg ( &stepper11 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_FULL );
    stepper11_set_direction( &stepper11, 1 );
    log_info( &logger, " Rotate motor CW for 360 degrees in full step" );
    stepper11_move_motor_angle( &stepper11, 360, STEPPER11_SPEED_FAST );
    Delay_ms( 1000 );
    stepper11_set_direction( &stepper11, 0 );
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_QUARTER );
    log_info( &logger, " Rotate motor CCW for 180 degrees in half step" );
    stepper11_move_motor_angle( &stepper11, 180, STEPPER11_SPEED_FAST );
    Delay_ms( 1000 );
    stepper11_set_step_resolution( &stepper11, STEPPER11_RESOLUTION_1div16 );
    log_info( &logger, " Rotate motor CCW for 180 degrees in 1/8 step" );
    stepper11_move_motor_angle( &stepper11, 180, STEPPER11_SPEED_FAST );
    Delay_ms( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
