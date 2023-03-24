/*!
 * @file main.c
 * @brief OLEDB Click example
 *
 # Description
 * This example demonstrates the use (control) of the OLED B display.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configures the microcontroller for communication and initializes the click
 * board to default state.
 *
 * ## Application Task
 * This section contains the main program that is executed showing a practical
 * example on how to use the implemented functions.
 *
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "oledb.h"

static oledb_t oledb;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    oledb_cfg_t oledb_cfg;  /**< Click config object. */

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
    oledb_cfg_setup( &oledb_cfg );
    OLEDB_MAP_MIKROBUS( oledb_cfg, MIKROBUS_1 );
    err_t init_flag  = oledb_init( &oledb, &oledb_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    oledb_default_cfg ( &oledb );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    oledb_clear_display( &oledb );
    Delay_ms( 100 );

    oledb_write_string( &oledb, OLEDB_FONT_6X8, 0, 0, "     MIKROE     " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 1, 0, "  OLED B click  " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 2, 0, "  with SSD1306  " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 3, 0, "   controller   " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 4, 0, "  TEST EXAMPLE  " );
    Delay_ms( 3000 );
    
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 0, 0, " TEXT SCROLL EXAMPLE " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 4, 0, " TEXT SCROLL EXAMPLE " );
    Delay_ms( 1000 );
    
    oledb_scroll_right( &oledb, 4, 0 );
    Delay_ms( 6000 );
    oledb_stop_scroll( &oledb );
    
    oledb_clear_display( &oledb );
    Delay_ms( 100 );
    
    oledb_display_picture( &oledb, oledb_img_mikroe );
    Delay_ms( 500 );
    oledb_send_cmd( &oledb, OLEDB_INVERTDISPLAY );
    Delay_ms( 500 );
    oledb_send_cmd( &oledb, OLEDB_NORMALDISPLAY );
    Delay_ms( 500 );
    oledb_send_cmd( &oledb, OLEDB_INVERTDISPLAY );
    Delay_ms( 500 );
    oledb_send_cmd( &oledb, OLEDB_NORMALDISPLAY );
    Delay_ms( 300 );

    for ( uint8_t contrast = 0xAF; contrast > 0x00; contrast-- ) 
    {
        oledb_set_contrast( &oledb, contrast );
        Delay_ms( 5 );
    }

    for ( uint8_t contrast = 0x00; contrast < 0xAF; contrast++ ) 
    {
        oledb_set_contrast( &oledb, contrast );
        Delay_ms( 5 );
    }

    oledb_scroll_left( &oledb, 0, 4 );
    Delay_ms( 1000 );
    oledb_stop_scroll( &oledb );

    oledb_scroll_right( &oledb, 0, 4 );
    Delay_ms( 2000 );
    oledb_stop_scroll( &oledb );
    
    oledb_scroll_left( &oledb, 0, 4 );
    Delay_ms( 1000 );
    oledb_stop_scroll( &oledb );
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
