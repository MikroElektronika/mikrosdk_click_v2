/*!
 * \file 
 * \brief Ambient Click example
 * 
 * # Description
 * This application turns light intensity into voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver and logger.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Ambient click board.
 * Ambient click reads ADC voltage once per second and converts it to light intensity [ uW/cm2 ].
 * Results are being sent to the USB UART where you can track their changes.
 *
 * \author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "ambient.h"

static ambient_t ambient;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    ambient_cfg_setup( &cfg );
    AMBIENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient_init( &ambient, &cfg );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t light_intensity = ambient_get_light_intensity( &ambient );
    log_printf( &logger, " Light Intensity: %u uW/cm2\r\n\n", light_intensity );
    Delay_ms( 1000 );
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
