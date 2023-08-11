/*!
 * @file main.c
 * @brief H-Bridge 13 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 13 click board by
 * driving the motor connected to OUT A and OUT B, in both directions with braking and freewheeling. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * This example is driving a motor in both directions with changes in speed and
 * motor braking and freewheeling in between.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge13.h"

static hbridge13_t hbridge13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge13_cfg_t hbridge13_cfg;  /**< Click config object. */

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
    hbridge13_cfg_setup( &hbridge13_cfg );
    HBRIDGE13_MAP_MIKROBUS( hbridge13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge13_init( &hbridge13, &hbridge13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE13_ERROR == hbridge13_default_cfg ( &hbridge13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for( uint8_t n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        log_printf( &logger, " Motor in forward mode with speed of %d %% \r\n", ( uint16_t ) n_cnt );
        hbridge13_set_direction( &hbridge13, HBRIDGE13_DIR_FORWARD, n_cnt );
        Delay_ms( 1000 );
    }
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge13_set_brake( &hbridge13 );
    Delay_ms( 5000 );
    
    for( uint8_t n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        log_printf( &logger, " Motor in reverse with speed of %d %% \r\n", ( uint16_t ) n_cnt );
        hbridge13_set_direction( &hbridge13, HBRIDGE13_DIR_REVERSE, n_cnt );
        Delay_ms( 1000 );
    }
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge13_set_coast( &hbridge13 );
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
