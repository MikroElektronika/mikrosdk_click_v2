/*!
 * @file main.c
 * @brief SolidSwitch 2 Click example
 *
 * # Description
 * This example demonstrates the use of SolidSwitch 2 click board by controlling the output state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which maps outputs as follows:
 * OUT2   - IN0,
 * OUT3   - IN1,
 * OUT4-5 - PWM GEN,
 * OUT6-7 - PWM LED.
 *
 * ## Application Task
 * Changes the PWM GEN (max to min) and PWM LED (min to max) duty cycle and toggles the IN0 and IN1
 * pins every 250ms. The duty cycle values and INx toggle messages will be displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch2.h"

static solidswitch2_t solidswitch2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch2_cfg_t solidswitch2_cfg;  /**< Click config object. */

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
    solidswitch2_cfg_setup( &solidswitch2_cfg );
    SOLIDSWITCH2_MAP_MIKROBUS( solidswitch2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch2_init( &solidswitch2, &solidswitch2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH2_ERROR == solidswitch2_default_cfg ( &solidswitch2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( uint16_t duty_cycle = SOLIDSWITCH2_MIN_DUTY_CYCLE; duty_cycle <= SOLIDSWITCH2_MAX_DUTY_CYCLE; duty_cycle += 5 )
    {
        if ( SOLIDSWITCH2_OK == solidswitch2_write_register ( &solidswitch2, SOLIDSWITCH2_REG_PWM_GEN_DC, 
                                                              ( uint8_t ) ( SOLIDSWITCH2_MAX_DUTY_CYCLE - duty_cycle ) ) )
        {
            log_printf ( &logger, " PWM GEN DC: %u\r\n", ( SOLIDSWITCH2_MAX_DUTY_CYCLE - duty_cycle ) );
        }
        if ( SOLIDSWITCH2_OK == solidswitch2_write_register ( &solidswitch2, SOLIDSWITCH2_REG_PWM_LED_DC, ( uint8_t ) duty_cycle ) )
        {
            log_printf ( &logger, " PWM LED DC: %u\r\n", duty_cycle );
        }
        solidswitch2_toggle_in0_pin ( &solidswitch2 );
        log_printf ( &logger, " Toggle IN0 pin\r\n" );
        solidswitch2_toggle_in1_pin ( &solidswitch2 );
        log_printf ( &logger, " Toggle IN1 pin\r\n\n" );
        Delay_ms ( 250 );
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
