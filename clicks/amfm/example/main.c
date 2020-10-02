/*!
 * \file 
 * \brief AmFm Click example
 * 
 * # Description
 * This app simulate RADIO RECEIVER.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Several additional functions are executed and printed over the terminal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "amfm.h"

// ------------------------------------------------------------------ VARIABLES

static amfm_t amfm;
static log_t logger;

float aux;
uint8_t volume = 0x3F;
uint8_t mute_flag = 0;
uint8_t status;
uint16_t station_1 = 0;
uint16_t station_2 = 0;
uint16_t station_3 = 0;
uint16_t station_4 = 0;
uint16_t station_5 = 0;
uint16_t station_frequency = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void amfm_case_memorize ( )
{
    uint8_t memory = 0;

    switch ( memory )
    {
        case 0 :
        {
            station_1 = station_frequency;
            memory += 1;
            log_printf( &logger, "> > > station 1 memorized\r\n" );
            break;
        }
        case 1 :
        {
            station_2 = station_frequency;
            memory += 1;
            log_printf( &logger, "> > > station 2 memorized\r\n" );
            break;
        }
        case 2 :
        {
            station_3 = station_frequency;
            memory += 1;
            log_printf( &logger, "> > > station 3 memorized\r\n" );
            break;
        }
        case 3 :
        {
            station_4 = station_frequency;
            memory += 1;
            log_printf( &logger, "> > > station 4 memorized\r\n" );
            break;
        }
        case 4 :
        {
            station_5 = station_frequency;
            memory = 0;
            log_printf( &logger, "> > > station 5 memorized\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
}

void amfm_case_station_1 ( amfm_t *ctx )
{
    log_printf( &logger, "> > > tune station 1 \r\n" );
    amfm_tune_frequency( ctx, station_1 );
    log_printf( &logger, "> > > tune done \r\n" );
    aux = station_1 / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

void amfm_case_station_2 ( amfm_t *ctx )
{
    log_printf( &logger, "> > > tune station 2 \r\n" );
    amfm_tune_frequency( ctx, station_2 );
    log_printf( &logger, "> > > tune done \r\n" );
    aux = station_2 / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

void amfm_case_station_3 ( amfm_t *ctx )
{
    log_printf( &logger, "> > > tune station 3 \r\n" );
    amfm_tune_frequency( ctx, station_3 );
    log_printf( &logger, "> > > tune done \r\n" );
    aux = station_3 / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

void amfm_case_station_4 ( amfm_t *ctx )
{
    log_printf( &logger, "> > > tune station 4 \r\n" );
    amfm_tune_frequency( ctx, station_4 );
    log_printf( &logger, "> > > tune done \r\n" );
    aux = station_4 / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

void amfm_case_station_5 ( amfm_t *ctx )
{
    log_printf( &logger, "> > > tune station 5 \r\n" );
    amfm_tune_frequency( ctx, station_5 );
    log_printf( &logger, "> > > tune done \r\n" );
    aux = station_5 / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

void amfm_case_seek ( amfm_t *ctx )
{
    log_printf( &logger, "> > > seek \r\n" );
    amfm_seek( ctx );
    log_printf( &logger, "> > > seek done \r\n" );
    station_frequency =  amfm_get_channel( ctx );
    aux = station_frequency / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

void amfm_case_plus ( amfm_t *ctx )
{
    if ( volume < 63 )
    {
        volume += 1;
        amfm_set_volume( ctx, volume );
        log_printf( &logger, "> > > volume: %u \r\n", volume );
    }
    else
    {
        log_printf( &logger, "> > > volume: MAX \r\n" );
    }
}

void amfm_case_minus ( amfm_t *ctx )
{
    if ( volume > 0 )
    {
        volume -= 1;
        amfm_set_volume( ctx, volume );
        log_printf( &logger, "> > > volume: %u \r\n", volume );
    }
    else
    {
        log_printf( &logger, "> > > volume: MIN \r\n" );
    }
}

void amfm_case_mute ( amfm_t *ctx )
{
    if ( mute_flag == 0 )
    {
        amfm_mute( ctx );
        log_printf( &logger, "> > > mute ON \r\n" );
        mute_flag = 1;
    }
    else
    {
        amfm_unmute( ctx );
        log_printf( &logger, "> > > mute OFF \r\n" );
        mute_flag = 0;
    }
}

void amfm_case_tune_up ( amfm_t *ctx )
{
    amfm_tune_up( ctx );
    station_frequency = amfm_get_channel( ctx );
    aux = station_frequency / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

void amfm_case_tune_down ( amfm_t *ctx )
{
    amfm_tune_down( ctx );
    station_frequency = amfm_get_channel( ctx );
    aux = station_frequency / 100.0;
    log_printf( &logger, "> > > frequency: %f MHz \r\n", aux );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    amfm_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    amfm_cfg_setup( &cfg );
    AMFM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    amfm_init( &amfm, &cfg );

    Delay_ms( 100 );
    status = amfm_init_device( &amfm );
    if ( status == 0 )
    {
        log_printf( &logger, "> > > app init done < < <\r\n" );
    }
    else if ( status == 1 )
    {
        log_printf( &logger, "> > >    timeout    < < <\r\n" );
    }
}

void application_task ( void )
{
    amfm_case_seek( &amfm );
    Delay_ms( 500 );
    amfm_case_memorize( );
    Delay_ms( 500 );
    amfm_case_plus( &amfm );
    Delay_ms( 500 );
    
    for ( ; ; )
    {
        amfm_case_station_1( &amfm );
        Delay_ms( 10000 );
    }
    
    Delay_ms( 2000 );
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
