/*!
 * \file 
 * \brief LedDriver8 Click example
 * 
 * # Description
 * This example demonstrates the use of LED Driver 8 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the Click board.
 * 
 * ## Application Task  
 * Increases the LEDs brightness then toggles all LEDs with a one-second delay.
 * Each step will be logged on the USB UART where you can track the program flow.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver8.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver8_t leddriver8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver8_cfg_t cfg;

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

    leddriver8_cfg_setup( &cfg );
    LEDDRIVER8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver8_init( &leddriver8, &cfg );

    leddriver8_reset( &leddriver8 );
    Delay_ms ( 500 );
    
    leddriver8_output_enable_pin( &leddriver8, LEDDRIVER8_ENABLE_LED_OUTPUTS );
    leddriver8_set_output_gain( &leddriver8, LEDDRIVER8_OUTPUT_GAIN_ALL_LED, LEDDRIVER8_FULL_OUTPUT_CURRENT_GAIN );
    leddriver8_set_mode_register( &leddriver8, LEDDRIVER8_MODE1_NORMAL_MODE, LEDDRIVER8_MODE2_DMBLNK_DIMMING |
                                  LEDDRIVER8_MODE2_CLRERR_ALL | LEDDRIVER8_MODE2_EXP_DISABLE );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    uint16_t cnt;

    log_printf( &logger, "Increasing LEDs brightness...\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    for ( cnt = LEDDRIVER8_MIN_BRIGHTNESS; cnt <= LEDDRIVER8_MAX_BRIGHTNESS; cnt++ )
    {
        leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, cnt );
        Delay_ms ( 20 );
    }
    
    log_printf( &logger, "Toggling all LEDs...\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    for ( cnt = 0; cnt < 5; cnt++ )
    {
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, LEDDRIVER8_MAX_BRIGHTNESS );
       Delay_ms ( 1000 );
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, LEDDRIVER8_MIN_BRIGHTNESS );
       Delay_ms ( 1000 );
    }
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
