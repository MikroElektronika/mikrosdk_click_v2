/*!
 * @file main.c
 * @brief DC Motor 23 Click example
 *
 * # Description
 * This example demonstrates the use of DC Motor 23 click board™. 
 * by driving the motors in both direction every 3 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration 
 * which sets the output torque to 100%.
 *
 * ## Application Task
 * This example demonstrates the use of the DC Motor 23  Click board™.
 * Drives the motors in the clockwise direction,
 * after that decay the motors with a 3 seconds delay
 * then switches to the counter-clockwise direction, 
 * and decay the motors with a 3 seconds delay.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor23.h"

static dcmotor23_t dcmotor23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor23_cfg_t dcmotor23_cfg;  /**< Click config object. */

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
    dcmotor23_cfg_setup( &dcmotor23_cfg );
    DCMOTOR23_MAP_MIKROBUS( dcmotor23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor23_init( &dcmotor23, &dcmotor23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( DCMOTOR23_ERROR == dcmotor23_default_cfg ( &dcmotor23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf ( &logger, "--------------------------\r\n" );
}

void application_task ( void ) 
{    
    if ( DCMOTOR23_OK == dcmotor23_set_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Clockwise\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Decay\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Decay\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_counter_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Counter-Clockwise\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_counter_clockwise( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Counter-Clockwise\r\n\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_A ) )
    {
        log_printf ( &logger, " OUTA: Decay\r\n" );
    }
    if ( DCMOTOR23_OK == dcmotor23_set_decay( &dcmotor23, DCMOTOR23_SEL_OUT_B ) )
    {
        log_printf ( &logger, " OUTB: Decay\r\n" );
    }
    log_printf ( &logger, "--------------------------\r\n" );
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
