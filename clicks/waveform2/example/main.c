/*!
 * @file main.c
 * @brief Waveform2 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Waveform 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialize the communication interface, preforming hardware reset, and configure the click board.
 *
 * ## Application Task
 * Predefined characters are inputed from the serial port.
 * Depending on the character sent the signal frequency, waveform or amplitude
 * will be changed.
 *
 * - Command:
 * [ + ] - Increase frequency
 * [ - ] - Decrease frequency
 * [ t ] - Triangle-shaped signal
 * [ s ] - The signal in the form of a sinusoid
 * 
 * - Additional Functions :
 * aprox_freq_calculation( float freqency ) - This function is used to calculate the aproximate 
 * value that will be written to the frequency set register.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "waveform2.h"

static waveform2_t waveform2;
static log_t logger;

float value = 100000;
char demo_rx_buf[ 10 ];
char demo_tx_buf[ 10 ] = "MikroE";

/**
 * @brief Aproximate frequency calculation function.
 * @details This function is used to calculate the aproximate value that will be 
 * written to the frequency set register..
 */
uint32_t aprox_freq_calculation ( float freqency );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    waveform2_cfg_t waveform2_cfg;  /**< Click config object. */

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
    waveform2_cfg_setup( &waveform2_cfg );
    WAVEFORM2_MAP_MIKROBUS( waveform2_cfg, MIKROBUS_1 );
    err_t init_flag  = waveform2_init( &waveform2, &waveform2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    waveform2_default_cfg ( &waveform2 );

    log_printf( &logger, "---- EEPROM test ----\r\n " );
    log_printf( &logger, ">> Write [MikroE] to address 0x0123\r\n " );
    waveform2_eeprom_write_string( &waveform2, 0x0123, demo_tx_buf, 6 );
    waveform2_eeprom_read_string ( &waveform2, 0x0123, demo_rx_buf, 6 );
    log_printf( &logger, ">> Read data: %s  from address 0x0123.... \r\n ", demo_rx_buf );
    Delay_ms( 1000 );
    waveform2_hw_reset( &waveform2 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "---- Waveform set freqency ----\r\n" );
    int32_t freqency;
    freqency = aprox_freq_calculation( value );
    waveform2_set_freq( &waveform2, freqency );
    waveform2_triangle_output( &waveform2 );
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    char rx_data;
    uint32_t freq_data;

    if ( log_read( &logger, &rx_data, 1 ) ) {
        switch ( rx_data ) {
            case '+': {
                if ( value > 200000 ) {
                    value = 0;
                }
                value += 100000;
                freq_data = aprox_freq_calculation( value );
                waveform2_set_freq( &waveform2, freq_data );
                log_printf( &logger, ">> Increasing the frequency \r\n " );
                break;
            }

            case '-': {
                if ( value < 200000 ) {
                    value = 400000;
                }
                value -= 100000;
                freq_data = aprox_freq_calculation( value );
                waveform2_set_freq( &waveform2, freq_data );
                log_printf( &logger, ">> Decreasing the frequency \r\n " );
                break;
            }

            case 't': {
                waveform2_triangle_output( &waveform2 );
                log_printf( &logger, ">> Triangle output \r\n " );
                break;
            }

            case 's': {
                waveform2_sine_output( &waveform2 );
                log_printf( &logger,  ">> Sinusoid output \r\n " );
                break;
            }
        }
    }
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

uint32_t aprox_freq_calculation ( float freqency ) {
    uint32_t calculation;
    float WAVEFORM_OSC_FREQ = 50000000.0;
    float WAVEFORM_CONSTANT = 268435456.0; 

    calculation = freqency * ( WAVEFORM_CONSTANT / WAVEFORM_OSC_FREQ );

    return calculation;
}

// ------------------------------------------------------------------------ END
