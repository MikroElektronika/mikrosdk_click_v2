/*!
 * \file 
 * \brief Leddriver6 Click example
 * 
 * # Description
 * This application designed to be used in tunable Smart Connected Lighting applications.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and pwm init for LED.
 * 
 * ## Application Task  
 * Waits for valid user input and executes functions based on set of valid commands.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver6.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver6_t leddriver6;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void increase ( )
{
    uint16_t maxLED_750mA = 1;
    
    duty_cycle += 0.1;
    if ( duty_cycle > maxLED_750mA )
    {
        duty_cycle = maxLED_750mA;
        log_printf( &logger, ">>> LED Maximum \r\n" );
    }
    log_printf( &logger, ">>> LED Increase \r\n" );
    leddriver6_set_duty_cycle( &leddriver6, duty_cycle );
}

static void decrease ( )
{
    if ( duty_cycle <= 0.1 )
    {
        duty_cycle = 0;
        log_printf( &logger, ">>> LED OFF \r\n" );
    }
    else
    {
        duty_cycle -= 0.1;
    }
    log_printf( &logger, ">>> LED Decrease \r\n" );
    leddriver6_set_duty_cycle( &leddriver6, duty_cycle );
}

static void current_pg_voltage ( )
{
    uint16_t pg_volt;
    char demo_text[ 20 ];

    pg_volt = leddriver6_get_pg_voltage(  &leddriver6 );
    
    log_printf( &logger, ">>> PG Voltage: %d \r\n", pg_volt );
    
    log_printf( &logger, " mV  \r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver6_cfg_setup( &cfg );
    LEDDRIVER6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver6_init( &leddriver6, &cfg );

    leddriver6_pwm_start( &leddriver6 );
}

void application_task ( void )
{
    uint8_t cnt;

    if ( duty_cycle > 1 )
    {
        duty_cycle = 0.5;
    }
    
    leddriver6_set_duty_cycle ( &leddriver6, duty_cycle );
    duty_cycle += 0.5;
    Delay_100ms( );
    
    increase( );
    Delay_10ms( );
    decrease( );
    Delay_10ms( );
    current_pg_voltage( );

    for( cnt = 0; cnt < 5; cnt++ )
    {
        increase( );
        Delay_10ms( );
    }
    for( cnt = 0; cnt < 3; cnt++ )
    {
        decrease( );
        Delay_10ms( );
    }
    current_pg_voltage( );

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
