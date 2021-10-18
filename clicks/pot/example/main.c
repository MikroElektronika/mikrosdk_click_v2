/*!
 * \file 
 * \brief Pot Click example
 * 
 * # Description
 * Click board with the accurate selectable reference voltage output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Performs logger and Click initialization.
 * 
 * ## Application Task  
 * Makes the averaged results by using the desired number of samples of AD conversion.
  The averaged results will be calculated to millivolts [mV] and sent to the uart terminal.
 * 
 * *note:* 
 * The AD conversion will be performed on the analog (AN) pin on the mikrobus 1.
 * 
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pot.h"

// ------------------------------------------------------------------ VARIABLES

static pot_t pot;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pot_cfg_t cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    //  Click initialization.

    pot_cfg_setup( &cfg );
    POT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( pot_init( &pot, &cfg ) == ADC_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done. ----\n" );
}

void application_task ( void )
{
    float an_voltage;

    an_voltage = pot_read_voltage( &pot );

    log_printf( &logger, " AN [V] : %.2f\r\n", an_voltage );
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
