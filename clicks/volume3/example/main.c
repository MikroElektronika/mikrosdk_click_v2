/*!
 * @file main.c
 * @brief Volume 3 Click example
 *
 * # Description
 * This example demonstrates control of the Volume 3 Click stereo attenuator.
 * The app enables zero-crossing and audio output, then sweeps left and right
 * volumes in opposite directions while logging their levels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger, configures the driver, and enables output with
 * zero-crossing.
 *
 * ## Application Task
 * Gradually changes left and right volume in opposite directions, printing
 * their values to the log.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "volume3.h"

static volume3_t volume3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    volume3_cfg_t volume3_cfg;  /**< Click config object. */

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
    volume3_cfg_setup( &volume3_cfg );
    VOLUME3_MAP_MIKROBUS( volume3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == volume3_init( &volume3, &volume3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    volume3_zero_crossing_enable ( &volume3 );
    volume3_sound_enable ( &volume3 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int8_t volume = VOLUME3_VOLUME_MUTE;
    static int8_t step = 1;
    
    if ( VOLUME3_OK == volume3_set_volume ( &volume3, volume, VOLUME3_VOLUME_MAX - volume ) )
    {
        log_printf( &logger, " Volume [L/R]: %u/%u %%\r\n\n", 
                    ( uint16_t ) volume, ( uint16_t ) ( VOLUME3_VOLUME_MAX - volume ) );
        Delay_ms ( 100 );
    }

    volume += step;
    if ( ( volume > VOLUME3_VOLUME_MAX ) || ( volume < VOLUME3_VOLUME_MUTE ) )
    {
        Delay_ms ( 1000 );
        step = -step;
        volume += step;
        volume += step;
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
