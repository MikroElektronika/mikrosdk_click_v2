/*!
 * @file main.c
 * @brief IPS Display 3 Click example
 *
 * # Description
 * This example demonstrates the use of the IPS Display 3 Click board by showing
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
#include "ipsdisplay3.h"
#include "ipsdisplay3_resources.h"

static ipsdisplay3_t ipsdisplay3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipsdisplay3_cfg_t ipsdisplay3_cfg;  /**< Click config object. */

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
    ipsdisplay3_cfg_setup( &ipsdisplay3_cfg );
    IPSDISPLAY3_MAP_MIKROBUS( ipsdisplay3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ipsdisplay3_init( &ipsdisplay3, &ipsdisplay3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IPSDISPLAY3_ERROR == ipsdisplay3_default_cfg ( &ipsdisplay3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    ipsdisplay3_point_t start_pt, end_pt;

#if IPSDISPLAY3_RESOURCES_INCLUDE_IMG
    log_printf( &logger, " Drawing MIKROE logo example\r\n\n" );
    ipsdisplay3_draw_picture ( &ipsdisplay3, IPSDISPLAY3_ROTATION_VERTICAL_0, ipsdisplay3_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
    log_printf( &logger, " Writing text example\r\n\n" );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = 0;
    start_pt.y = ipsdisplay3.center.y - 50;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "    MIKROE    ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "   128x115px  ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, " IPS Display 3", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "     Click    ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "    GC9107    ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "  controller  ", IPSDISPLAY3_COLOR_RED );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " RGB fill screen example\r\n\n" );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_RED );
    Delay_ms ( 1000 );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_LIME );
    Delay_ms ( 1000 );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_BLUE );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing objects example\r\n\n" );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = ipsdisplay3.center.x - 50;
    start_pt.y = ipsdisplay3.center.y - 50;
    end_pt.x = ipsdisplay3.center.x + 50;
    end_pt.y = ipsdisplay3.center.y + 50;
    ipsdisplay3_draw_line ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = ipsdisplay3.center.x + 50;
    start_pt.y = ipsdisplay3.center.y - 50;
    end_pt.x = ipsdisplay3.center.x - 50;
    end_pt.y = ipsdisplay3.center.y + 50;
    ipsdisplay3_draw_line ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = ipsdisplay3.center.x - 40;
    start_pt.y = ipsdisplay3.center.y - 40;
    end_pt.x = ipsdisplay3.center.x + 40;
    end_pt.y = ipsdisplay3.center.y + 40;
    ipsdisplay3_draw_rectangle ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_CYAN );
    Delay_ms ( 1000 );
    start_pt.x += 20;
    start_pt.y += 20;
    end_pt.x -= 20;
    end_pt.y -= 20;
    ipsdisplay3_draw_rectangle ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_CYAN );
    Delay_ms ( 1000 );
    ipsdisplay3_draw_circle ( &ipsdisplay3, ipsdisplay3.center, ipsdisplay3.center.x - 25, IPSDISPLAY3_COLOR_MAGENTA );
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
