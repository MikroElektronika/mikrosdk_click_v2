/*!
 * \file 
 * \brief DigiVref Click example
 * 
 * # Description
 * This app changes the reference output voltage. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * Changes the reference output voltage every 3 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digivref.h"

// ------------------------------------------------------------------ VARIABLES

static digivref_t digivref;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    digivref_cfg_t cfg;

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

    digivref_cfg_setup( &cfg );
    DIGIVREF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digivref_init( &digivref, &cfg );
}

void application_task ( void )
{
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_4096mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage(  &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_1024mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms( 3000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
    Delay_ms( 3000 );
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
