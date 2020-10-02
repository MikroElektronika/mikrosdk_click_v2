/*!
 * \file 
 * \brief Dac5 Click example
 * 
 * # Description
 *
 * This demo example sends digital signal to one of the outputs and converts it to analog
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver init, tests communication and configures device for measureing
 *
 * ## Application Task
 * Sends 4 different values to one output and prints expected measurement
 *
 * *note:*
 * Values that are tested and expected are values for Vref on 2.048
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac5.h"

// ------------------------------------------------------------------ VARIABLES

static dac5_t dac5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dac5_cfg_setup( &cfg );
    DAC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac5_init( &dac5, &cfg );

    if ( dac5_get_device_id( &dac5 ) == DAC5_DEVICE_ID )
    {
        log_printf( &logger,"DEVICE READY\r\n" );
    }
    else
    {
        log_printf( &logger, "DEVICE NOT READY\r\n" );
        for ( ; ; );
    }

    dac5_config( &dac5, DAC5_CONFIG_GLOBAL_ENABLED );
    log_printf( &logger, "CONFIGURATION COMPLETE\r\n" );

    log_printf( &logger, "***** APP INIT *****\r\n" );
    log_printf( &logger, "_________________________________________\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint16_t sender[ 4 ] = { 0x0118, 0x0FF0, 0x0AAC, 0x0DD4 };
    uint16_t expected[ 4 ] = { 140, 2030, 1360, 1760 };
    uint8_t end_count = 4;
    uint8_t cnt;

    for ( cnt = 0; cnt < end_count; cnt++ )
    {
        if ( dac5_send_data( &dac5, DAC5_REG_DAC_H_DATA, sender[ cnt ] ) == DAC5_ERROR )
        {
            log_printf( &logger, "-ERROR SENDING DATA\r\n" );
        }
        else
        {
            log_printf( &logger, "Sending : %#06X\r\n", sender[ cnt ] );
            log_printf( &logger, "Expected return around : %d mV\r\n", expected[ cnt ] );
        }
        Delay_ms ( 5000 );
        dac5_clear( &dac5 );
        log_printf( &logger,"Clearing output...\r\n" );
        log_printf( &logger,"...........................................\r\n" );
        Delay_ms ( 2000 );
    }

    log_printf( &logger,"___________________________________________________\r\n" );

    Delay_ms ( 1000 );
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
