/*!
 * \file 
 * \brief OledSwitch Click example
 * 
 * # Description
 * This example showcases how to configure and use the OLED Switch Click. This Click is a 
 * combination of a button and a full color organic LED display. Displays settings are first
 * loaded onto the chip and after that you can show any 64x48 pixel image on the display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the Click modules. In order for the
 * Click to work properly, you need to configure display and power settings. 
 * The full initialization of the chip is done in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function shows the user how to display images on the OLED screen. Every image you'd
 * like to display needs to have a resolution of 64x48 and be stored in a 6144 cell array.
 * 
 * @note 
 * Every pixel on the OLED screen is displayed at the time of writing to the chip (PWM 1).
 * Displaying speed can be directly controled by adding delays in the for loop section of 
 * the draw_image(...) function.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oledswitch.h"
#include "oledswitch_image.h"

// ------------------------------------------------------------------ VARIABLES

static oledswitch_t oledswitch;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    oledswitch_cfg_t cfg;
    
    //  Click initialization.

    oledswitch_cfg_setup( &cfg );
    OLEDSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oledswitch_init( &oledswitch, &cfg );
    oledswitch_default_cfg( &oledswitch, OLEDSWITCH_BUFFER_SIZE_SMALL );
}

void application_task ( )
{
    oledswitch_draw_image( &oledswitch, array_red, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );

    oledswitch_draw_image( &oledswitch, array_green, OLEDSWITCH_IMG_SIZE_NORMAL );
    Delay_1sec( );

    oledswitch_draw_image( &oledswitch, array_blue, OLEDSWITCH_IMG_SIZE_NORMAL );
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
