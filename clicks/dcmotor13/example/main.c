/*!
 * @file main.c
 * @brief DCMotor13 Click example
 *
 * # Description
 * This example demonstrates the use of DC Motor 13 click board by driving the motors
 * in both direction in the span of 9 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets the output
 * torque to 100%.
 *
 * ## Application Task
 * Drives the motors in the clockwise direction, then switches to the counter-clockwise direction, 
 * and after that pulls the motors brake with a 3 seconds delay after each change.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor13.h"

static dcmotor13_t dcmotor13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor13_cfg_t dcmotor13_cfg;  /**< Click config object. */

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
    dcmotor13_cfg_setup( &dcmotor13_cfg );
    DCMOTOR13_MAP_MIKROBUS( dcmotor13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor13_init( &dcmotor13, &dcmotor13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR13_ERROR == dcmotor13_default_cfg ( &dcmotor13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_CW ) )
    {
        log_printf ( &logger, " OUTA: Clockwise\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_CW ) )
    {
        log_printf ( &logger, " OUTB: Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_CCW ) )
    {
        log_printf ( &logger, " OUTA: Counter-Clockwise\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_CCW ) )
    {
        log_printf ( &logger, " OUTB: Counter-Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR13_OK == dcmotor13_set_outa_mode ( &dcmotor13, DCMOTOR13_MODE_SHORT_BRAKE ) )
    {
        log_printf ( &logger, " OUTA: Short brake\r\n" );
    }
    if ( DCMOTOR13_OK == dcmotor13_set_outb_mode ( &dcmotor13, DCMOTOR13_MODE_SHORT_BRAKE ) )
    {
        log_printf ( &logger, " OUTB: Short brake\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
