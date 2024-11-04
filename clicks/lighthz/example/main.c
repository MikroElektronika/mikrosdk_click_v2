/*!
 * @file main.c
 * @brief LightHz Click Example.
 *
 * # Description
 * This example demonstrates the use of LightHz Click board by measuring and displaying
 * the frequency of clock output signal. The higher the light intensity the higher the frequency.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the sensitivity mode and frequency scaling in case
 * the onboard jumpers are set to MCU instead to ON-BRD.
 *
 * ## Application Task
 * Measures the clock output frequency using the polling method and delays. The results are being
 * sent to the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lighthz.h"

static lighthz_t lighthz;   /**< LightHz Click driver object. */
static log_t logger;        /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lighthz_cfg_t lighthz_cfg;  /**< Click config object. */

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
    lighthz_cfg_setup( &lighthz_cfg );
    LIGHTHZ_MAP_MIKROBUS( lighthz_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == lighthz_init( &lighthz, &lighthz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lighthz_set_sensitivity ( &lighthz, LIGHTHZ_SENS_100X );
    lighthz_set_frequency_scaling ( &lighthz, LIGHTHZ_FSCALE_100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint32_t freq_cnt = 0;
    uint16_t sample_cnt = 0;

    // Wait for the clock rising edge signal
    while ( !hal_ll_gpio_read_pin_input( &lighthz.freq.pin ) );

    // A loop for measuring the clock frequency counts. It's not an ideal implementation.
    // Here we should use an external interrupt on the clock pin rising edge and a timer interrupt
    // for the best accuracy, however, those interrupt features have not yet been implemented in the SDK. 
    while ( ( sample_cnt < LIGHTHZ_SAMPLE_COUNTS ) && ( freq_cnt < LIGHTHZ_MAX_COUNTS_PER_S ) )
    {
        // A single iteration in the loops below should take as close to 10us as possible
        // So to improve the measurement accuracy adjust the delay below for your system
        while ( hal_ll_gpio_read_pin_input( &lighthz.freq.pin ) )
        {
            freq_cnt++;
            Delay_us ( LIGHTHZ_DELAY_US );
        }
        while ( !hal_ll_gpio_read_pin_input( &lighthz.freq.pin ) )
        {
            freq_cnt++;
            Delay_us ( LIGHTHZ_DELAY_US );
        }
        sample_cnt++;
    }
    freq_cnt /= sample_cnt;

    // The higher the light intensity the higher the frequency.
    log_printf( &logger, " Frequency: %.1f Hz\r\n\n", ( float ) LIGHTHZ_MAX_COUNTS_PER_S / freq_cnt );

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
