/*!
 * \file 
 * \brief Buck12 Click example
 * 
 * # Description
 * This demo application reads the voltage in [mV] at the input and output terminals.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Reads the voltage in [mV] at the input and output terminals.
 * This data logs to the USBUART every 2 sec.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck12.h"

// ------------------------------------------------------------------ VARIABLES

static buck12_t buck12;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck12_cfg_t cfg;

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

    buck12_cfg_setup( &cfg );
    BUCK12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck12_init( &buck12, &cfg );

    buck12_control( &buck12, BUCK12_ENABLE );
    Delay_ms( 2000 );
}

void application_task ( void )
{
    float voltage;

    voltage = buck12_get_voltage( &buck12, BUCK12_INPUT_VOLTAGE );
    
    log_printf( &logger, "* Vin : %f mV \r\n ", voltage);
    voltage = buck12_get_voltage( &buck12, BUCK12_OUTPUT_VOLTAGE );

    log_printf( &logger, "* Vout : %f mV \r\n ", voltage);
    log_printf( &logger, "--------------------------\r\n");
    Delay_ms( 2000 );
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
