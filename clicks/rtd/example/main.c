/*!
 * \file 
 * \brief Rtd Click example
 * 
 * # Description
 * This app measures temperature and converts the data to celsius degrees.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes RTD click driver, and sets the
 * proper configuration mode for three wire RTD.
 * 
 * ## Application Task  
 * Measures temperature, converts the data to celsius degrees,
 * and displays it on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtd.h"

// ------------------------------------------------------------------ VARIABLES

static rtd_t rtd;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtd_cfg_t cfg;

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
    rtd_cfg_setup( &cfg );
    RTD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtd_init( &rtd, &cfg );
    
    RTD_SET_DATA_SAMPLE_EDGE;

    rtd_write_register( &rtd, RTD_CONFIGURATION, 0xD0 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t read_value = 0;
    float converted_value = 0;

    read_value = rtd_read_temperature( &rtd );
    converted_value = rtd_convert_temperature( &rtd, read_value, RTD_REF_RESISTANCE_470 );

    log_printf( &logger, " Current temperature: %.2f \r\n", converted_value );

    Delay_ms ( 300 );
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
