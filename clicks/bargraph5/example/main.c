/*!
 * @file main.c
 * @brief BarGraph 5 Click example
 *
 * # Description
 * This example demonstrates the use of BarGraph 5 Click board by changing
 * the level of all BarGraph output channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Changes the level of all BarGraph channels once per second.
 * The channels level is displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bargraph5.h"

static bargraph5_t bargraph5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bargraph5_cfg_t bargraph5_cfg;  /**< Click config object. */

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
    bargraph5_cfg_setup( &bargraph5_cfg );
    BARGRAPH5_MAP_MIKROBUS( bargraph5_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == bargraph5_init( &bargraph5, &bargraph5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BARGRAPH5_ERROR == bargraph5_default_cfg ( &bargraph5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( bargraph5_level_t cnt = BARGRAPH5_LEVEL_0; cnt <= BARGRAPH5_LEVEL_4; cnt++ )
    {
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_0, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_1, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_2, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_3, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_4, cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        bargraph5_set_bar_level ( &bargraph5, BARGRAPH5_BAR_5, BARGRAPH5_LEVEL_4 - cnt, BARGRAPH5_BRIGHTNESS_DEFAULT );
        log_printf( &logger, " Bars 0-2-4 level: %u\r\n", ( uint16_t ) cnt );
        log_printf( &logger, " Bars 1-3-5 level: %u\r\n\n", ( uint16_t ) ( BARGRAPH5_LEVEL_4 - cnt ) );
        Delay_ms ( 1000 );
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
