/*!
 * @file main.c
 * @brief DC Motor 29 Click example
 *
 * # Description
 * This example demonstrates the use of the DC Motor 29 Click board by driving the 
 * motor in both directions with braking and coasting in between.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Drives the motor in both directions with coasting and braking in between, every sate is lasting 5 seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor29.h"

static dcmotor29_t dcmotor29;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor29_cfg_t dcmotor29_cfg;  /**< Click config object. */

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
    dcmotor29_cfg_setup( &dcmotor29_cfg );
    DCMOTOR29_MAP_MIKROBUS( dcmotor29_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dcmotor29_init( &dcmotor29, &dcmotor29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR29_ERROR == dcmotor29_default_cfg ( &dcmotor29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
       
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_CW );
    log_printf( &logger, " Driving motor Clockwise \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_BRAKE );
    log_printf( &logger, " Brake is on \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_CCW );
    log_printf( &logger, " Driving motor counter-clockwise \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_COASTING );
    log_printf( &logger, " Driving motor Coasting \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
