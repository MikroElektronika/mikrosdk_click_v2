/*!
 * \file 
 * \brief Color 2 Click example
 * 
 * # Description
 * This example demonstrates the use of Color 2 click board by reading data
 * from RGB channels and converting them to HSL color and displaying those data as 
 * well as the detected color name on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the values of all channels and converts
 * them to HSL color and displays those data as well as the detected color name on the USB UART
 * every 100ms approximately.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color2.h"

// ------------------------------------------------------------------ VARIABLES

static color2_t color2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    color2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.
    color2_cfg_setup( &cfg );
    COLOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color2_init( &color2, &cfg );
    
    if ( COLOR2_ERROR == color2_default_cfg ( &color2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    // Wait for the data ready interrupt indication
    while ( color2_get_int_pin ( &color2 ) );
    
    uint8_t status = 0;
    color2_rgb_t rgb;
    if ( ( COLOR2_OK == color2_read_status ( &color2, &status ) ) && 
         ( COLOR2_OK == color2_read_rgb ( &color2, &rgb ) ) )
    {
        color2_hsl_t hsl;
        color2_rgb_to_hsl ( &color2, &rgb, &hsl );
        log_printf ( &logger, "\r\n Red: %u\r\n", rgb.red );
        log_printf ( &logger, " Green: %u\r\n", rgb.green );
        log_printf ( &logger, " Blue: %u\r\n", rgb.blue );
        log_printf ( &logger, " Hue: %.1f deg\r\n", hsl.hue );
        log_printf ( &logger, " Saturation: %.1f %%\r\n", hsl.saturation );
        log_printf ( &logger, " Lightness: %.1f %%\r\n", hsl.lightness );
        log_printf ( &logger, " Dominated color: " );
        switch ( color2_get_color ( &hsl ) )
        {
            case COLOR2_RED_COLOR:
            {
                log_printf ( &logger, "RED\r\n" );
                break;
            }
            case COLOR2_YELLOW_COLOR:
            {
                log_printf ( &logger, "YELLOW\r\n" );
                break;
            }
            case COLOR2_GREEN_COLOR:
            {
                log_printf ( &logger, "GREEN\r\n" );
                break;
            }
            case COLOR2_CYAN_COLOR:
            {
                log_printf ( &logger, "CYAN\r\n" );
                break;
            }
            case COLOR2_BLUE_COLOR:
            {
                log_printf ( &logger, "BLUE\r\n" );
                break;
            }
            case COLOR2_MAGENTA_COLOR:
            {
                log_printf ( &logger, "MAGENTA\r\n" );
                break;
            }
            case COLOR2_WHITE_COLOR:
            {
                log_printf ( &logger, "WHITE\r\n" );
                break;
            }
            case COLOR2_BLACK_COLOR:
            {
                log_printf ( &logger, "BLACK\r\n" );
                break;
            }
            default:
            {
                log_printf ( &logger, "UNKNOWN\r\n" );
                break;
            }
        }
    }
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
