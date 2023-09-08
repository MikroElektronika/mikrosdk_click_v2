/*!
 * @file main.c
 * @brief DC Motor 27 Click example
 *
 * # Description
 * This example demonstrates the use of the DC Motor 27 Click board by driving 
 * the motor at different speeds, enabling brake and coast modes.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every second, 
 * places the motor into coast or braking mode.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor27.h"

static dcmotor27_t dcmotor27;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor27_cfg_t dcmotor27_cfg;  /**< Click config object. */

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
    dcmotor27_cfg_setup( &dcmotor27_cfg );
    DCMOTOR27_MAP_MIKROBUS( dcmotor27_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == dcmotor27_init( &dcmotor27, &dcmotor27_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    if ( DCMOTOR27_ERROR == dcmotor27_default_cfg ( &dcmotor27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        float speed = ( float ) speed_cnt / 100;
        dcmotor27_set_duty_cycle( &dcmotor27, speed );
        log_printf( &logger, " Motor speed %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms( 1000 );
    }
    
    log_printf( &logger, " Motor coasting \r\n" );
    dcmotor27_set_coast( &dcmotor27, DCMOTOR27_SET_COAST_ON );
    Delay_ms( 2000 );
    dcmotor27_set_coast( &dcmotor27, DCMOTOR27_SET_COAST_OFF );
    
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        float speed = ( float ) speed_cnt / 100;
        dcmotor27_set_duty_cycle( &dcmotor27, speed );
        log_printf( &logger, " Motor speed %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms( 1000 );
    }
    
    log_printf( &logger, " Motor brake is on \r\n" );
    dcmotor27_pwm_stop( &dcmotor27 );
    Delay_ms( 2000 );
    dcmotor27_pwm_start( &dcmotor27 );
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
