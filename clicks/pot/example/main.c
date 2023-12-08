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
 * Reads and displays on the USB UART the voltage level measured from AN pin.
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
    log_cfg_t log_cfg;  /**< Logger config object. */
    pot_cfg_t pot_cfg;  /**< Click config object. */

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
    pot_cfg_setup( &pot_cfg );
    POT_MAP_MIKROBUS( pot_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == pot_init( &pot, &pot_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    if ( POT_OK == pot_read_an_pin_voltage ( &pot, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms( 1000 );
    }
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
