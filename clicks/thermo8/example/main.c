/*!
 * \file 
 * \brief Thermo8 Click example
 * 
 * # Description
 * This application measures temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize device.
 * 
 * ## Application Task  
 * Wait for the interrupt pin to be triggered. When the
 * measured temperature breaches the upper or lower limit the
 * temperature value as well as the status of the breach is
 * is shown on the serial port (UART).
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo8.h"

// ------------------------------------------------------------------ VARIABLES

static thermo8_t thermo8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo8_cfg_t cfg;

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

    thermo8_cfg_setup( &cfg );
    THERMO8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo8_init( &thermo8, &cfg );
    
    Delay_ms ( 100 );
    thermo8_default_cfg( &thermo8 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    float t_data;
    char alert;
    char alert_on;

    alert = thermo8_ale_get( &thermo8 );

    if ( alert == 0 )
    {
        t_data  = thermo8_get_temperature( &thermo8 );
        alert_on = thermo8_get_alert_stat( &thermo8 );
    }

    if ( alert_on & THERMO8_TLOWER_REACHED )
    {
        log_printf( &logger, "Temperature under the low limit: %.2f C \r\n", 
t_data );
    }

    if ( alert_on & THERMO8_TUPPER_REACHED )
    {
        log_printf( &logger, "Temperature over the high limit: %.2f C \r\n", 
t_data );
    }
    Delay_ms ( 1000 );
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
