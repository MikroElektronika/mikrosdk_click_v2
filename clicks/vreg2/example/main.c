/*!
 * @file main.c
 * @brief VREG 2 Click example
 * 
 * # Description
 * This example demonstrates the use of the VREG 2 Click board by changing
 * the voltage output every 5 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Controls the voltage output by changing the PWM duty cycle every 5 seconds.
 * The duty cycle ranges from 10% to 50%. Each step will be logged on
 * the USB UART where you can track the program flow.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vreg2.h"

static vreg2_t vreg2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vreg2_cfg_t vreg2_cfg;  /**< Click config object. */

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
    vreg2_cfg_setup( &vreg2_cfg );
    VREG2_MAP_MIKROBUS( vreg2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == vreg2_init( &vreg2, &vreg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VREG2_ERROR == vreg2_default_cfg ( &vreg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int8_t duty_pct = 10;
    static int8_t duty_step = 10;
    if ( VREG2_OK == vreg2_set_duty_cycle ( &vreg2, ( float ) duty_pct / 100 ) )
    {
        log_printf( &logger, "\r\n Duty: %u%%\r\n", ( uint16_t ) duty_pct );
    }
    duty_pct += duty_step;
    if ( ( duty_pct > 50 ) || ( duty_pct < 10 ) ) 
    {
        duty_step = -duty_step;
        duty_pct += ( duty_step * 2 );
    }
    Delay_ms( 5000 );
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
