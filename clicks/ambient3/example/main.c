/*!
 * \file 
 * \brief Ambient3 Click example
 * 
 * # Description
 * This example demonstrates the use of Ambient 3 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger.
 * 
 * ## Application Task  
 * Reads the device temperature, and daylight in LUX and logs results to USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient3.h"

// ------------------------------------------------------------------ VARIABLES

static ambient3_t ambient3;
static log_t logger;

static uint8_t temperature;
static uint16_t data_lux;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient3_cfg_t cfg;

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

    ambient3_cfg_setup( &cfg );
    AMBIENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient3_init( &ambient3, &cfg );
    ambient3_default_cfg( &ambient3 );
    Delay_ms( 100 );
}

void application_task ( )
{
    temperature = ambient3_get_device_temperature( &ambient3 );
    log_printf( &logger, " - Device temperature in Celsius : %u\r\n", ( uint16_t ) temperature );

    data_lux = ambient3_get_data_in_lux( &ambient3 );
    log_printf( &logger, " - Light in LUX : %u\r\n", data_lux );
    log_printf( &logger, " --------------------\r\n" );
    
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
