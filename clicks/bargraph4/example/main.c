/*!
 * @file main.c
 * @brief BarGraph4 Click example
 *
 * # Description
 * This example demonstrates the use of BarGraph 4 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables output.
 *
 * ## Application Task
 * Changes the level of all bar graph channels every second.
 * The channels level will be logged on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bargraph4.h"

static bargraph4_t bargraph4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    bargraph4_cfg_t bargraph4_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    bargraph4_cfg_setup( &bargraph4_cfg );
    BARGRAPH4_MAP_MIKROBUS( bargraph4_cfg, MIKROBUS_1 );
    err_t init_flag  = bargraph4_init( &bargraph4, &bargraph4_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    bargraph4_enable_output( &bargraph4 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( bargraph4_level_t cnt = BARGRAPH4_LEVEL_0; cnt <= BARGRAPH4_LEVEL_4; cnt++ )
    {
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_A, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_B, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_C, cnt );
        bargraph4_set_channel_level( &bargraph4, BARGRAPH4_CHANNEL_D, cnt );
        log_printf( &logger, " All channels set to level %u\r\n\n", ( uint16_t ) cnt );
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
