/*!
 * @file main.c
 * @brief DAC 14 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 14 click board by changing the voltage level
 * on the OUT0 as well as the waveform signals from a function generator on the OUT1.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the voltage level on the OUT0 as well as the waveform signals from a function
 * generator on the OUT1 every 3 seconds. The state of both outputs will be displayed
 * on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac14.h"

static dac14_t dac14;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac14_cfg_t dac14_cfg;  /**< Click config object. */

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
    dac14_cfg_setup( &dac14_cfg );
    DAC14_MAP_MIKROBUS( dac14_cfg, MIKROBUS_1 );
    err_t init_flag = dac14_init( &dac14, &dac14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC14_ERROR == dac14_default_cfg ( &dac14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint16_t dac = 0;
    static uint8_t waveform = DAC14_WAVEFORM_TRIANGULAR;
    if ( DAC14_OK == dac14_set_dac_data ( &dac14, DAC14_SEL_DAC_0, dac ) )
    {
        log_printf( &logger, "\r\n OUT0: %u -> %.2f V\r\n", 
                    dac, ( float ) dac * DAC14_VDD_3V3 / DAC14_DAC_DATA_MAX );
        dac += 100;
        if ( dac > DAC14_DAC_DATA_MAX )
        {
            dac = DAC14_DAC_DATA_MIN;
        }
    }
    err_t error_flag = dac14_stop_function_gen ( &dac14, DAC14_SEL_DAC_1 );
    error_flag |= dac14_config_function_gen ( &dac14, DAC14_SEL_DAC_1, waveform,
                                              DAC14_CODE_STEP_32_LSB, DAC14_SLEW_RATE_4_US );
    error_flag |= dac14_start_function_gen ( &dac14, DAC14_SEL_DAC_1 );
    if ( DAC14_OK == error_flag )
    {
        log_printf( &logger, " OUT1: " );
        switch ( waveform )
        {
            case DAC14_WAVEFORM_TRIANGULAR:
            {
                log_printf( &logger, "triangular wave at about 4kHz\r\n" );
                waveform = DAC14_WAVEFORM_SAWTOOTH;
                break;
            }
            case DAC14_WAVEFORM_SAWTOOTH:
            {
                log_printf( &logger, "sawtooth wave at about 7.8kHz\r\n" );
                waveform = DAC14_WAVEFORM_INV_SAWTOOTH;
                break;
            }
            case DAC14_WAVEFORM_INV_SAWTOOTH:
            {
                log_printf( &logger, "inverse sawtooth wave at about 7.8kHz\r\n" );
                waveform = DAC14_WAVEFORM_SINE;
                break;
            }
            case DAC14_WAVEFORM_SINE:
            {
                log_printf( &logger, "sine wave at about 10.7kHz\r\n" );
                waveform = DAC14_WAVEFORM_DISABLE;
                break;
            }
            case DAC14_WAVEFORM_DISABLE:
            {
                log_printf( &logger, "function generator disabled\r\n" );
                waveform = DAC14_WAVEFORM_TRIANGULAR;
                break;
            }
            default:
            {
                log_printf( &logger, "unknown state\r\n" );
                break;
            }
        }
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
