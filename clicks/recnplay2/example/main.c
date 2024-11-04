/*!
 * @file main.c
 * @brief Rec N Play 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Rec N Play 2 Click board by 
 * recording and then playing recorded sound.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration.
 *
 * ## Application Task
 * Recording sound for 5 seconds, then playing it back.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "recnplay2.h"

static recnplay2_t recnplay2;   /**< Rec N Play 2 Click driver object. */
static log_t logger;    /**< Logger object. */

#define RECORDING_LEN       5000

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    recnplay2_cfg_t recnplay2_cfg;  /**< Click config object. */

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
    recnplay2_cfg_setup( &recnplay2_cfg );
    RECNPLAY2_MAP_MIKROBUS( recnplay2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == recnplay2_init( &recnplay2, &recnplay2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    recnplay2_default_cfg ( &recnplay2 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Recording... \r\n" );
    recnplay2_record_sound( &recnplay2, RECORDING_LEN );
    Delay_ms ( 1000 );

    log_printf( &logger, " Playing... \r\n" );
    recnplay2_play_sound( &recnplay2, RECORDING_LEN );
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
