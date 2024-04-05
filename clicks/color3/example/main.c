/*!
 * \file 
 * \brief Color 3 Click example
 * 
 * # Description
 * This example demonstrates the use of Color 3 click board by reading data
 * from RGBC channels and converting them to HSL color and displaying those data as 
 * well as the detected color name on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the values of all channels and converts them to HSL color and displays those data
 * as well as the detected color name on the USB UART every 500ms approximately.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color3.h"

// ------------------------------------------------------------------ VARIABLES

static color3_t color3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    color3_cfg_t cfg;

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
    color3_cfg_setup( &cfg );
    COLOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color3_init( &color3, &cfg );
    Delay_ms ( 100 );

    color3_set_default_settings( &color3 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Color 3  Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );
}

void application_task ( void )
{
    color3_channels_t rgbc;
    if ( COLOR3_OK == color3_get_rgbc_data ( &color3, &rgbc ) )
    {
        color3_hsl_t hsl;
        color3_rgbc_to_hsl ( &color3, &rgbc, &hsl );
        log_printf ( &logger, "\r\n Red: %u\r\n", rgbc.red );
        log_printf ( &logger, " Green: %u\r\n", rgbc.green );
        log_printf ( &logger, " Blue: %u\r\n", rgbc.blue );
        log_printf ( &logger, " Clear: %u\r\n", rgbc.clear );
        log_printf ( &logger, " Hue: %.1f deg\r\n", hsl.hue );
        log_printf ( &logger, " Saturation: %.1f %%\r\n", hsl.saturation );
        log_printf ( &logger, " Lightness: %.1f %%\r\n", hsl.lightness );
        log_printf ( &logger, " Dominated color: " );
        switch ( color3_get_color ( &hsl ) )
        {
            case COLOR3_RED_COLOR:
            {
                log_printf ( &logger, "RED\r\n" );
                break;
            }
            case COLOR3_YELLOW_COLOR:
            {
                log_printf ( &logger, "YELLOW\r\n" );
                break;
            }
            case COLOR3_GREEN_COLOR:
            {
                log_printf ( &logger, "GREEN\r\n" );
                break;
            }
            case COLOR3_CYAN_COLOR:
            {
                log_printf ( &logger, "CYAN\r\n" );
                break;
            }
            case COLOR3_BLUE_COLOR:
            {
                log_printf ( &logger, "BLUE\r\n" );
                break;
            }
            case COLOR3_MAGENTA_COLOR:
            {
                log_printf ( &logger, "MAGENTA\r\n" );
                break;
            }
            case COLOR3_WHITE_COLOR:
            {
                log_printf ( &logger, "WHITE\r\n" );
                break;
            }
            case COLOR3_BLACK_COLOR:
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
    Delay_ms ( 500 );
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
