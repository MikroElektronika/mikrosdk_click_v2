/*!
 * \file 
 * \brief Voltmeter Click example
 * 
 * # Description
 * This application give a voltage in milivolts.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C,
 * start calibration reading and also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Voltmeter Click board.
 * These examples read ADC value from the register of MCP3201 chip on the Voltmeter click board
 * and calculate the voltage value [ mV ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "voltmeter.h"

// ------------------------------------------------------------------ VARIABLES

static voltmeter_t voltmeter;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    voltmeter_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    voltmeter_cfg_setup( &cfg );
    VOLTMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    voltmeter_init( &voltmeter, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, " Initialization  Driver \r\n" );
    log_printf( &logger, "------------------------\r\n" );

    voltmeter_calibration( &voltmeter );
    Delay_ms( 100 );
    log_printf( &logger, " Calibration  completed \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, " Measurement  available \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void )
{
    uint16_t adc_value;
    float voltage;

    adc_value = voltmeter_read_data( &voltmeter );
    log_printf( &logger, " ADC Value: %d\r\n", adc_value );

    voltage = voltmeter_get_voltage( &voltmeter, VOLTMETER_VCC_5V_COEFF_0 );
    log_printf( &logger, " Voltage  : %.2f mV\r\n", voltage );
    log_printf( &logger, "------------------------\r\n");
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
