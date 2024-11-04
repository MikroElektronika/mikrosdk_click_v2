/*!
 * \file 
 * \brief RgbDriver Click example
 * 
 * # Description
 * This application sets the brightness over RGB value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and logger, and configures the Click board.
 * 
 * ## Application Task  
 * Changes the color of RGB LED tape connected to the Click board every 2 seconds.
 * The name of the selected color will be displayed on USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rgbdriver.h"

// ------------------------------------------------------------------ VARIABLES

static rgbdriver_t rgbdriver;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rgbdriver_cfg_t cfg;

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

    rgbdriver_cfg_setup( &cfg );
    RGBDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rgbdriver_init( &rgbdriver, &cfg );
    Delay_ms ( 1000 );
    
    rgbdriver_default_cfg( &rgbdriver );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_RED_LOW_INTENSITY );
    log_printf( &logger, "\r\n--- RED ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_ORANGE_LOW_INTENSITY );
    log_printf( &logger, "--- ORANGE ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_YELLOW_LOW_INTENSITY );
    log_printf( &logger, "--- YELLOW ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_GREEN_LOW_INTENSITY );
    log_printf( &logger, "--- GREEN ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_BLUE_LOW_INTENSITY );
    log_printf( &logger, "--- BLUE ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_WHITE_LOW_INTENSITY );
    log_printf( &logger, "--- WHITE ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_PURPLE_LOW_INTENSITY );
    log_printf( &logger, "--- PURPLE ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
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
