/*!
 * @file main.c
 * @brief DC Motor 26 Click example
 *
 * # Description
 * This example demonstrates the use of DC Motor 26 click board by controlling the speed
 * of DC motor over PWM duty cycle as well as displaying the motor current consumption.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the operation mode and motor speed by setting the PWM duty cycle and then calculates
 * the motor current consumption for that speed. All data is being logged on the USB UART
 * where you can track changes.
 *
 * @note
 * The click board swiches should be set as follows: SW 1-2-3-4 : H-H-L-L
 * This sets the click board as a SPI controlled single-channel device so 
 * the motor should be connected to OUT1/2 and OUT3/4.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor26.h"

static dcmotor26_t dcmotor26;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor26_cfg_t dcmotor26_cfg;  /**< Click config object. */

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
    dcmotor26_cfg_setup( &dcmotor26_cfg );
    DCMOTOR26_MAP_MIKROBUS( dcmotor26_cfg, MIKROBUS_1 );
    if ( DCMOTOR26_OK != dcmotor26_init( &dcmotor26, &dcmotor26_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR26_OK != dcmotor26_default_cfg ( &dcmotor26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_OUTPUT_OFF ) )
    {
        log_printf ( &logger, " MODE: OFF\r\n" );
        Delay_ms ( 3000 );
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_FORWARD ) )
    {
        dcmotor26_set_cm_sel_pin ( &dcmotor26, DCMOTOR26_PIN_LOW_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: FORWARD\r\n" );
            if ( DCMOTOR26_OK == dcmotor26_set_ch1_duty_period ( &dcmotor26, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR26_OK == dcmotor26_get_motor_current ( &dcmotor26, &current ) )
            {
                log_printf ( &logger, " Current: %.3f A\r\n\n", current );
            }
            Delay_ms ( 500 );
        }
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_BRAKE ) )
    {
        log_printf ( &logger, " MODE: BRAKE\r\n" );
        Delay_ms ( 3000 );
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_REVERSE ) )
    {
        dcmotor26_set_cm_sel_pin ( &dcmotor26, DCMOTOR26_PIN_HIGH_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: REVERSE\r\n" );
            if ( DCMOTOR26_OK == dcmotor26_set_ch1_duty_period ( &dcmotor26, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR26_OK == dcmotor26_get_motor_current ( &dcmotor26, &current ) )
            {
                log_printf ( &logger, " Current: %.3f A\r\n\n", current );
            }
            Delay_ms ( 500 );
        }
    }
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
