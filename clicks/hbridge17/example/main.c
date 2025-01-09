/*!
 * @file main.c
 * @brief H-Bridge 17 Click Example.
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 17 Click board by
 * driving the motor in both directions with braking and freewheeling. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enable H-Bridge driver IC.
 *
 * ## Application Task
 * The demo application drives the motor in both directions 
 * with coasting and braking in between, every state lasts 5 seconds.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge17.h"

static hbridge17_t hbridge17;   /**< H-Bridge 17 Click driver object. */
static log_t logger;            /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge17_cfg_t hbridge17_cfg;  /**< Click config object. */

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
    hbridge17_cfg_setup( &hbridge17_cfg );
    HBRIDGE17_MAP_MIKROBUS( hbridge17_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridge17_init( &hbridge17, &hbridge17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    hbridge17_ic_enable( &hbridge17 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_FORWARD ) )
    {
        log_printf( &logger, " Motor in forward mode.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_BRAKE ) )
    {
        log_printf( &logger, " Motor brake is on.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_REVERSE ) )
    {
        log_printf( &logger, "Motor in reverse mode.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_FREEWHEEL ) )
    {
        log_printf( &logger, " Motor is coasting.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, "-------------------\r\n" );
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
