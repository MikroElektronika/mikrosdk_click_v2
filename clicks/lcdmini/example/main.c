/*!
 * @file main.c
 * @brief LCDmini Click example
 *
 * # Description
 * This is an example that demonstrates the use of the LCD mini Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - SPI, performing hardware reset, default config, 
 * setting up the backlight, and entering text to be written.
 *
 * ## Application Task
 * This example shows the written text, then the text is moved left, 
 * with changing between rows of the LCD screen.
 *
 * @note If the screen isn't initialized you may need to restart the device.
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "lcdmini.h"

static lcdmini_t lcdmini;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lcdmini_cfg_t lcdmini_cfg;  /**< Click config object. */

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
    lcdmini_cfg_setup( &lcdmini_cfg );
    LCDMINI_MAP_MIKROBUS( lcdmini_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == lcdmini_init( &lcdmini, &lcdmini_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    lcdmini_hw_reset( &lcdmini );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   SPI LCD Config    \r\n" );
    log_printf( &logger, " Clear LCD display   \r\n" );
    log_printf( &logger, "     Cursor OFF      \r\n" );
    
    if ( LCDMINI_ERROR == lcdmini_default_cfg ( &lcdmini ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Setting Backlight  \r\n" );
    lcdmini_set_backlight ( &lcdmini, 1 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Set Contrast: 200  \r\n" );
    lcdmini_set_contrast( &lcdmini, 200 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "     Display text    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    
    lcdmini_display_text ( &lcdmini, 1, 6, "Mikro E" );
    lcdmini_display_text ( &lcdmini, 2, 2, "LCD mini Click" ); 
    lcdmini_display_text ( &lcdmini, 3, 2, "LCD mini Click" ); 
    lcdmini_display_text ( &lcdmini, 4, 6, "Mikro E" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    Delay_ms ( 500 );
    lcdmini_send_cmd( &lcdmini, LCDMINI_SHIFT_LEFT ); 
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
