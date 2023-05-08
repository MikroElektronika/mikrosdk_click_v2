/*!
 * @file main.c
 * @brief Magnetic Rotary 5 Click example
 *
 * # Description
 * This example demonstrates the use of Magnetic Rotary 5 click board by reading and displaying
 * the magnet angular position as well as the AGC and multi turn counter values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the multi turn counter to zero.
 *
 * ## Application Task
 * Reads the magnet angular position in degrees as well as the voltage from AN pin which is
 * proportional to the angular position. Also reads the AGC and multi turn counter values.
 * The results will be displayed on the USB UART every 100ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneticrotary5.h"

static magneticrotary5_t magneticrotary5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary5_cfg_t magneticrotary5_cfg;  /**< Click config object. */

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
    magneticrotary5_cfg_setup( &magneticrotary5_cfg );
    MAGNETICROTARY5_MAP_MIKROBUS( magneticrotary5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == magneticrotary5_init( &magneticrotary5, &magneticrotary5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY5_ERROR == magneticrotary5_default_cfg ( &magneticrotary5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t agc = 0;
    uint16_t angle = 0;
    int16_t mt_cnt = 0;
    float voltage = 0;
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_angle ( &magneticrotary5, &agc, &angle ) )
    {
        log_printf ( &logger, "\r\n AGC: %u\r\n Angle: %u\r\n", ( uint16_t ) agc, angle );
    }
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_mt_cnt ( &magneticrotary5, &mt_cnt ) )
    {
        log_printf ( &logger, " Multi turn counter: %d\r\n", mt_cnt );
    }
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_voltage ( &magneticrotary5, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
    }
    Delay_ms ( 100 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
