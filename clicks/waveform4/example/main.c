/*!
 * @file main.c
 * @brief Waveform4 Click example
 *
 * # Description
 * This example demonstrates the use of Waveform 4 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which
 * resets the registers and sets the sine wave output with default gain and 
 * default frequency for all channels. After that it displays the list of
 * supported commands on the USB UART.
 *
 * ## Application Task
 * Depending on the command character received from USB UART it changes the 
 * signal frequency, gain or wave of the selected channel.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "waveform4.h"

static waveform4_t waveform4;
static log_t logger;

#define GAIN_STEP 0.05  // Gain step, used for increase/decrease gain commands.
#define FREQ_STEP 100   // Frequency step, used for increase/decrease frequency commands.

uint32_t freq = WAVEFORM4_DEFAULT_FREQUENCY;
float gain = WAVEFORM4_DEFAULT_GAIN;
uint8_t channel = WAVEFORM4_CHANNEL_1;
uint8_t wave = WAVEFORM4_WAVE_SINE;

/**
 * @brief Waveform 4 display commands function.
 * @details This function displays the list of supported commands on the USB UART.
 * @return None.
 * @note None.
 */
void waveform4_display_commands ( void );

/**
 * @brief Waveform 4 parse command function.
 * @details This function checks if the input command is supported and executes it.
 * @param[in] command : Command input, for more details refer to @b waveform4_display_commands function.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Wrong command or command is not executed properly.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waveform4_parse_command ( uint8_t command );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waveform4_cfg_t waveform4_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    waveform4_cfg_setup( &waveform4_cfg );
    WAVEFORM4_MAP_MIKROBUS( waveform4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == waveform4_init( &waveform4, &waveform4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( WAVEFORM4_ERROR == waveform4_default_cfg ( &waveform4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    waveform4_display_commands ( );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t command = 0;
    if ( log_read ( &logger, &command, 1 ) > 0 ) 
    {
        waveform4_parse_command ( command );
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

void waveform4_display_commands ( void )
{
    log_printf( &logger, "-------------------------------------------\r\n" );
    log_info( &logger, "- UART commands list -\r\n" );
    log_printf( &logger, "'+' - Increase frequency.\r\n" );
    log_printf( &logger, "'-' - Decrease frequency.\r\n" );
    log_printf( &logger, "'G' - Increase gain.\r\n" );
    log_printf( &logger, "'g' - Decrease gain.\r\n" );
    log_printf( &logger, "'S' or 's' - Select sine wave output.\r\n" );
    log_printf( &logger, "'C' or 'c' - Select cosine wave output.\r\n" );
    log_printf( &logger, "'T' or 't' - Select triangle wave output.\r\n" );
    log_printf( &logger, "'P' or 'p' - Select positive sawtooth wave output.\r\n" );
    log_printf( &logger, "'N' or 'n' - Select negative sawtooth wave output.\r\n" );
    log_printf( &logger, "'1' - Select channel 1.\r\n" );
    log_printf( &logger, "'2' - Select channel 2.\r\n" );
    log_printf( &logger, "'3' - Select channel 3.\r\n" );
    log_printf( &logger, "'4' - Select channel 4.\r\n" );
    log_printf( &logger, "'L' or 'l' - Display commands list.\r\n" );
    log_printf( &logger, "-------------------------------------------\r\n" );
}

err_t waveform4_parse_command ( uint8_t command )
{
    switch( command )
    {
        case '+': 
        {
            freq += FREQ_STEP;
            if ( freq > WAVEFORM4_MASTER_CLOCK )
            {
                freq = WAVEFORM4_MASTER_CLOCK;
            }
            log_printf( &logger, "Frequency increased: %lu Hz\r\n", freq );
            return waveform4_set_frequency ( &waveform4, freq );
        }
        case '-': 
        {
            freq -= FREQ_STEP;
            if ( freq > WAVEFORM4_MASTER_CLOCK )
            {
                freq = 0;
            }
            log_printf( &logger, "Frequency decreased: %lu Hz\r\n", freq );
            return waveform4_set_frequency ( &waveform4, freq );
        }
        case 'G': 
        {
            gain += GAIN_STEP;
            if ( gain > WAVEFORM4_GAIN_MAX )
            {
                gain = WAVEFORM4_GAIN_MAX;
            }
            log_printf( &logger, "Gain increased: %.3f\r\n", gain );
            return waveform4_set_gain ( &waveform4, channel, gain );
        }
        case 'g': 
        {
            gain -= GAIN_STEP;
            if ( gain < WAVEFORM4_GAIN_MIN )
            {
                gain = WAVEFORM4_GAIN_MIN;
            }
            log_printf( &logger, "Gain decreased: %.3f\r\n", gain );
            return waveform4_set_gain ( &waveform4, channel, gain );
        }
        case 'S': case 's': 
        {
            wave = WAVEFORM4_WAVE_SINE;
            log_printf( &logger, "Sine wave selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case 'C': case 'c': 
        {
            wave = WAVEFORM4_WAVE_COSINE;
            log_printf( &logger, "Cosine wave selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case 'T': case 't': 
        {
            wave = WAVEFORM4_WAVE_TRIANGLE;
            log_printf( &logger, "Triangle wave selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case 'P': case 'p': 
        {
            wave = WAVEFORM4_WAVE_POSITIVE_SAWTOOTH;
            log_printf( &logger, "Positive sawtooth wave selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case 'N': case 'n': 
        {
            wave = WAVEFORM4_WAVE_NEGATIVE_SAWTOOTH;
            log_printf( &logger, "Negative sawtooth wave selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case '1': 
        {
            channel = WAVEFORM4_CHANNEL_1;
            log_printf( &logger, "Channel 1 selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case '2': 
        {
            channel = WAVEFORM4_CHANNEL_2;
            log_printf( &logger, "Channel 2 selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case '3': 
        {
            channel = WAVEFORM4_CHANNEL_3;
            log_printf( &logger, "Channel 3 selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case '4': 
        {
            channel = WAVEFORM4_CHANNEL_4;
            log_printf( &logger, "Channel 4 selected.\r\n" );
            return waveform4_set_wave_output ( &waveform4, channel, wave );
        }
        case 'L': case 'l': 
        {
            waveform4_display_commands ( );
            return WAVEFORM4_OK;
        }
        default :
        {
            log_error( &logger, "Wrong command." );
            return WAVEFORM4_ERROR; 
        }
    }
}

// ------------------------------------------------------------------------ END
