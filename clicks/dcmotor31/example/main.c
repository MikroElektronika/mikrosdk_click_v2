/*!
 * @file main.c
 * @brief DC Motor 31 Click example
 *
 * # Description
 * This example demonstrates the operation of the DC Motor 31 Click board by 
 * alternating the motor direction between forward and reverse with braking in between.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board, then applies the default configuration.
 *
 * ## Application Task
 * Changes the motor direction from forward to reverse with a brake period in between,
 * and logs the current motor state on the UART terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor31.h"

static dcmotor31_t dcmotor31;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor31_cfg_t dcmotor31_cfg;  /**< Click config object. */

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
    dcmotor31_cfg_setup( &dcmotor31_cfg );
    DCMOTOR31_MAP_MIKROBUS( dcmotor31_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor31_init( &dcmotor31, &dcmotor31_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR31_ERROR == dcmotor31_default_cfg ( &dcmotor31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Motor state : FORWARD\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor state : BRAKE\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_BRAKE );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor state : REVERSE\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Motor state : BRAKE\r\n\n" );
    dcmotor31_set_mode ( &dcmotor31, DCMOTOR31_MODE_BRAKE );
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
