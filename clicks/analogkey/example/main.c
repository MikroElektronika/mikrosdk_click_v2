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
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "analogkey.h"

#define ANALOGKEY_N_SAMPLES  50

// ------------------------------------------------------------------ VARIABLES

static analogkey_t analogkey;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    analogkey_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init... ----" );

    analogkey_cfg_setup( &cfg );
    ANALOGKEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( analogkey_init( &analogkey, &cfg ) == ADC_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done. ----\n" );
}

void application_task ( void )
{
    float an_voltage = 0;
    analogkey_key_id_t key;
    float an_average = 0;
    
    an_voltage = analogkey_read_voltage( &analogkey );
    
    if ( an_voltage > 0.2 )
    {
        an_average += an_voltage / ANALOGKEY_N_SAMPLES;
        for ( uint8_t cnt = 0; cnt < ANALOGKEY_N_SAMPLES - 1; cnt++ )
        {
            an_voltage = analogkey_read_voltage( &analogkey );
        
            an_average += an_voltage / ANALOGKEY_N_SAMPLES;
        }
    }
    
    if ( ( key = analogkey_get_key( &analogkey, an_average ) ) != ANALOGKEY_TOUCH_KEY_NONE )
    {
        log_printf( &logger, " T%u is pressed.\r\n", (uint16_t)key );
        
        while ( analogkey_read_voltage( &analogkey ) > 0.2 ) {
             Delay_ms( 1 );   
        }
    
        log_printf( &logger, " T%u is released.\r\n", (uint16_t)key );
        Delay_ms( 10 );
    }
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
