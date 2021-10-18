/*!
 * @file main.c
 * @brief Stepper15 Click example
 *
 * # Description
 * This library contains API for the Stepper 15 Click driver.
 * The library contains drivers for work control of the Stepper Motor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C and SPI driver and set default configuration,
 * enable the device and enable outputs mode.
 *
 * ## Application Task
 * The application task represents an example that demonstrates 
 * the use of the Stepper 15 Click board™ 
 * with which the user can sequentially move the motor. 
 * The first part of the sequence executes the clockwise/counterclockwise motor movement
 * for an angle of 90-degrees with a step speed of 85/100%, 
 * all the way to the last sequence of the same movement routine of 360-degree angle
 * with a step speed of 85/100%. 
 * Results are sent to the USART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper15.h"

static stepper15_t stepper15;
static log_t logger;
static uint8_t step_speed = 100;
static uint16_t step_360 = 200;

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    stepper15_cfg_t stepper15_cfg;  /**< Click config object. */

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

    stepper15_cfg_setup( &stepper15_cfg );
    STEPPER15_MAP_MIKROBUS( stepper15_cfg, MIKROBUS_1 );
    err_t init_flag  = stepper15_init( &stepper15, &stepper15_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    stepper15_default_cfg ( &stepper15 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------------\r\n" );
    
    stepper15_set_work_mode( &stepper15, STEPPER15_WORK_MODE_ENABLE_DEVICE );
    Delay_ms( 100 );
    stepper15_set_output_mode( &stepper15, STEPPER15_OUTPUT_MODE_OUTPUTS_ENABLE );
    Delay_ms( 100 );
    
    if ( stepper15_get_fault_condition( &stepper15 ) == STEPPER15_FAULT_CONDITION ) {
        log_printf( &logger, "         Fault condition         \r\n" );   
    } else {
        log_printf( &logger, "        Correct condition        \r\n" );
    }
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "      Stop the stepper motor     \r\n" );
    stepper15_motor_stop( &stepper15 );
    Delay_ms( 1000 );
}

void application_task ( void ) {
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "        Clockwise motion         \r\n" );
    log_printf( &logger, " Angle of rotation :  90 degrees \r\n" );
    log_printf( &logger, " Step speed        :  85 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_CLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed - 15, 90, step_360 );
    Delay_ms( 2000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "     Counterclockwise motion     \r\n" );
    log_printf( &logger, " Angle of rotation : 180 degrees \r\n" );
    log_printf( &logger, " Step speed        :  85 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_COUNTERCLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed - 15, 180, step_360 );
    Delay_ms( 2000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "        Clockwise motion         \r\n" );
    log_printf( &logger, " Angle of rotation : 270 degrees \r\n" );
    log_printf( &logger, " Step speed        :  90 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_CLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed - 10, 270, step_360 );
    Delay_ms( 2000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "     Counterclockwise motion     \r\n" );
    log_printf( &logger, " Angle of rotation : 360 degrees \r\n" );
    log_printf( &logger, " Step speed        : 100 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_COUNTERCLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed, 360, step_360 );
    Delay_ms( 2000 );
    
    log_printf( &logger, "---------------------------------\r\n" );
    log_printf( &logger, "        Clockwise motion         \r\n" );
    log_printf( &logger, " Angle of rotation : 360 degrees \r\n" );
    log_printf( &logger, " Step speed        : 100 %%      \r\n" );
    stepper15_set_direction ( &stepper15, STEPPER15_DIRECTION_CLOCKWISE );
    stepper15_step_by_angle( &stepper15, step_speed, 360, step_360 );
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
