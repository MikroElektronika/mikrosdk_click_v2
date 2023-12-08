/*!
 * @file main.c
 * @brief Zero-Cross Click Example.
 *
 * # Description
 * This example demonstrates the use of the Zero-Cross Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of the log UART and basic Click initialisation.
 *
 * ## Application Task
 * Reading frequency value approximately once every second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "zerocross.h"

static zerocross_t zerocross;   /**< Zero-Cross Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    zerocross_cfg_t zerocross_cfg;  /**< Click config object. */

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
    zerocross_cfg_setup( &zerocross_cfg );
    ZEROCROSS_MAP_MIKROBUS( zerocross_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == zerocross_init( &zerocross, &zerocross_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float freq_val = 0;
    zerocross_get_freq( &zerocross, &freq_val );
    log_printf( &logger, " Freq %.2f Hz \n\r", freq_val );
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
