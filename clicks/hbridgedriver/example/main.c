/*!
 * @file main.c
 * @brief H-Bridge Driver Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the H-Bridge Driver Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes GPIO and LOG structures, and sets AN, RST, CS, PWM and 
 * INT pins as output and start to write log.
 *
 * ## Application Task
 * Demonstrates use of the H-Bridge Driver click board by turning connected MOSFETs 
 * gates high or low in order to drive the motor forward, in reverse, brake or coast.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridgedriver.h"

static hbridgedriver_t hbridgedriver;   /**< H-Bridge Driver Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridgedriver_cfg_t hbridgedriver_cfg;  /**< Click config object. */

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
    hbridgedriver_cfg_setup( &hbridgedriver_cfg );
    HBRIDGEDRIVER_MAP_MIKROBUS( hbridgedriver_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridgedriver_init( &hbridgedriver, &hbridgedriver_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    hbridgedriver_glo_enable( &hbridgedriver, HBRIDGEDRIVER_PROP_EN );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " The motor turns forward! \r\n" );
    hbridgedriver_forward( &hbridgedriver );
    Delay_ms( 3000 );
    log_printf( &logger, " The motor brakes! \r\n" );
    hbridgedriver_braking( &hbridgedriver );
    Delay_ms( 3000 );
    log_printf( &logger, " The motor turns in reverse \r\n" );
    hbridgedriver_reverse( &hbridgedriver );
    Delay_ms( 3000 );
    log_printf( &logger, " The motor coasting \r\n" );
    hbridgedriver_coasting( &hbridgedriver );
    Delay_ms( 3000 );
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
