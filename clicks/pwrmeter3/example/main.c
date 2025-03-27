/*!
 * @file main.c
 * @brief PWR Meter 3 Click example
 *
 * # Description
 * This example demonstrates the use of PWR Meter 3 Click board by reading and displaying
 * the voltage, current, and power RMS measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets the DC measurement
 * and VRMS thresholds to about 28V for overvoltage and about 9.3V for undervoltage flag.
 *
 * ## Application Task
 * Reads the voltage and current RMS values averaged from 500 samples, then calculates the power from it
 * and displays the results on the USB UART. Also if an UV or OV flag is detected it will be logged accordingly.
 * 
 * @note
 * In case of 15A or 60A versions of PWR Meter 3 Click board the PWRMETER3_MAX_CURRENT macro from pwrmeter3.h file
 * must be adjusted for accurate current measurements.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pwrmeter3.h"

static pwrmeter3_t pwrmeter3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pwrmeter3_cfg_t pwrmeter3_cfg;  /**< Click config object. */

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
    pwrmeter3_cfg_setup( &pwrmeter3_cfg );
    PWRMETER3_MAP_MIKROBUS( pwrmeter3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pwrmeter3_init( &pwrmeter3, &pwrmeter3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PWRMETER3_ERROR == pwrmeter3_default_cfg ( &pwrmeter3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float v_rms, i_rms;
    if ( PWRMETER3_OK == pwrmeter3_read_average_rms ( &pwrmeter3, &v_rms, &i_rms, PWRMETER3_DEF_AVG_SAMPLES ) )
    {
        if ( !pwrmeter3_get_dio0_pin ( &pwrmeter3 ) )
        {
            log_printf ( &logger, " Over-voltage detected!\r\n" );
        }
        if ( !pwrmeter3_get_dio1_pin ( &pwrmeter3 ) )
        {
            log_printf ( &logger, " Under-voltage detected!\r\n" );
        }
        log_printf ( &logger, " Voltage: %.2f V\r\n", v_rms );
        log_printf ( &logger, " Current: %.2f A\r\n", i_rms );
        log_printf ( &logger, " Power: %.2f W\r\n\n", i_rms * v_rms );
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
