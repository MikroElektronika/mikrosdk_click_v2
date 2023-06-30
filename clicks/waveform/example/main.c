/*!
 * \file 
 * \brief Waveform Click example
 * 
 * # Description
 * This example demonstrates the use of Waveform click board.
 *
 * The application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the communication interface and configures the click board.
 * 
 * ## Application Task  
 * Predefined commands are inputed from the serial port.
 * Changes the signal frequency, waveform or amplitude depending on the receiver command.
 * 
 * \author MikroE Team 
 *
 */

#include "board.h"
#include "log.h"
#include "waveform.h"

static waveform_t waveform;
static log_t logger;

static uint32_t frequency = 200000;
static uint32_t frequency_step = 10000;

/**
 * @brief Waveform display commands function.
 * @details This function displays the list of supported commands on the USB UART.
 * @return None.
 * @note None.
 */
void waveform_display_commands ( void );

/**
 * @brief Waveform parse command function.
 * @details This function checks if the input command is supported and executes it.
 * @param[in] command : Command input, for more details refer to @b waveform_display_commands function.
 * @return None.
 * @note None.
 */
void waveform_parse_command ( uint8_t command );

void application_init ( void )
{
    log_cfg_t log_cfg;
    waveform_cfg_t waveform_cfg;

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
    waveform_cfg_setup( &waveform_cfg );
    WAVEFORM_MAP_MIKROBUS( waveform_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == waveform_init( &waveform, &waveform_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    waveform_sine_output( &waveform, frequency );
    log_printf( &logger, "Sine wave output set with approx. frequency: %lu Hz\r\n", frequency );
    waveform_display_commands ( );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t command = 0;
    if ( 1 == log_read ( &logger, &command, 1 ) ) 
    {
        waveform_parse_command ( command );
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

void waveform_display_commands ( void )
{
    log_printf( &logger, "-------------------------------------------\r\n" );
    log_info( &logger, "- UART commands list -\r\n" );
    log_printf( &logger, "'+' - Increase amplitude.\r\n" );
    log_printf( &logger, "'-' - Decrease amplitude.\r\n" );
    log_printf( &logger, "'S' - Select sine wave output and increase frequency.\r\n" );
    log_printf( &logger, "'s' - Select sine wave output and decrease frequency.\r\n" );
    log_printf( &logger, "'T' - Select triangle wave output and increase frequency.\r\n" );
    log_printf( &logger, "'t' - Select triangle wave output and decrease frequency.\r\n" );
    log_printf( &logger, "'Q' - Select square wave output and increase frequency.\r\n" );
    log_printf( &logger, "'q' - Select square wave output and decrease frequency.\r\n" );
    log_printf( &logger, "'L' or 'l' - Display commands list.\r\n" );
    log_printf( &logger, "-------------------------------------------\r\n" );
}

void waveform_parse_command ( uint8_t command )
{
    switch ( command )
    {
        case '+': 
        {
            log_printf( &logger, "Increasing amplitude of the current wave.\r\n" );
            waveform_digipot_inc ( &waveform );
            break;
        }
        case '-': 
        {
            log_printf( &logger, "Decreasing amplitude of the current wave.\r\n" );
            waveform_digipot_dec ( &waveform );
            break;
        }
        case 'S': 
        {
            log_printf( &logger, "Increasing frequency of the sine wave.\r\n" );
            frequency += frequency_step;
            waveform_sine_output( &waveform, frequency );
            log_printf( &logger, "Approx. frequency: %lu Hz\r\n", frequency );
            break;
        }
        case 's': 
        {
            log_printf( &logger, "Decreasing frequency of the sine wave.\r\n" );
            if ( frequency < frequency_step )
            {
                frequency = 0;
            }
            else
            {
                frequency -= frequency_step;
            }
            waveform_sine_output( &waveform, frequency );
            log_printf( &logger, "Approx. frequency: %lu Hz\r\n", frequency );
            break;
        }
        case 'T': 
        {
            log_printf( &logger, "Increasing frequency of the triangle wave.\r\n" );
            frequency += frequency_step;
            waveform_triangle_output( &waveform, frequency );
            log_printf( &logger, "Approx. frequency: %lu Hz\r\n", frequency );
            break;
        }
        case 't': 
        {
            log_printf( &logger, "Decreasing frequency of the triangle wave.\r\n" );
            if ( frequency < frequency_step )
            {
                frequency = 0;
            }
            else
            {
                frequency -= frequency_step;
            }
            waveform_triangle_output( &waveform, frequency );
            log_printf( &logger, "Approx. frequency: %lu Hz\r\n", frequency );
            break;
        }
        case 'Q': 
        {
            log_printf( &logger, "Increasing frequency of the square wave.\r\n" );
            frequency += frequency_step;
            waveform_square_output( &waveform, frequency );
            log_printf( &logger, "Approx. frequency: %lu Hz\r\n", frequency );
            break;
        }
        case 'q': 
        {
            log_printf( &logger, "Decreasing frequency of the square wave.\r\n" );
            if ( frequency < frequency_step )
            {
                frequency = 0;
            }
            else
            {
                frequency -= frequency_step;
            }
            waveform_square_output( &waveform, frequency );
            log_printf( &logger, "Approx. frequency: %lu Hz\r\n", frequency );
            break;
        }
        case 'L': case 'l': 
        {
            waveform_display_commands ( );
            break;
        }
        default :
        {
            log_error( &logger, "Wrong command." );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
