/*!
 * @file main.c
 * @brief AN to PWM 2 Click example
 *
 * # Description
 * This example demonstrates the use of AN to PWM 2 click board by changing the PWM output
 * frequency from 500kHz to 1MHz in steps of 50kHz.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Changes the PWM output frequency every 5 seconds in steps of 50kHz going through the full range
 * from 500kHz to 1MHz. The currently set frequency will be displayed on the USB UART.
 * 
 * @note
 * Applying a voltage of -2.5 to 2.5V on the input will generate the PWM pulse train
 * with a duty cycle linearly proportional to the input voltage.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "antopwm2.h"

static antopwm2_t antopwm2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    antopwm2_cfg_t antopwm2_cfg;  /**< Click config object. */

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
    antopwm2_cfg_setup( &antopwm2_cfg );
    ANTOPWM2_MAP_MIKROBUS( antopwm2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == antopwm2_init( &antopwm2, &antopwm2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint32_t freq = ANTOPWM2_FREQ_MIN;
    if ( ANTOPWM2_OK == antopwm2_set_frequency ( &antopwm2, freq ) )
    {
        log_printf ( &logger, " Frequency: %lu Hz\r\n\n", freq );
    }
    freq += 50000;
    if ( freq > ANTOPWM2_FREQ_MAX )
    {
        freq = ANTOPWM2_FREQ_MIN;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
