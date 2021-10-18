/*!
 * \file 
 * \brief BUCK7 Click example
 * 
 * # Description
 * This demo application controls the voltage at the output using the BUCK 7 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init, reset chip, enable chip and set mode
 * 
 * ## Application Task  
 * Sets output voltage to 5V, 10V, 15V, 20V, 25V every 3 seconds.
 * It is necessary to set the input voltage on 2.7V + maximum output voltage.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck7.h"

// ------------------------------------------------------------------ VARIABLES

static buck7_t buck7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck7_cfg_t cfg;

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

    buck7_cfg_setup( &cfg );
    BUCK7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck7_init( &buck7, &cfg );

    buck7_enable( &buck7 );
    buck7_set_mode( &buck7, BUCK7_MODE_PWM );
}

void application_task ( )
{
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_5V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_10V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_15V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_20V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_25V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_20V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_15V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, 0x0BB8 ); 
    Delay_ms( 3000 );
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
