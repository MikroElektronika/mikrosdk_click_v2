/*!
 * \file 
 * \brief OledC Click example
 * 
 * # Description
 * This demo demonstrates the use of the OLED C click board and the control of
 * the OLED C display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and OLED C init and sets full screen on white color
 * with writting demo text.
 * 
 * ## Application Task  
 * This function is composed of three sections :
 *  -  Display demo rectangle.
 *  -  Display demo line.
 *  -  Display demo image.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oledc.h"
#include "oledc_font.h"
#include "oledc_image.h"

// ------------------------------------------------------------------ VARIABLES

static oledc_t oledc;
static log_t logger;

#define text1 "Hello"
#define text2  "this is the demo"
#define text3  "for OLED C click"

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    oledc_cfg_t cfg;

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

    oledc_cfg_setup( &cfg );
    OLEDC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oledc_init( &oledc, &cfg );

    oledc_default_cfg( &oledc );
    oledc_fill_screen( &oledc, 0xFFFF );

    oledc_set_font( &oledc, guiFont_Tahoma_8_Regular, 0 );
    oledc_text( &oledc, text1, 15, 10 );
    oledc_text( &oledc, text2, 5, 30 );
    oledc_text( &oledc, text3, 5, 45 );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    oledc_fill_screen( &oledc, 0xFFFF );
    Delay_100ms();

    // Rectangle demo
    oledc_rectangle( &oledc, 0, 0, 96, 96, 0xF000 );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 5, 5, 91, 91, 0xFF00 );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 10, 10, 86, 86, 0x00F0 );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 15, 15, 81, 81, 0x0F0F );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 20, 20, 76, 76, 0xF000 );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 25, 25, 71, 71, 0xFF00 );
    Delay_100ms();

    // Line demo 
    oledc_rectangle( &oledc, 25, 25, 71, 27, 0 );
    Delay_100ms();
    oledc_rectangle( &oledc, 25, 71, 71, 73, 0 );
    Delay_100ms();
    oledc_rectangle( &oledc, 25, 25, 27, 71, 0 );
    Delay_100ms();
    oledc_rectangle( &oledc, 68, 25, 71, 71, 0 );
    Delay_ms( 3000 );


    // Image demo 
    oledc_image( &oledc, mikroe_with_slogan96x96, 0, 0 );
    Delay_ms( 2000 );
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
