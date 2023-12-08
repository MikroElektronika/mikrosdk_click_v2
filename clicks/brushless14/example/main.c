/*!
 * @file main.c
 * @brief Brushless14 Click example
 *
 * # Description
 * This application example showcases ability of the device to control motor,
 * It's speed and rotation direction. Also it gives user ability to change other
 * configuration parameters.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (I2C, PWM, UART) and additional 
 * pins (INT, DIR). It reads ID from DAC ic to confirm communcation. Then
 * configures device for control.
 *
 * ## Application Task
 * Drives motor using PWM from 10% duty cycle to 100% and back to 0%. 
 * Increment is done by 10% in span of 2 seconds. Whenever application gets
 * to 0% duty cycle it chages direction of rotation.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless14.h"

static brushless14_t brushless14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless14_cfg_t brushless14_cfg;  /**< Click config object. */

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
    brushless14_cfg_setup( &brushless14_cfg );
    BRUSHLESS14_MAP_MIKROBUS( brushless14_cfg, MIKROBUS_1 );
    err_t init_flag = brushless14_init( &brushless14, &brushless14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint16_t data_read = 0;
    brushless14_dac_read( &brushless14, 0x02, &data_read);
    if ( BRUSHLESS14_DAC_ID != data_read )
    {
        log_error( &logger, " Communication. " );
    }
    
    brushless14_default_cfg ( &brushless14 );
    
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    static uint8_t direction = 0;
    float duty = duty_cnt / 10.0;
    
    brushless14_set_duty_cycle ( &brushless14, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 2000 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        direction = !direction;
        brushless14_set_dir( &brushless14, direction );
    }
    duty_cnt += duty_inc;
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
