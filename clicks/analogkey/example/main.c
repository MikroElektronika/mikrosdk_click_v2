/*!
 * \file 
 * \brief AnalogKey Click example
 * 
 * # Description
 * This application logs what button is pressed.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads ADC value and detects which button is pressed based on that value.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "analogkey.h"

// ------------------------------------------------------------------ VARIABLES

static analogkey_t analogkey;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    analogkey_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    analogkey_cfg_setup( &cfg );
    ANALOGKEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    analogkey_set_resolution( &analogkey, ANALOGKEY_ADC_RESOLUTION_12bit );
    
    analogkey_init( &analogkey, &cfg );
    Delay_ms( 100 );

    log_printf(&logger, " Press the button :D\r\n ");

}

void application_task ( void )
{
    uint16_t adc_value;
    uint8_t is_key;
    uint8_t cnt;
    uint16_t sum_value = 0;
    
    for ( cnt = 0; cnt < 5; cnt++ )
    {
        adc_value = analogkey_generic_read( &analogkey );
        sum_value += adc_value;
        Delay_ms( 10 );
    }
    adc_value = sum_value / 5;
    is_key = analogkey_get_key( &analogkey ,adc_value );

    if ( is_key != ANALOGKEY_NO_TOUCH )
    {
        log_printf( &logger, "Pressed the button: %d\r\n", is_key );
    }
    Delay_ms( 300 );
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
