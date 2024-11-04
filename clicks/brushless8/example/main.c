/*!
 * @file main.c
 * @brief Brushless8 Click example
 *
 * # Description
 * This example showcases how to initialize and use the Brushless 8 Click. 
 * This application is a schowcase of controlling speed 
 * and direction of brushless motor with hall sesnor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init 
 * Initializes the Click board to appropriate settings based on selected mode.
 * Initialization settings are sent through I2C bus and the motor itself is
 * controlled via PWM or DAC over I2C.
 * Modes:
 *     - BRUSHLESS8_PWM
 *     - BRUSHLESS8_DAC
 *
 * ## Application Task  
 * This example demonstrates the use of Brushless 8 Click board.
 * Brushless 8 Click communicates with the device via I2C driver in order to 
 * set adequate voltage level for connected motor.
 * Current PWM/DAC settings being output are sent via logger.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * @note Take into consideration that the jumper on Brushless 8 Click board
 * has to be set adequately for selected mode ( @b VSPSEL ).
 *
 * @author Nikola Peric
 */

// ------------------------------------------------------------------- INCLUDES

#include "brushless8.h"
#include "board.h"
#include "math.h"
#include "log.h"

/* Select desired mode. */
#define BRUSHLESS8_MODE BRUSHLESS8_PWM

#define COMM_DELAY 500

// ------------------------------------------------------------------ VARIABLES

static brushless8_t brushless8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless8_cfg_t brushless8_cfg;  /**< Click config object. */

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
    log_info( &logger, "Application Init" );

    // Click initialization.

    brushless8_cfg_setup( &brushless8_cfg );
    // Select desired mode.
    brushless8_cfg.ctrl_mod = BRUSHLESS8_MODE;
    BRUSHLESS8_MAP_MIKROBUS( brushless8_cfg, MIKROBUS_1 );

    BRUSHLESS8_RETVAL init_flag = brushless8_init( &brushless8, &brushless8_cfg );
    if ( BRUSHLESS8_OK != init_flag )
    {
        log_error( &logger, "Application Init Error" );
        log_info( &logger, "Please, run program again..." );

        for ( ; ; );
    }

    brushless8_default_cfg ( &brushless8 );

    if ( BRUSHLESS8_PWM == brushless8.ctrl_mod )
    {
        brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, 0 );
        brushless8_set_duty_cycle( &brushless8, 0 );
        brushless8_pwm_start( &brushless8 );

        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_info( &logger, "Application Task" );
    log_printf( &logger, "------------------------------\r\n" );
}

void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless8_set_duty_cycle ( &brushless8, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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
