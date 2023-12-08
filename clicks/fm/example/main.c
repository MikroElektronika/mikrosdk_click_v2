/*!
 * \file 
 * \brief Fm Click example
 * 
 * # Description
 * This click represent FM radio tuner which supports worldwide FM band (76 – 108 MHz)
 * and has a set of features such as automatic frequency and gain control, seek tuning and volume control.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializing I2C driver, powering up device, setting basic settings for Europe, 
 * setting values of seek threshold, volume, snr threshold and impulse detection threshold.
 * Seek and memorize 5 radio stations with a signal strength above the set limit.
 * 
 * ## Application Task  
 * Tunes all memorized stations. Switches the stations each 10 seconds.
 * 
 * ## Additional Functions
 * - void fm_case_plus( fm_t *ctx )      - Increases volume
 * - void fm_case_minus( fm_t *ctx )     - Decreases volume
 * - void fm_case_seek( fm_t *ctx )      - Seeks next station
 * - void fm_case_tune( fm_t *ctx )      - Tunes default station
 * - void fm_case_memorize( )            - Memorizes current station
 * - void fm_case_station1( fm_t *ctx )  - Tunes memorized station 1
 * - void fm_case_station2( fm_t *ctx )  - Tunes memorized station 2
 * - void fm_case_station3( fm_t *ctx )  - Tunes memorized station 3
 * - void fm_case_station4( fm_t *ctx )  - Tunes memorized station 4
 * - void fm_case_station5( fm_t *ctx )  - Tunes memorized station 5
 * - void fm_case_mute( fm_t *ctx )      - Mutes device
 * - void fm_case_tune_up( fm_t *ctx )   - Fine tunes frequency
 * - void fm_case_tune_down( fm_t *ctx ) - Fine tunes frequency
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fm.h"

// ------------------------------------------------------------------ VARIABLES

#define SIGNAL_STRENGTH_LOWER_LIMIT 25

static fm_t fm;
static log_t logger;

static uint16_t received_signal_strength_indicator;
static uint16_t station_channel;
static uint16_t station1;
static uint16_t station2;
static uint16_t station3;
static uint16_t station4;
static uint16_t station5;

static uint8_t memory;
static uint8_t mute;
static uint8_t received_data;
static uint8_t data_ready;
static uint8_t error_flag;
static uint8_t cnt;

static float channel_frequency;
static float tuned_frequency;
static float tune_freq;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void fm_case_plus ( fm_t *ctx  )
{
    error_flag = fm_volume_up( ctx );

    if ( error_flag == 0 )
    {
        log_printf( &logger, "volume up\r\n" );
    }
    else
    {
        log_printf( &logger, "volume max\r\n" );
    }
}

void fm_case_minus ( fm_t *ctx )
{
    error_flag = fm_volume_down( ctx );

    if ( error_flag == 0 )
    {
        log_printf( &logger, "volume down\r\n" );
    }
    else
    {
        log_printf( &logger, "volume min\r\n" );
    }
}

void fm_case_seek ( fm_t *ctx )
{
    fm_seek( ctx );

    Delay_ms( 500 );

    fm_end_seek( ctx );

    Delay_ms( 10 );

    received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
    channel_frequency = fm_get_channel_frequency( ctx );
    station_channel = fm_get_channel( ctx );
}

void fm_case_tune ( fm_t *ctx )
{
    error_flag = fm_tune( ctx, tune_freq );

    Delay_ms( 100 );

    fm_end_tune( ctx );

    Delay_ms( 10 );

    if ( error_flag == 0 )
    {
        received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
        tuned_frequency = fm_get_channel_frequency( ctx );
        station_channel = fm_get_channel( ctx );

        log_printf( &logger, "tune complete\r\n" );

        log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

        log_printf( &logger, "tuned frequency: %.2f MHz\r\n", tuned_frequency );
        log_printf( &logger, "-----------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "frequency not in valid range\r\n" );
    }
}

void fm_case_memorize ( )
{
    switch ( memory )
    {
        case 0 :
        {
            station1 = station_channel;
            memory += 1;

            log_printf( &logger, "station 1 memorized\r\n" );

            break;
        }
        case 1 :
        {
            station2 = station_channel;
            memory += 1;

            log_printf( &logger, "station 2 memorized\r\n" );

            break;
        }
        case 2 :
        {
            station3 = station_channel;
            memory += 1;

            log_printf( &logger, "station 3 memorized\r\n" );
            
            break;
        }
        case 3 :
        {
            station4 = station_channel;
            memory += 1;

            log_printf( &logger, "station 4 memorized\r\n" );

            break;
        }
        case 4 :
        {
            station5 = station_channel;
            memory = 0;

            log_printf( &logger, "station 5 memorized\r\n" );

            break;
        }
        default :
        {
            break;
        }
    }
}

void fm_case_mute ( fm_t *ctx )
{
    if ( mute == 0 )
    {
        fm_mute_enable( ctx );

        log_printf( &logger, "mute enabled\r\n" );

        mute = 1;
    }
    else if ( mute == 1 )
    {
        fm_mute_disable( ctx );

        log_printf( &logger, "mute disabled\r\n" );

        mute = 0;
    }
}

void fm_case_station_1 ( fm_t *ctx  )
{
    fm_tune_channel( ctx, station1 );

    Delay_ms( 100 );

    fm_end_tune( ctx );

    Delay_ms( 10 );

    received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
    channel_frequency = fm_get_channel_frequency( ctx );

    log_printf( &logger, "station 1 tuned\r\n" );

    log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

    log_printf( &logger, "tuned frequency: %.2f MHz\r\n", channel_frequency );
    log_printf( &logger, "-----------------------\r\n" );
}

void fm_case_station_2 ( fm_t *ctx )
{
    fm_tune_channel( ctx, station2 );

    Delay_ms( 100 );

    fm_end_tune( ctx );

    Delay_ms( 10 );

    received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
    channel_frequency = fm_get_channel_frequency( ctx );

    log_printf( &logger, "station 2 tuned\r\n" );

    log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

    log_printf( &logger, "tuned frequency: %.2f MHz\r\n", channel_frequency );
    log_printf( &logger, "-----------------------\r\n" );
}

void fm_case_station_3 ( fm_t *ctx )
{
    fm_tune_channel( ctx, station3 );

    Delay_ms( 100 );

    fm_end_tune( ctx );

    Delay_ms( 10 );

    received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
    channel_frequency = fm_get_channel_frequency( ctx );

    log_printf( &logger, "station 3 tuned\r\n" );

    log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

    log_printf( &logger, "tuned frequency: %.2f MHz\r\n", channel_frequency );
    log_printf( &logger, "-----------------------\r\n" );
}

void fm_case_station_4 ( fm_t *ctx )
{
    fm_tune_channel( ctx, station4 );

    Delay_ms( 100 );

    fm_end_tune( ctx );

    Delay_ms( 10 );

    received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
    channel_frequency = fm_get_channel_frequency( ctx );

    log_printf( &logger, "station 4 tuned\r\n" );

    log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

    log_printf( &logger, "tuned frequency: %.2f MHz\r\n", channel_frequency );
    log_printf( &logger, "-----------------------\r\n" );
}

void fm_case_station_5 ( fm_t *ctx )
{
    fm_tune_channel( ctx, station5 );

    Delay_ms( 100 );

    fm_end_tune( ctx );

    Delay_ms( 10 );

    received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
    channel_frequency = fm_get_channel_frequency( ctx );

    log_printf( &logger, "station 5 tuned\r\n" );

    log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

    log_printf( &logger, "tuned frequency: %.2f MHz\r\n", channel_frequency );
    log_printf( &logger, "-----------------------\r\n" );
}

void fm_case_tune_up ( fm_t *ctx )
{
    error_flag = fm_fine_tune_up( ctx );

    if ( error_flag == 0 )
    {
        Delay_ms( 100 );

        fm_end_tune( ctx );

        Delay_ms( 10 );
        
        received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
        channel_frequency = fm_get_channel_frequency( ctx );
        station_channel = fm_get_channel( ctx ); 

        log_printf( &logger, "tune up\r\n" );

        log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

        log_printf( &logger, "tuned frequency: %.2f MHz\r\n", channel_frequency );
        log_printf( &logger, "-----------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "upper band limit reached\r\n" );
    }
}

void fm_case_tune_down ( fm_t *ctx )
{
    error_flag = fm_fine_tune_down( ctx );

    if ( error_flag == 0 )
    {
        Delay_ms( 100 );

        fm_end_tune( ctx );

        Delay_ms( 10 );
    
        received_signal_strength_indicator = fm_get_received_signal_strength_indicator( ctx );
        channel_frequency = fm_get_channel_frequency( ctx );
        station_channel = fm_get_channel( ctx );

        log_printf( &logger, "tune down\r\n" );

        log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );

        log_printf( &logger, "tuned frequency: %.2f MHz\r\n", channel_frequency );
        log_printf( &logger, "-----------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "lower band limit reached\r\n" );
    }
}

void fm_case_wrong_command ( )
{
    log_printf( &logger, "wrong command\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fm_cfg_t cfg;

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

    fm_cfg_setup( &cfg );
    FM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fm_init( &fm, &cfg );
    
    Delay_ms( 500 );
    fm_default_cfg( &fm );

    memory = 0;
    mute = 0;
    fm_case_mute( &fm );
     
    for ( cnt = 0; cnt < 5;  )
    {
        log_printf( &logger, "seeking...\r\n" );
        do 
        {
            received_signal_strength_indicator = 0;
            fm_case_seek( &fm );
        }
        while ( received_signal_strength_indicator < SIGNAL_STRENGTH_LOWER_LIMIT ); //rssi value
        
        log_printf( &logger, "station found\r\n" );
        log_printf( &logger, "rssi: %u dBuV\r\n", received_signal_strength_indicator );
        log_printf( &logger, "channel frequency: %.2f MHz\r\n", channel_frequency );
        fm_case_memorize( );
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms( 100 );
        cnt++;
    }  
    
    mute = 1;
    fm_case_mute( &fm );
    log_printf( &logger, "playing memorized stations...\r\n\r\n" );
}

void application_task ( void )
{ 
    fm_case_station_1( &fm );
    Delay_ms( 10000 );
       
    fm_case_station_2( &fm );
    Delay_ms( 10000 );
    
    fm_case_station_3( &fm );
    Delay_ms( 10000 );
    
    fm_case_station_4( &fm );
    Delay_ms( 10000 );
    
    fm_case_station_5( &fm );
    Delay_ms( 10000 );
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
