/*!
 * \file 
 * \brief Pressure2 Click example
 * 
 * # Description
 * This application measures pressure in range from 0 to 14 bars
 * (with a resolution of up to 0.2 mbars), but because of the stainless
 * steel cap enclosure, the sensor can withstand up to 30 bars of pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and chip init.
 * 
 * ## Application Task  
 * Reads sensor and logs to USB UART pressure and temperature every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure2.h"

// ------------------------------------------------------------------ VARIABLES

static pressure2_t pressure2;
static log_t logger;

static float pressure;
static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure2_cfg_t pressure2_cfg;

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
    pressure2_cfg_setup( &pressure2_cfg );
    PRESSURE2_MAP_MIKROBUS( pressure2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pressure2_init( &pressure2, &pressure2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE2_ERROR == pressure2_default_cfg ( &pressure2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    pressure2_read_sensor( &pressure2, &pressure, &temperature );
    
    log_printf( &logger," Pressure: %.2f mBar\r\n", pressure );
    log_printf( &logger," Temperature: %.2f degC\r\n\n", temperature );

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
