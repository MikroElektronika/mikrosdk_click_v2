/*!
 * @file main.c
 * @brief H-Bridge 15 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 15 Click board by
 * driving the motor in both directions with braking and freewheeling. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * This example is driving a motor in both directions with 
 * motor braking and freewheeling in between.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge15.h"

static hbridge15_t hbridge15;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge15_cfg_t hbridge15_cfg;  /**< Click config object. */

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
    hbridge15_cfg_setup( &hbridge15_cfg );
    HBRIDGE15_MAP_MIKROBUS( hbridge15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge15_init( &hbridge15, &hbridge15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE15_ERROR == hbridge15_default_cfg ( &hbridge15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Motor in forward mode. \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor in reverse mode. \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_FREEWHEEL );
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
