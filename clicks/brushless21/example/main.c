/*!
 * @file main.c
 * @brief Brushless21 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 21 click board by driving the 
 * motor at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets the GPIO 
 * as a default communication and enables the PWM.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle once per second. The duty cycle ranges from 0% to 100%. 
 * When the click board is configured in I2C mode the motor switches the direction at a minimal speed.
 * Also, the chip internal temperature, VBB voltage and the motor speed readings are supported in I2C mode.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless21.h"

static brushless21_t brushless21;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless21_cfg_t brushless21_cfg;  /**< Click config object. */

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
    brushless21_cfg_setup( &brushless21_cfg );
    BRUSHLESS21_MAP_MIKROBUS( brushless21_cfg, MIKROBUS_1 );
    err_t init_flag = brushless21_init( &brushless21, &brushless21_cfg );
    if ( ( PWM_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS21_ERROR == brushless21_default_cfg ( &brushless21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    if ( BRUSHLESS21_OK == brushless21_set_duty_cycle ( &brushless21, duty ) )
    {
        log_printf( &logger, "\r\n Duty Cycle : %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    }
    
    if ( BRUSHLESS21_DRV_SEL_I2C == brushless21.drv_sel ) 
    {
        int8_t temperature = 0;
        float motor_speed = 0;
        float vbb_voltage = 0;
        if ( BRUSHLESS21_OK == brushless21_get_temperature ( &brushless21, &temperature ) )
        {
            log_printf( &logger, " Temperature: %d C\r\n", ( int16_t ) temperature );
        }
        if ( BRUSHLESS21_OK == brushless21_get_motor_speed ( &brushless21, &motor_speed ) )
        {
            log_printf( &logger, " Motor Speed: %.2f Hz\r\n", motor_speed );
        }
        if ( BRUSHLESS21_OK == brushless21_get_vbb_voltage ( &brushless21, &vbb_voltage ) )
        {
            log_printf( &logger, " VBB Voltage: %.2f V\r\n", vbb_voltage );
        }
        if ( 0 == duty_cnt ) 
        {
            duty_inc = 1;
            if ( BRUSHLESS21_OK == brushless21_switch_direction ( &brushless21 ) )
            {
                log_printf( &logger, " Switch direction\r\n" );
            }
        }
    }
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
