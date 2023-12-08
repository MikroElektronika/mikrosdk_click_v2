/*!
 * @file main.c
 * @brief H-Bridge 12 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 12 click board by
 * driving the motor connected to OUT A and OUT B, in both directions with braking and freewheeling. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Driving motor in both directions for 5 seconds with a motor braking and freewheeling in between.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge12.h"

static hbridge12_t hbridge12;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge12_cfg_t hbridge12_cfg;  /**< Click config object. */

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
    hbridge12_cfg_setup( &hbridge12_cfg );
    HBRIDGE12_MAP_MIKROBUS( hbridge12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge12_init( &hbridge12, &hbridge12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE12_ERROR == hbridge12_default_cfg ( &hbridge12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf( &logger, " Turning motor counterclockwise \r\n" );
    hbridge12_turn_counterclockwise( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Turning motor brake on \r\n" );
    hbridge12_turn_brake_on( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Turning motor clockwise \r\n" );
    hbridge12_turn_clockwise( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Motor freewheeling \r\n" );
    hbridge12_freewheeling_on( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms( 5000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
