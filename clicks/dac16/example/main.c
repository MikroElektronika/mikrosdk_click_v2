/*!
 * @file main.c
 * @brief DAC 16 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 16 click board by changing the voltage level
 * on the OUT0 as well as the waveform signals from a function generator on the OUT1.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the voltage level on the OUT0 as well as the waveform signals from a function
 * generator on the OUT1 every 3 seconds. The state of all outputs will be displayed
 * on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac16.h"

static dac16_t dac16;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac16_cfg_t dac16_cfg;  /**< Click config object. */

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
    dac16_cfg_setup( &dac16_cfg );
    DAC16_MAP_MIKROBUS( dac16_cfg, MIKROBUS_1 );
    err_t init_flag = dac16_init( &dac16, &dac16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC16_ERROR == dac16_default_cfg ( &dac16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint16_t dac = 0;
    static uint8_t waveform = DAC16_WAVEFORM_TRIANGULAR;
    if ( DAC16_OK == dac16_set_dac_data ( &dac16, DAC16_SEL_DAC_0, dac ) )
    {
        log_printf( &logger, "\r\n OUT0: %u -> %.2f V\r\n", 
                    dac, ( float ) dac * DAC16_VDD_3V3 / DAC16_DAC_DATA_MAX );
        dac += 100;
        if ( dac > DAC16_DAC_DATA_MAX )
        {
            dac = DAC16_DAC_DATA_MIN;
        }
    }
    err_t error_flag = dac16_stop_function_gen ( &dac16, DAC16_SEL_DAC_1 );
    error_flag |= dac16_config_function_gen ( &dac16, DAC16_SEL_DAC_1, waveform,
                                              DAC16_CODE_STEP_32_LSB, DAC16_SLEW_RATE_4_US );
    error_flag |= dac16_start_function_gen ( &dac16, DAC16_SEL_DAC_1 );
    if ( DAC16_OK == error_flag )
    {
        log_printf( &logger, " OUT1: " );
        switch ( waveform )
        {
            case DAC16_WAVEFORM_TRIANGULAR:
            {
                log_printf( &logger, "triangular wave at about 1kHz\r\n" );
                waveform = DAC16_WAVEFORM_SAWTOOTH;
                break;
            }
            case DAC16_WAVEFORM_SAWTOOTH:
            {
                log_printf( &logger, "sawtooth wave at about 2kHz\r\n" );
                waveform = DAC16_WAVEFORM_INV_SAWTOOTH;
                break;
            }
            case DAC16_WAVEFORM_INV_SAWTOOTH:
            {
                log_printf( &logger, "inverse sawtooth wave at about 2kHz\r\n" );
                waveform = DAC16_WAVEFORM_SINE;
                break;
            }
            case DAC16_WAVEFORM_SINE:
            {
                log_printf( &logger, "sine wave at about 10.5kHz\r\n" );
                waveform = DAC16_WAVEFORM_DISABLE;
                break;
            }
            case DAC16_WAVEFORM_DISABLE:
            {
                log_printf( &logger, "function generator disabled\r\n" );
                waveform = DAC16_WAVEFORM_TRIANGULAR;
                break;
            }
            default:
            {
                log_printf( &logger, "unknown state\r\n" );
                break;
            }
        }
        // OUT2 and OUT3 are set in dac16_default_cfg
        log_printf( &logger, " OUT2: sine wave at about 10.5kHz\r\n" );
        log_printf( &logger, " OUT3: sawtooth wave at about 2kHz\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
