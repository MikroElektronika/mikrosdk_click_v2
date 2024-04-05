/*!
 * @file main.c
 * @brief DCMotor18 Click example
 *
 * # Description
 * This example application showcases ability of click 
 * board to control DC motors using PWM modulation in 
 * both directions and different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of MCU communication modules (PWM, ADC, UART) 
 * and additioal gpio for control of the device. Then sets 
 * default configuration that enables device to control the DC motor.
 *
 * ## Application Task
 * Drives motor in one direction from 0 to 100% of the speed using 
 * PWM, and then returns it back to 0. Then changes the rotation
 * direction and repeats the process of increasing and decreasing 
 * acceleration.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor18.h"

static dcmotor18_t dcmotor18;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor18_cfg_t dcmotor18_cfg;  /**< Click config object. */

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
    dcmotor18_cfg_setup( &dcmotor18_cfg );
    DCMOTOR18_MAP_MIKROBUS( dcmotor18_cfg, MIKROBUS_1 );
    err_t init_flag  = dcmotor18_init( &dcmotor18, &dcmotor18_cfg );
    if ( PWM_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dcmotor18_default_cfg ( &dcmotor18 );

    log_info( &logger, " Application Task " );
    Delay_ms ( 500 );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float speed = duty_cnt / 10.0;
    static uint8_t direction = 1;

    dcmotor18_set_direction( &dcmotor18, direction );
    dcmotor18_set_speed_percentage ( &dcmotor18, speed );

    if ( dcmotor18.direction )
    {
        log_printf( &logger, "<<< " );
    }
    else
    {
        log_printf( &logger, ">>> " );
    }
    log_printf( &logger, "Speed: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );

    if ( 10 == duty_cnt )
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt )
    {
        duty_inc = 1;
        direction = !direction;
    }
    duty_cnt += duty_inc;

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
