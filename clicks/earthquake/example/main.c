/*!
 * \file 
 * \brief Earthquake Click example
 * 
 * # Description
 * Intializes I2C module, LOG and GPIO structure, sets INT and PWM pins as 
 * input and sets CS pin as output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Intializes of I2C driver and makes initial log.
 * 
 * ## Application Task  
 * This is an example that shows most of the functions that Earthquake click
 * has. Results are being sent to the Usart Terminal where you can track their 
 * changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "earthquake.h"

// ------------------------------------------------------------------ VARIABLES

static earthquake_t earthquake;
static log_t logger;
uint16_t read_data;
uint8_t cnt;

void display_status( uint8_t status_data )
{
    if ( status_data == EARTHQUAKE_STANDBY_MODE )
    {
        log_printf( &logger, "Standby  Mode \r\n" );
    }

    if ( status_data == EARTHQUAKE_NORMAL_MODE )
    {
        log_printf( &logger, "Normal Mode \r\n" );
    }
    
    if ( status_data == EARTHQUAKE_INIT_INST )
    {
        log_printf( &logger, "Initial Installation Mode \r\n" );
    }
    
    if ( status_data == EARTHQUAKE_OFFSET_ACQ )
    {
        log_printf( &logger, "Offset Acquisition Mode \r\n" );
    }
    
    if ( status_data == EARTHQUAKE_SELF_DIAGNOSTIC )
    {
        log_printf( &logger, "Self-Diagnostic Mode \r\n" );
    }
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    earthquake_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    earthquake_cfg_setup( &cfg );
    EARTHQUAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    earthquake_init( &earthquake, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "    Earthquake Click    \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void )
{
    if ( earthquake_proc_notify( &earthquake ) )
    {
        log_printf( &logger, "  Earthquake detected!  \r\n" );
        log_printf( &logger, "------------------------\r\n" );
        Delay_ms ( 2000 );

        for ( cnt = 20; cnt > 0; cnt-- )
        {
            log_printf( &logger, " Status : " );
            display_status( earthquake_read_status( &earthquake ) );

            read_data = earthquake_read_si( &earthquake );
            log_printf( &logger, " Max SI : %5d\r\n", read_data );
            log_printf( &logger, "------------------------ \r\n" );
            Delay_ms( 5000 );
        }

        earthquake_clear_mememory( &earthquake );
        log_printf( &logger, " Afterquake  processing \r\n" );
        log_printf( &logger, "     please wait...     \r\n" );
        Delay_ms( 20000 );

        log_printf( &logger, "------------------------\r\n" );
        log_printf( &logger, " Waiting for a quake... \r\n" );
        log_printf( &logger, "------------------------\r\n" );
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
