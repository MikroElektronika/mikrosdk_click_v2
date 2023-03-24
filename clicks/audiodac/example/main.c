/*!
 * @file main.c
 * @brief Audio DAC Click example
 *
 * # Description
 * This example demonstrates the use of Audio DAC click board by controling the volume
 * level of both output channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Checks if the auto mute flag is set and then changes the volume level of both output channels
 * every 100ms. All data is being displayed on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "audiodac.h"

static audiodac_t audiodac;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    audiodac_cfg_t audiodac_cfg;  /**< Click config object. */

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
    audiodac_cfg_setup( &audiodac_cfg );
    AUDIODAC_MAP_MIKROBUS( audiodac_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == audiodac_init( &audiodac, &audiodac_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AUDIODAC_ERROR == audiodac_default_cfg ( &audiodac ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t volume = AUDIODAC_VOLUME_MUTE;
    if ( audiodac_get_gpio4_pin ( &audiodac ) )
    {
        log_printf ( &logger, " Auto mute flag (both L and R channels are auto muted)\r\n" );
        // Wait until the channels are auto unmuted, i.e. until a valid digital signal is received
        while ( audiodac_get_gpio4_pin ( &audiodac ) );
    }
    if ( AUDIODAC_OK == audiodac_volume_control ( &audiodac, AUDIODAC_CHANNEL_BOTH, volume ) )
    {
        log_printf ( &logger, "\r\n Volume: " );
        if ( AUDIODAC_VOLUME_MUTE == volume )
        {
            log_printf ( &logger, "MUTE\r\n" );
            Delay_ms ( 3000 );
        }
        else if ( AUDIODAC_VOLUME_MAX == volume )
        {
            log_printf ( &logger, "MAX\r\n" );
            Delay_ms ( 3000 );
        }
        else
        {
            log_printf ( &logger, "%u\r\n", ( uint16_t ) volume );
            Delay_ms ( 100 );
        }
        volume++; 
        if ( volume > AUDIODAC_VOLUME_MAX )
        {
            volume = AUDIODAC_VOLUME_MUTE;
        }
    }
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
