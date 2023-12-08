/*!
 * \file 
 * \brief Light Click example
 * 
 * # Description
 * This application return the ambient light intensity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Light Click board.
 * Measured light intensity and calculate light intensity percent from sensor,
 * results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 100 ms when the data value changes.
 * 
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "light.h"

// ------------------------------------------------------------------ VARIABLES

static light_t light;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    light_cfg_t cfg;

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

    light_cfg_setup( &cfg );
    LIGHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    light_init( &light, &cfg );

}

void application_task ( void )
{
    uint16_t light_value;
    uint8_t light_percent;

    light_value = light_read_data( &light );
    light_percent = light_calculate_percent( &light, light_value );
    
    log_printf( &logger, " Light Intensity : %d \r\n", (uint16_t)light_percent );
    log_printf( &logger, " Light Value     : %d\r\n", light_value );
    Delay_ms( 1000 );

}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
