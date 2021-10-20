/*!
 * \file 
 * \brief ShtAn Click example
 * 
 * # Description
 * This app demonstrates the use of SHT AN click to measure temperature and humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init
 * Initialization driver enables - GPIO, sw reset,
 * initializes ADC, set ADC channel and sets ADC read mode.
 * 
 * ## Application Task
 * This is a example which demonstrates the use of SHT AN Click board.
 * Measured temperature and humidity ADC data and calculate temperature data to degrees
 * Celsius/Fahrenheit and relative humidity data to percentage.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 1 sec.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "shtan.h"

// ------------------------------------------------------------------ VARIABLES

static shtan_t shtan;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    shtan_cfg_t cfg;

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

    shtan_cfg_setup( &cfg );
    SHTAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    if ( shtan_init( &shtan, &cfg ) == ADC_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );

    shtan_reset( &shtan );

    log_info( &logger, "---- Application Running... ----\n" );
}

void application_task ( void )
{
    shtan_set_mode( &shtan, SHTAN_SET_ADC_MODE_TEMP );
    Delay_ms( 200 );

    float shtan_temperature;

    if ( shtan_meas_temperature( &shtan, &shtan_temperature, SHTAN_SET_TEMP_MODE_DEG_C ) != ADC_ERROR )
    {
        log_printf( &logger, "  Temp [T] : %.2f degC\r\n", shtan_temperature );
    }

    shtan_set_mode( &shtan, SHTAN_SET_ADC_MODE_HUM );
    Delay_ms( 200 );

    float shtan_humidity;

    if ( shtan_meas_humidity( &shtan, &shtan_humidity ) != ADC_ERROR )
    {
        log_printf( &logger, "  Hum [RH] : %.2f %%\r\n", shtan_humidity );
    }

    log_printf( &logger, "\n" );
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
