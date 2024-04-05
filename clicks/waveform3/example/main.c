/*!
 * @file main.c
 * @brief Waveform3 Click example
 *
 * # Description
 * This demo app shows the basic capabilities of Waveform 3
 * click board. First, the sinusoidal wave is incremented
 * to targeted frequency for visually pleasing introduction
 * after which it changes between 4 modes of output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Application initializes the UART LOG and SPI drivers,
 * resets the device and sets frequency and phase shift to
 * default values. In the end, the mode is set with the 
 * preferred freq and phase channel.
 *
 * ## Application Task
 * Task commences with the start frequency rising up to
 * the targeted one. When it reaches desired frequency,
 * the mode changes every 5 seconds which includes: 
 * sinusoidal, triangular, DAC divided by 2 and DAC
 * outputs respectively.
 *
 * *note:*
 * Waveform 3 click might not provide a high enough peak to peak signal on higher frequencies.
 * The user can freely implement custom buffer for the output stage.
 * Special thanks to my esteemed co-worker Nenad Filipovic for support during firmware development.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "waveform3.h"

static waveform3_t waveform3;
static log_t logger;

static uint32_t start_frequency = 100;
static uint32_t rising_factor = 10;
static uint32_t target_frequency = 10000;

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    waveform3_cfg_t waveform3_cfg;  /**< Click config object. */

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

    waveform3_cfg_setup( &waveform3_cfg );
    WAVEFORM3_MAP_MIKROBUS( waveform3_cfg, MIKROBUS_1 );
    err_t init_flag  = waveform3_init( &waveform3, &waveform3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    waveform3_default_cfg( &waveform3 );
    Delay_ms ( 500 );
    log_info( &logger, " Application Task " );
    waveform3_set_mode( &waveform3, WAVEFORM3_CFG_MODE_SINUSOIDAL, WAVEFORM3_CFG_FREQ_REG0, WAVEFORM3_CFG_PHASE_REG0 );
}

void application_task ( void ) {
    uint8_t cfg_mode_switch;
    
    if ( start_frequency < target_frequency ) {
        if ( start_frequency / rising_factor < 100 ) {
            start_frequency += rising_factor;
            waveform3_set_freq( &waveform3, start_frequency, WAVEFORM3_CFG_FREQ_REG0 );
            Delay_ms ( 5 );
        } else {
            rising_factor += 10;
        }
    } else {
        for ( cfg_mode_switch = 0 ; cfg_mode_switch < 4 ; cfg_mode_switch++ ) {
        waveform3_set_mode( &waveform3, cfg_mode_switch, WAVEFORM3_CFG_FREQ_REG0, WAVEFORM3_CFG_PHASE_REG0 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        }
    }
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
