/*!
 * \file 
 * \brief Multimeter Click example
 * 
 * # Description
 * This example showcases how to configure, initialize and use the Multimeter click. The
 * click measures resistance in Ohms, voltage in mVs, current in mAs and capacitance in nFs
 * using a dual CMOS and quad CMOS op-amps, an ADC and other on board modules.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules. Additional 
 * calibration of the measurement components is done in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function measures and displays resistance, voltage, current and capacitance data.
 * It does so every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "multimeter.h"

// ------------------------------------------------------------------ VARIABLES

static multimeter_t multimeter;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    multimeter_cfg_t cfg;

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

    multimeter_cfg_setup( &cfg );
    MULTIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    multimeter_init( &multimeter, &cfg );
    multimeter_default_cfg( &multimeter );
}

void application_task ( )
{
    float resistance;
    float voltage;
    float current;
    float capacitance;

    resistance = multimeter_read_resistance( &multimeter );
    log_printf( &logger, " * Resistance: %.3f Ohms * \r\n", resistance );

    voltage = multimeter_read_voltage( &multimeter );
    log_printf( &logger, " * Voltage: %.3f mV * \r\n", voltage );

    current = multimeter_read_current( &multimeter );
    log_printf( &logger, " * Current: %.3f mA * \r\n", current );

    capacitance = multimeter_read_capacitance( &multimeter );
    log_printf( &logger, " * Capacitance: %.3f nF * \r\n", capacitance );

    log_printf( &logger, "------------------------\r\n" );
    Delay_1sec( );
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
