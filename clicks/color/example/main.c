/*!
 * \file 
 * \brief Color Click example
 * 
 * # Description
 * This demo shows color detection/recognition 
 * functionality of the Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and driver.
 * 
 * ## Application Task  
 * Checks which color is detected by the sensor.
 * The name of the detected color is logged on the USBUART.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color.h"

// ------------------------------------------------------------------ VARIABLES

static color_t color;
static log_t logger;

static uint8_t is_color;
static float color_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    color_cfg_t cfg;

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

    color_cfg_setup( &cfg );
    COLOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color_init( &color, &cfg );
    color_default_cfg( &color );
    is_color = 0;
}

void application_task ( void )
{
    color_value = color_get_color_value( &color );
    is_color = color_get_color( color_value );

    switch( is_color )
    {
        case ORANGE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: ORANGE\r\n" );
            break;
        }
        case RED_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: RED\r\n" );
            break;
        }
        case PINK_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PINK\r\n" );
            break;
        }
        case PURPLE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PURPLE\r\n" );
            break;
        }
        case BLUE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: BLUE\r\n" );
            break;
        }
        case CYAN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: CYAN\r\n" );
            break;
        }
        case GREEN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: GREEN\r\n" );
            break;
        }
        case YELLOW_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: YELLOW\r\n" );
            break;
        }
        default:
        {
            break;
        }
    }

    Delay_ms ( 300 );
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
