/*!
 * @file main.c
 * @brief DC Motor 25 Click example
 *
 * # Description
 * This example demonstrates the use of DC Motor 25 Click board™
 * by driving the DC motor in both directions every 3 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the I2C driver and performs the Click default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the DC Motor 25 Click board™.
 * Drives the motors in the forward and reverse direction 
 * with a 3 seconds delay with engine braking between direction changes.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor25.h"

static dcmotor25_t dcmotor25;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor25_cfg_t dcmotor25_cfg;  /**< Click config object. */

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
    dcmotor25_cfg_setup( &dcmotor25_cfg );
    DCMOTOR25_MAP_MIKROBUS( dcmotor25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dcmotor25_init( &dcmotor25, &dcmotor25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR25_ERROR == dcmotor25_default_cfg ( &dcmotor25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Forward\r\n" );
    dcmotor25_forward( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Brake\r\n" );
    dcmotor25_brake( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Reverse\r\n" );
    dcmotor25_reverse( &dcmotor25 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf ( &logger, " Brake\r\n" );
    dcmotor25_brake( &dcmotor25 );
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
