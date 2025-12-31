/*!
 * @file main.c
 * @brief Servo 3 Click example
 *
 * # Description
 * This example demonstrates the use of the Servo 3 Click board for controlling the angle of servo motors. 
 * The board is capable of driving multiple servos, and the example illustrates how to change the angle 
 * of all connected servos simultaneously within a defined range.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger module and configures the Servo 3 Click board. The PWM communication is 
 * established, and the device is prepared for controlling the servos.
 *
 * ## Application Task
 * Gradually changes the angle of all connected servo motors from a minimum to a maximum value, and 
 * then back to the minimum, creating a sweeping motion. The current angle is logged during each update.
 *
 * @note
 * Ensure that the servo motors are properly connected to the Servo 3 Click board and are compatible 
 * with the specified angle range such as the SG90 Micro Servo motors.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "servo3.h"

static servo3_t servo3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    servo3_cfg_t servo3_cfg;  /**< Click config object. */

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
    servo3_cfg_setup( &servo3_cfg );
    SERVO3_MAP_MIKROBUS( servo3_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == servo3_init( &servo3, &servo3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t angle = SERVO3_ANGLE_MIN;
    static int8_t step = 1;
    log_printf( &logger, "All channels angle: %u\r\n\n", ( uint16_t ) angle );
    servo3_set_angle ( &servo3, SERVO3_CHANNEL_ALL, angle );
    servo3_update_output ( &servo3 );
    angle += step;
    if ( angle > SERVO3_ANGLE_MAX )
    {
        step = -step;
        angle += step;
    }
    else if ( angle < SERVO3_ANGLE_MIN )
    {
        step = -step;
        angle += step;
    }
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
