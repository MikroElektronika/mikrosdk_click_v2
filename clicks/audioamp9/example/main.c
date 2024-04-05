/*!
 * @file main.c
 * @brief AudioAmp 9 Click Example.
 *
 * # Description
 * This example demonstrates the use of the AudioAmp 9 Click board by 
 * changing the gain level.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs default configuration putting AudioAmp 9 Click 
 * into Gain 1 mode with unmuted output.
 *
 * ## Application Task
 * Controlling the volume of the speaker by setting the gain level, and increasing it 
 * every 5 seconds until the maximum level is reached, then the sound is muted for 5 seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "audioamp9.h"

static audioamp9_t audioamp9;   /**< AudioAmp 9 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audioamp9_cfg_t audioamp9_cfg;  /**< Click config object. */

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
    audioamp9_cfg_setup( &audioamp9_cfg );
    AUDIOAMP9_MAP_MIKROBUS( audioamp9_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == audioamp9_init( &audioamp9, &audioamp9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    audioamp9_default_cfg ( &audioamp9 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t vol_lvl = AUDIOAMP9_GAIN_LEVEL1; vol_lvl <= AUDIOAMP9_GAIN_LEVEL4; vol_lvl++ )
    {
        audioamp9_set_gain_level( &audioamp9, vol_lvl );
        log_printf( &logger, " Volume gain level %d \r\n ", vol_lvl );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " Sound is muted \r\n " );
    audioamp9_mute_on( &audioamp9 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Sound is unmuted \r\n " );
    audioamp9_mute_off( &audioamp9 );
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
