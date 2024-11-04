/*!
 * \file 
 * \brief Slider Click example
 * 
 * # Description
 * This example detect even the smallest move, faithfully capturing the smoothness of 
 * the slider movement, while digitizing its position.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Click driver
 * 
 * ## Application Task  
 * Converts analog input voltage (VCC), witch value depends on the slider position,
 * to digital output value, shows result of conversion on LED and logs result on USB UART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "slider.h"

// ------------------------------------------------------------------ VARIABLES

static slider_t slider;
static log_t logger;

static float adc_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    slider_cfg_t cfg;

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

    slider_cfg_setup( &cfg );
    SLIDER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    slider_init( &slider, &cfg );
    Delay_ms ( 200 );

}

void application_task ( void )
{
    adc_value = slider_write_output( &slider );
    log_printf( &logger, "%.2f\r\n", adc_value );
    Delay_ms ( 100 );
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
