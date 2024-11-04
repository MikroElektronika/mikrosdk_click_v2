/*!
 * \file 
 * \brief Color7 Click example
 * 
 * # Description
 * Demo application reads and detects colors - detected color logs on USBUART.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the Click in the default configuration.
 * 
 * ## Application Task  
 * Reads light color and checks which color of light is detected by the sensor
 * If the light color is detected, the detected color message is logged on the USBUART.
 * 
 * *note:* 
 * Light source must be pointed towards sensor in order for sensor to 
 * detect light source color correctly.
 * We used the HSL color palette on the monitor as an example.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "color7.h"

// ------------------------------------------------------------------ VARIABLES

static color7_t color7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    color7_cfg_t cfg;

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

    color7_cfg_setup( &cfg );
    COLOR7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color7_init( &color7, &cfg );

    color7_default_cfg( &color7 );
    log_info( &logger, "---- Start measurement ----" );
}

void application_task ( void )
{
    uint8_t color;

    //  Task implementation.

    color = color7_get_color( &color7 );

    switch( color )
    {
        case 1:
        {
            log_printf( &logger, "--- Color: ORANGE \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, "--- Color: RED \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, "--- Color: PINK \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, "--- Color: PURPLE \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, "--- Color: BLUE \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, "--- Color: CYAN \r\n" );
            break;
        }
        case 7:
        {
            log_printf( &logger, "--- Color: GREEN \r\n" );
            break;
        }
        case 8:
        {
            log_printf( &logger, "--- Color: YELLOW \r\n" );
            break;
        }
        default:
        {
            // log_printf( &logger, "--- Color: UNRECOGNIZABLE \r\n" );
            break;
        }
    }
    Delay_100ms();
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
