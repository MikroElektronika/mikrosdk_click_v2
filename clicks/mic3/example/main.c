/*!
 * @file main.c
 * @brief MIC 3 Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the MIC 3 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SHD to output and log module, maping GPIO for Mikrobus1, and seting SHD pin to 
 * HIGH state.
 *
 * ## Application Task
 * Turning microphone on for the 5 seconds, then turning it off for 5 seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "mic3.h"

static mic3_t mic3;   /**< MIC 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mic3_cfg_t mic3_cfg;  /**< Click config object. */

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
    mic3_cfg_setup( &mic3_cfg );
    MIC3_MAP_MIKROBUS( mic3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == mic3_init( &mic3, &mic3_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    mic3_default_cfg ( &mic3 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " - Microphone is turned on  - \r\n" );
    mic3_shd_pin_set( &mic3, MIC3_PIN_STATE_HIGH );
    Delay_ms( 5000 );
    
    log_printf( &logger, " - Microphone is turned off  - \r\n" );
    mic3_shd_pin_set( &mic3, MIC3_PIN_STATE_LOW );
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
