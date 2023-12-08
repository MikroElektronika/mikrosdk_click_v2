/*!
 * @file main.c
 * @brief AudioAMP 12 Click Example.
 *
 * # Description
 * This example demonstrates the use of AudioAMP 12 Click board™. 
 * The library contains an API for switching between two gain settings 
 * and device control selection between operation and standby mode.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART. After driver initialization, 
 * the app sets default settings performs a power-up sequence, and sets the sound volume to 6 dB.
 *
 * ## Application Task
 * The app performs circles the volume switch between two gain settings, 
 * 6 dB or 12 dB, every 5 seconds. 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "audioamp12.h"

static audioamp12_t audioamp12;    /**< AudioAMP 12 Click driver object. */
static log_t logger;               /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    audioamp12_cfg_t audioamp12_cfg;    /**< Click config object. */

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
    audioamp12_cfg_setup( &audioamp12_cfg );
    AUDIOAMP12_MAP_MIKROBUS( audioamp12_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == audioamp12_init( &audioamp12, &audioamp12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    audioamp12_default_cfg ( &audioamp12 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    audioamp12_gain_select( &audioamp12, AUDIOAMP12_GAIN_6_DB );
    log_printf( &logger, " Gain set to 6 dB.\r\n" );
    Delay_ms( 5000 );
    
    audioamp12_gain_select( &audioamp12, AUDIOAMP12_GAIN_12_DB );
    log_printf( &logger, " Gain set to 12 dB.\r\n" );
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
