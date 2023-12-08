/*!
 * @file main.c
 * @brief MUX 9 Click example
 *
 * # Description
 * This example demonstrates the use of MUX 9 click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the reset.
 *
 * ## Application Task
 * This is an example that shows the use of a MUX 9 click board™.
 * This example shows switching channels (from CH 1 to CH 8) on and off.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mux9.h"

static mux9_t mux9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    mux9_cfg_t mux9_cfg;  /**< Click config object. */

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
    mux9_cfg_setup( &mux9_cfg );
    MUX9_MAP_MIKROBUS( mux9_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mux9_init( &mux9, &mux9_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    mux9_reset( &mux9 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------\r\n" );
}

void application_task ( void )
{
    for ( uint8_t ch_pos = MUX9_SELECT_CH_1; ch_pos <= MUX9_SELECT_CH_8; ch_pos++ )
    {
        if ( MUX9_OK == mux9_active_channel( &mux9, ch_pos ) )
        {
            log_printf( &logger, " The Channel %d is activated. \r\n", ( uint16_t ) ch_pos );
            Delay_ms( 1000 );
        }
    }
    log_printf( &logger, " -----------\r\n" );
    Delay_ms( 1000 );
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
