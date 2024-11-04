/*!
 * \file
 * \brief R Meter Click example
 *
 * # Description
 * Demo app measures and displays resistance of a resistor connected 
 * to the R Meter Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes SPI serial communication, LOG module and Click driver.
 * Also sets the app callback handler.
 *
 * ## Application Task
 * This is an example that shows the capabilities of the R Meter Click by 
 * measuring the target resistance.
 *
 * *note:*
 * R Meter Click is a handy tool but it is not to be used as a high precision 
 * instrument! The linearity of the OP Amplifier impacts the measurement.
 * The range of resistance measurement goes from 1 ohm to 1M9 ohms.
 *
 * \author Nemanja Medakovic
 *
 */

#include "board.h"
#include "log.h"
#include "rmeter.h"

static rmeter_t rmeter;
static log_t logger;

void application_callback ( char *message )
{
    log_printf( &logger, "- %s\r\n", message );
}

void application_init ( void )
{
    log_cfg_t log_cfg;

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

    rmeter_cfg_t rmeter_cfg;

    //  Click initialization.

    rmeter_cfg_setup( &rmeter_cfg );
    RMETER_MAP_MIKROBUS( rmeter_cfg, MIKROBUS_1 );

    if ( rmeter_init( &rmeter, &rmeter_cfg ) == RMETER_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    rmeter_set_callback_handler( &rmeter, application_callback );

    log_info( &logger, "---- Application Init Done. ----\n" );
}

void application_task ( void )
{
    uint16_t meas_value = rmeter_auto_scale_range_execution( &rmeter );

    float res_value;

    if ( rmeter_calculate_resistance( &rmeter, &res_value, meas_value ) == RMETER_OK )
    {
        log_printf( &logger, "  - Resistor value is %.1f ohms\r\n\n", res_value );
    }

    Delay_ms ( 1000 );
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
