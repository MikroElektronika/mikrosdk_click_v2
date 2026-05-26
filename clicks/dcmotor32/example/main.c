/*!
 * @file main.c
 * @brief DC Motor 32 Click example
 *
 * # Description
 * This example demonstrates the use of the DC Motor 32 Click board for
 * controlling a DC motor. The application switches between different
 * operation modes (forward, brake, reverse, and off) and measures the
 * output current in each state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and DC Motor 32 Click driver, and applies the
 * default configuration.
 *
 * ## Application Task
 * Cycles through motor operation modes, measures the output current,
 * and logs the results to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor32.h"

#ifndef MIKROBUS_POSITION_DCMOTOR32
    #define MIKROBUS_POSITION_DCMOTOR32 MIKROBUS_1
#endif

static dcmotor32_t dcmotor32;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor32_cfg_t dcmotor32_cfg;  /**< Click config object. */

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
    dcmotor32_cfg_setup( &dcmotor32_cfg );
    DCMOTOR32_MAP_MIKROBUS( dcmotor32_cfg, MIKROBUS_POSITION_DCMOTOR32 );
    if ( DCMOTOR32_OK != dcmotor32_init( &dcmotor32, &dcmotor32_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR32_OK != dcmotor32_default_cfg ( &dcmotor32 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float current = 0;
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_FORWARD_HSB ) )
    {
        log_printf( &logger, " MODE: Forward\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
        }
    }
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_SLOW_DECAY_LSA ) )
    {
        log_printf( &logger, " MODE: Brake\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
        }
    }
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_REVERSE_HSA ) )
    {
        log_printf( &logger, " MODE: Reverse\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
        }
    }
    if ( DCMOTOR32_OK == dcmotor32_set_operation_mode ( &dcmotor32, DCMOTOR32_CONTROL_MODE_HALF_BRIDGE_A_TRI_STATE ) )
    {
        log_printf( &logger, " MODE: Off\r\n\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        if ( DCMOTOR32_OK == dcmotor32_get_out_current ( &dcmotor32, &current ) ) 
        {
            log_printf( &logger, " Current : %.3f A\r\n\n", current );
        }
    }
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
