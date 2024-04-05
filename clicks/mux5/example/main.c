/*!
 * @file main.c
 * @brief MUX 5 Click example
 *
 * # Description
 * This example demonstrates the use of MUX 5 click board by mapping the common connection
 * A and B to different channels every 5 seconds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Maps the common connection A and B to different channels every 5 seconds, and displays
 * the channels state on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mux5.h"

static mux5_t mux5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mux5_cfg_t mux5_cfg;  /**< Click config object. */

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
    mux5_cfg_setup( &mux5_cfg );
    MUX5_MAP_MIKROBUS( mux5_cfg, MIKROBUS_1 );
    if ( MUX5_OK != mux5_init( &mux5, &mux5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MUX5_OK != mux5_default_cfg ( &mux5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t ch_num = 0;
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_ALL, MUX5_CHANNEL_STATE_HIGH_Z ) )
    {
        log_printf ( &logger, " All channels disconnected\r\n" );
    }
    Delay_ms ( 1000 );
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_1 << ch_num, MUX5_CHANNEL_STATE_COM_A ) )
    {
        log_printf ( &logger, " Channel %u connected to COM_A\r\n", ( uint16_t ) ( ch_num + 1 ) );
    }
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_16 >> ch_num, MUX5_CHANNEL_STATE_COM_B ) )
    {
        log_printf ( &logger, " Channel %u connected to COM_B\r\n\n", ( uint16_t ) ( 16 - ch_num ) );
    }
    if ( ++ch_num >= 16 )
    {
        ch_num = 0;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
