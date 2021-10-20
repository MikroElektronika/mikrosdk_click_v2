/*!
 * \file 
 * \brief Color3 Click example
 * 
 * # Description
 * This application return the color of object.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies default settings and makes an initial log.
 * 
 * ## Application Task  
 * Checks which color is detected by the sensor.
 * The detected color name is being logged on the USBUART.
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
static uint8_t is_color;
static float color_value;

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
    Delay_ms( 100 );

    color3_set_default_settings( &color3 );
    Delay_ms( 1000 );

    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Color 3  Click  \r\n" );
    log_printf( &logger, "-----------------\r\n" );
}

void application_task ( void )
{
    color_value = color3_get_color_value( &color3 );
    is_color = color3_get_color( color_value );

    switch( is_color )
    {
        case COLOR3_ORANGE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: ORANGE\r\n" );
            break;
        }
        case COLOR3_RED_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: RED\r\n" );
            break;
        }
        case COLOR3_PINK_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PINK\r\n" );
            break;
        }
        case COLOR3_PURPLE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PURPLE\r\n" );
            break;
        }
        case COLOR3_BLUE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: BLUE\r\n" );
            break;
        }
        case COLOR3_CYAN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: CYAN\r\n" );
            break;
        }
        case COLOR3_GREEN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: GREEN\r\n" );
            break;
        }
        case COLOR3_YELLOW_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: YELLOW\r\n" );
            break;
        }
        default:
        {
            break;
        }
    }

    Delay_ms( 300 );
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
