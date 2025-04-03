/*!
 * @file main.c
 * @brief IPS Display 2 Click example
 *
 * # Description
 * This example demonstrates the use of the IPS Display 2 Click board by showing
 * a practical example of using the implemented functions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Showcases the text writing example as well as drawing pictures and objects,
 * and filling the whole screen with a desired color. All data is logged on the USB UART
 * where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ipsdisplay2.h"
#include "ipsdisplay2_resources.h"

static ipsdisplay2_t ipsdisplay2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipsdisplay2_cfg_t ipsdisplay2_cfg;  /**< Click config object. */

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
    ipsdisplay2_cfg_setup( &ipsdisplay2_cfg );
    IPSDISPLAY2_MAP_MIKROBUS( ipsdisplay2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ipsdisplay2_init( &ipsdisplay2, &ipsdisplay2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IPSDISPLAY2_ERROR == ipsdisplay2_default_cfg ( &ipsdisplay2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    ipsdisplay2_point_t start_pt, end_pt;

#if IPSDISPLAY2_RESOURCES_INCLUDE_IMG
    log_printf( &logger, " Drawing MIKROE logo example\r\n\n" );
    ipsdisplay2_draw_picture ( &ipsdisplay2, IPSDISPLAY2_ROTATION_VERTICAL_0, ipsdisplay2_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
    log_printf( &logger, " Writing text example\r\n\n" );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = 0;
    start_pt.y = 50;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "      MIKROE      ", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "   IPS Display 2  ", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "       Click      ", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "     240x240px    ", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "ST7789V controller", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "   TEST EXAMPLE   ", IPSDISPLAY2_COLOR_RED );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " RGB fill screen example\r\n\n" );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_RED );
    Delay_ms ( 1000 );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_LIME );
    Delay_ms ( 1000 );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_BLUE );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing objects example\r\n\n" );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = IPSDISPLAY2_POS_WIDTH_MIN;
    start_pt.y = IPSDISPLAY2_POS_HEIGHT_MIN;
    end_pt.x = IPSDISPLAY2_POS_WIDTH_MAX;
    end_pt.y = IPSDISPLAY2_POS_HEIGHT_MAX;
    ipsdisplay2_draw_line ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = IPSDISPLAY2_POS_WIDTH_MAX;
    start_pt.y = IPSDISPLAY2_POS_HEIGHT_MIN;
    end_pt.x = IPSDISPLAY2_POS_WIDTH_MIN;
    end_pt.y = IPSDISPLAY2_POS_HEIGHT_MAX;
    ipsdisplay2_draw_line ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = 60;
    start_pt.y = 40;
    end_pt.x = 180;
    end_pt.y = 100;
    ipsdisplay2_draw_rectangle ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_CYAN );
    Delay_ms ( 1000 );
    start_pt.y += 100;
    end_pt.y += 100;
    ipsdisplay2_draw_rectangle ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_CYAN );
    Delay_ms ( 1000 );
    start_pt.x = 120;
    start_pt.y = 120;
    ipsdisplay2_draw_circle ( &ipsdisplay2, start_pt, start_pt.x, IPSDISPLAY2_COLOR_MAGENTA );
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
