/*!
 * @file main.c
 * @brief Boost 11 Click Example.
 *
 * # Description
 * This example demonstrates the use of Boost 11 Click board 
 * by controlling the output state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module, log UART, and activate the boost operating mode.
 *
 * ## Application Task
 * The demo application reads measurements of the output voltage level [V].
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "boost11.h"

static boost11_t boost11;   /**< Boost 11 Click driver object. */
static log_t logger;        /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    boost11_cfg_t boost11_cfg;  /**< Click config object. */

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
    boost11_cfg_setup( &boost11_cfg );
    BOOST11_MAP_MIKROBUS( boost11_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == boost11_init( &boost11, &boost11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    boost11_active_mode( &boost11 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( BOOST11_OK == boost11_read_an_pin_voltage ( &boost11, &voltage ) ) 
    {
        log_printf( &logger, " Output Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms ( 1000 );
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
