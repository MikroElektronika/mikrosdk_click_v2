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
 * Measured temperature and humidity ADC data and calculate temperature data to degrees Celsius [ �C ] and
 * humidity data to percentarg [ % ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "shtan.h"

// ------------------------------------------------------------------ VARIABLES

static shtan_t shtan;
static log_t logger;
uint16_t adc_value;
uint8_t adc_mode;
char demo_text[ 50 ];
char deg_cel[ 4 ];
float temperature;
float humidity;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void shtan_calculate_temperature ( void )
{
    shtan_set_mode ( &shtan, SHTAN_SET_ADC_MODE_TEMP );
    Delay_ms( 100 );

    adc_value = shtan_generic_read( &shtan );

    temperature = ( ( ( ( ( float ) adc_value ) / SHTAN_ADC_RES_12_BIT ) * ( SHTAN_V_REF_2_048_mV / SHTAN_V_DD_3_3_mV ) ) * 218.75 ) -66.875;
}

void shtan_calculate_humidity ( void )
{
    shtan_set_mode ( &shtan, SHTAN_SET_ADC_MODE_HUM );
    Delay_ms( 100 );
    
    adc_value = shtan_generic_read( &shtan );

    humidity = ( ( ( ( ( float ) adc_value ) / SHTAN_ADC_RES_12_BIT ) * ( SHTAN_V_REF_2_048_mV / SHTAN_V_DD_3_3_mV ) ) * 125.0 ) - 12.5;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    shtan_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    shtan_cfg_setup( &cfg );
    SHTAN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    shtan_init( &shtan, &cfg );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "   SHT AN click   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms ( 1100 );

    deg_cel[ 0 ] = 32;
    deg_cel[ 1 ] = 176;
    deg_cel[ 2 ] = 67;
    deg_cel[ 3 ] = 0;

    shtan_reset( &shtan );
    Delay_ms( 1000 );
    shtan_set_mode( &shtan, SHTAN_SET_ADC_MODE_TEMP );
    adc_mode = SHTAN_SET_ADC_MODE_TEMP;
    log_printf( &logger, "  Temp. & Hum.   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 1000 );


}

void application_task ( void )
{
   shtan_calculate_temperature( void );
   log_printf( &logger, "  Temp. : %.2f\r\n", temperature );
   shtan_calculate_humidity( void );
   log_printf( &logger, "  Hum.  : %.2f\r\n", humidity );
   log_printf( &logger, "--------------------------\r\n" );
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
