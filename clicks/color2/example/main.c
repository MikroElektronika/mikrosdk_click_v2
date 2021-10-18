/*!
 * \file 
 * \brief Color2 Click example
 * 
 * # Description
 * Example demonstrates use of Color 2 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - initialize ISL29125 RGB color light sensor and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Color 2 Click board.
 * ISL29125 RGB color light sensor on Color 2 Click, detects red, green and blue in a variety of lighting conditions
 * and outputting 16-bit resolution data on the USBUART.
 * Also read color and check which color is detected by the sensor.
 * If the color is detected, the detected color message is logged on the USBUART.
 * All data logs on usb uart for aproximetly every 3 sec.
 * 
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
    color2_default_cfg ( &color2 );
}

void application_task ( void )
{
    //  Task implementation.

    uint16_t value_red_color;
    uint16_t value_green_color;
    uint16_t value_blue_color;
    uint8_t is_color;
    float color_value;

    color_value = color2_get_color_value( &color2 );
    is_color = color2_get_color( color_value );

    value_green_color = color2_read_green( &color2 );
    value_red_color = color2_read_red( &color2 );
    value_blue_color = color2_read_blue( &color2 );

    switch(is_color)
    {
        case 1:
        {
            log_printf( &logger, "    *** ORANGE ***\r\n");
            break;
        }
        case 2:
        {
            log_printf( &logger, "    *** RED ***\r\n");
            break;
        }
        case 3:
        {
            log_printf( &logger, "    *** PINK ***\r\n");
            break;
        }
        case 4:
        {
            log_printf( &logger, "    *** PURPLE ***\r\n");
            break;
        }
        case 5:
        {
            log_printf( &logger, "    *** BLUE ***\r\n");
            break;
        }
        case 6:
        {
            log_printf( &logger, "    *** CYAN ***\r\n");
            break;
        }
        case 7:
        {
            log_printf( &logger, "    *** GREEN ***\r\n");
            break;
        }
        case 8:
        {
            log_printf( &logger, "    *** YELLOW ***\r\n");
            break;
        }
        default:
        {
            break;
        }
    }

    log_printf( &logger, "----------------------\r\n");
    log_printf( &logger, " Red  value  : %d\r\n", value_red_color);
    log_printf( &logger, " Green  value  : %d\r\n", value_green_color);
    log_printf( &logger, " Blue  value  : %d\r\n", value_blue_color);
    log_printf( &logger, "----------------------\r\n");

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
