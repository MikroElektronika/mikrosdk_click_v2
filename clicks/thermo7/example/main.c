/*!
 * \file 
 * \brief Thermo7 Click example
 * 
 * # Description
 * This application reads ambient temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Reads ambient temperature and logs to USBUART every 1 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo7.h"

// ------------------------------------------------------------------ VARIABLES

static thermo7_t thermo7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo7_cfg_t cfg;

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

    thermo7_cfg_setup( &cfg );
    THERMO7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo7_init( &thermo7, &cfg );

    thermo7_set_configuration( &thermo7, THERMO7_CONFIG_COMPARATOR_MODE | THERMO7_CONFIG_ALERT_POLARITY_ACTIVE_HIGH );
    thermo7_set_resolution( &thermo7, THERMO7_CONFIG_ADC_RESOLUTION_12bit );
}

void application_task ( void )
{
    float ambient_temperature;

    ambient_temperature = thermo7_read_ambient_temperature( &thermo7 );
    log_printf( &logger, " Ambient temperature : %f C\r\n", ambient_temperature 
);

    Delay_ms ( 1000 );
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
