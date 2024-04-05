/*!
 * @file 
 * @brief DcMotor8 Click example
 * 
 * # Description
 * This click can drive simple DC motors with brushes, providing them with a significant amount 
 * of current and voltage up to 40V. The click has one control input, that uses the PWM signal 
 * from the host MCU. It uses the half-bridge topology to regulate the speed of the motor 
 * rotation, employs advanced dead-time circuitry that monitors the output stage, providing 
 * maximum switching efficiency and features an advanced technique to avoid shoot-through 
 * currents.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the click board.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of DC Motor 8 click
 * board by increasing and decreasing the motor speed.
 * DC Motor 8 Click communicates with the register via the PWM interface.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor8.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor8_t dcmotor8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor8_cfg_setup( &cfg );
    DCMOTOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor8_init( &dcmotor8, &cfg );

    dcmotor8_set_duty_cycle ( &dcmotor8, 0.0 );
    dcmotor8_enable ( &dcmotor8, DCMOTOR8_ENABLE );
    dcmotor8_pwm_start( &dcmotor8 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    dcmotor8_set_duty_cycle ( &dcmotor8, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
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
