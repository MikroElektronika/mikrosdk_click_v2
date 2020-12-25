/*!
 * \file 
 * \brief Waveform Click example
 * 
 * # Description
 * This program outputs wave forms.
 *
 * The application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize the communication interface and configure the click board.
 * 
 * ## Application Task  
 * Predefined characters are inputed from the serial port.
 * Depending on the character sent the signal frequency, waveform or amplitude 
 * will be changed.
 * 
 * ## Additional Functions
 * uint32_t waveform_aprox_freqcalculation ( float freqency ) - This function is used
 * to calculate the aproximate value that will be written to the frequency set
 * register.
 * 
 * void output_waveform ( uint32_t frequency_temp, uint8_t output_mode ) - This function 
 * checks which wave form has been chosen and sets frequency of the wave.
 * 
 * void frequency_increment ( uint8_t output_mode ) - This function increases frequency 
 * of the wave.
 * 
 * void frequency_decrement ( uint8_t output_mode ) - This function reduces frequency
 * of the wave.
 * 
 * \author MikroE Team 
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "waveform.h"

// ------------------------------------------------------------------ VARIABLES

static waveform_t waveform;
static log_t logger;

static uint32_t freq;
static char rx_data_buffer[ 2 ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

uint32_t waveform_aprox_freqcalculation ( float freqency )
{
    uint32_t calculation;
    float waveform_osc_freq = 25000000.0;
    float waveform_constant = 268435456.0; // 2^28
    
    calculation = freqency * ( waveform_constant / waveform_osc_freq );
    
    return calculation;
}

void output_waveform ( uint32_t frequency_temp, uint8_t output_mode )
{
    if ( output_mode == WAVEFORM_SINE_OUT )
    {
        waveform_sine_output( &waveform, frequency_temp );
    }
    else if ( output_mode == WAVEFORM_TRIANGLE_OUT )
    {
        waveform_triangle_output( &waveform, frequency_temp );
    }
    else if ( output_mode == WAVEFORM_SQUARE_OUT )
    {
        waveform_square_output( &waveform, frequency_temp );
    }
}

void frequency_increment ( uint8_t output_mode )
{
    uint32_t frequency_temp;
    freq += 1;
    frequency_temp = freq << 14;
    output_waveform( frequency_temp, output_mode );
}

void frequency_decrement ( uint8_t output_mode )
{
    uint32_t frequency_temp;
    if ( freq > 1 )
    {
        freq -= 1;
    }
    frequency_temp = freq << 14;
    output_waveform( frequency_temp, output_mode );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    waveform_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    waveform_cfg_setup( &cfg );
    WAVEFORM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    waveform_init( &waveform, &cfg );

    freq = waveform_aprox_freqcalculation( 5000 );
    waveform_square_output( &waveform, freq );
    freq = 1;
}

void application_task ( )
{
    uint8_t rx_len = log_read ( &logger, rx_data_buffer, 1 );
    
    if ( rx_len > 0 ) 
    {
       switch( rx_data_buffer[ 0 ] )
       {
           case '+': {
                            waveform_digipot_inc( &waveform );
                            log_printf( &logger, "Increasing amplitude of the current wave.\r\n" );
                            break;
                        }
           case '-': {
                            waveform_digipot_dec( &waveform );
                            log_printf( &logger, "Decreasing amplitude of the current wave.\r\n" );
                            break;
                        }
           case 'S': {
                            frequency_increment( WAVEFORM_SINE_OUT );
                            log_printf( &logger, "Increasing frequency of the sine wave.\r\n" );
                            break;
                        }
           case 's': {
                            frequency_decrement( WAVEFORM_SINE_OUT );
                            log_printf( &logger, "Decreasing frequency of the sine wave.\r\n" );
                            break;
                        }
           case 'T': {
                            frequency_increment( WAVEFORM_TRIANGLE_OUT );
                            log_printf( &logger, "Increasing frequency of the triangle wave.\r\n" );
                            break;
                        }
           case 't': {
                            frequency_decrement( WAVEFORM_TRIANGLE_OUT );
                            log_printf( &logger, "Decreasing frequency of the triangle wave.\r\n" );
                            break;
                        }
           case 'Q': {
                            frequency_increment( WAVEFORM_SQUARE_OUT );
                            log_printf( &logger, "Increasing frequency of the square wave.\r\n" );
                            break;
                        }
           case 'q': {
                            frequency_decrement( WAVEFORM_SQUARE_OUT );
                            log_printf( &logger, "Decreasing frequency of the square wave.\r\n" );
                            break;
                        }
           default :{
                            break;
                        }
       }
       rx_data_buffer[ 0 ] = 0;
       rx_len = 0;
    }
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
