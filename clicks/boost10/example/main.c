/*!
 * @file main.c
 * @brief Boost 10 Click example
 *
 * # Description
 * This example demonstrates the use of the Boost 10 Click board by dynamically
 * adjusting the output voltage using the onboard digital potentiometer.
 * The application gradually increases and decreases the output voltage
 * within the supported range and logs the set value to the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Boost 10 Click driver and configures SPI
 * communication through the mikroBUS socket.
 *
 * ## Application Task
 * Periodically changes the output voltage between the minimum and maximum
 * supported values in defined steps and logs the configured voltage.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "boost10.h"

static boost10_t boost10;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost10_cfg_t boost10_cfg;  /**< Click config object. */

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
    boost10_cfg_setup( &boost10_cfg );
    BOOST10_MAP_MIKROBUS( boost10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == boost10_init( &boost10, &boost10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static float vout = BOOST10_VOUT_MIN;
    static float vout_step = 0.5;
    if ( BOOST10_OK == boost10_set_vout ( &boost10, vout ) )
    {
        log_printf ( &logger, " VOUT: %.1f V\r\n\n", vout );
        vout += vout_step;
        if ( vout > BOOST10_VOUT_MAX || vout < BOOST10_VOUT_MIN )
        {
            vout_step = -vout_step;
            vout += vout_step;
            vout += vout_step;
        }
    }
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
