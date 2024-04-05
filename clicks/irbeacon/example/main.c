/*!
 * @file 
 * @brief IrBeacon Click example
 * 
 * # Description
 * This library contains an API for the IrBeacon Click driver.
 * This application is suitable for high pulse current operation.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Enables GPIO and PWM, sets the frequency and duty cycle and enables PWM.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of IR Beacon Click board.
 * It shows how to enable the device and gradualy increase the duty cycle.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irbeacon.h"

// ------------------------------------------------------------------ VARIABLES

static irbeacon_t irbeacon;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irbeacon_cfg_t cfg;

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

    irbeacon_cfg_setup( &cfg );
    IRBEACON_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irbeacon_init( &irbeacon, &cfg );
    irbeacon_pwm_start( &irbeacon );
    
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    irbeacon_set_duty_cycle ( &irbeacon, duty );
    irbeacon_enable_mod( &irbeacon );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        irbeacon_disable_mod( &irbeacon );
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
