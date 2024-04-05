/*!
 * @file main.c
 * @brief Stepper18 Click example
 *
 * # Description
 * This example showcases the device's ability to control the motor.
 * It initializes the device for control and moves the motor in two 
 * directions in a variety of speeds for 360 degrees.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART and I2C communication modules, and additional  
 * pins for motor control, and set's default configuration
 *
 * ## Application Task
 * First it move motor clockwise for 360 degrees in medium speed. 
 * Then changes direction and moves motor for 180 degrees in slow speed,
 * and additional 180 degrees in fast speed.
 *
 * @note
 * Step resolution is changed by the switches[ M0, M1 ] on device.
 * Full step    :   M0=>0 ,     M1=>0
 * Half step    :   M0=>1 ,     M1=>0
 * Quarter step :   M0=>0 ,     M1=>1
 * 1/8 step     :   M0=>1 ,     M1=>1
 * 1/16 step    :   M0=>Hi-Z ,  M1=>1
 * 1/32 step    :   M0=>0 ,     M1=>Hi-Z
 * 1/64 step    :   M0=>Hi-Z ,  M1=>0
 * 1/128 step   :   M0=>Hi-Z ,  M1=>Hi-Z
 * 1/256 step   :   M0=>1 ,     M1=>0
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepper18.h"

static stepper18_t stepper18;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepper18_cfg_t stepper18_cfg;  /**< Click config object. */

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
    stepper18_cfg_setup( &stepper18_cfg );
    STEPPER18_MAP_MIKROBUS( stepper18_cfg, MIKROBUS_1 );
    err_t init_flag = stepper18_init( &stepper18, &stepper18_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    stepper18_default_cfg ( &stepper18 );
    log_info( &logger, " Application Task " );
    stepper18_set_dir( &stepper18, 0 );
}

void application_task ( void ) 
{
    static uint8_t direction = 0;
    log_printf( &logger, "> Move 360deg in CW direction.\r\n" );
    stepper18_move_motor_angle( &stepper18, 360, STEPPER18_STEP_RES_FULL, STEPPER18_SPEED_MEDIUM );
    direction = !direction;
    stepper18_set_dir( &stepper18, direction );
    Delay_ms ( 500 );
    log_printf( &logger, "> Move 180deg in CCW direction.\r\n" );
    stepper18_move_motor_angle( &stepper18, 180, STEPPER18_STEP_RES_FULL, STEPPER18_SPEED_SLOW );
    Delay_ms ( 1000 );
    log_printf( &logger, "> Move 180deg in CCW direcion.\r\n" );
    stepper18_move_motor_angle( &stepper18, 180, STEPPER18_STEP_RES_FULL, STEPPER18_SPEED_FAST );
    direction = !direction;
    stepper18_set_dir( &stepper18, direction );
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
