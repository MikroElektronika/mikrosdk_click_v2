/*!
 * @file main.c
 * @brief ADC 26 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 26 Click board by reading and
 * displaying the voltage levels from IN0-IN1 differential and IN2-IN3
 * single-ended analog input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the voltage levels from IN0-IN1 differential (+/- 2.048V) and
 * IN2-IN3 single-ended (+/- 4.096V) analog input channels and displays
 * the results on the USB UART once per second approximately.
 *
 * @note
 * Do not apply more than VCC + 0.3 V to the analog inputs of the device.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc26.h"

static adc26_t adc26;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc26_cfg_t adc26_cfg;  /**< Click config object. */

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
    adc26_cfg_setup( &adc26_cfg );
    ADC26_MAP_MIKROBUS( adc26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc26_init( &adc26, &adc26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC26_ERROR == adc26_default_cfg ( &adc26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( ADC26_OK == adc26_start_conversion ( &adc26, ADC26_MUX_P_AIN0_N_AIN1, ADC26_PGA_2_048V ) )
    {
        while ( adc26_get_alert_pin ( &adc26 ) ); // Waits for a data ready indication
        
        if ( ADC26_OK == adc26_read_voltage ( &adc26, &voltage ) )
        {
            log_printf ( &logger, " Voltage between IN0[P] and IN1[N]: %.3f V\r\n", voltage );
        }
    }
    if ( ADC26_OK == adc26_start_conversion ( &adc26, ADC26_MUX_P_AIN2_N_GND, ADC26_PGA_4_096V ) )
    {
        while ( adc26_get_alert_pin ( &adc26 ) ); // Waits for a data ready indication
        
        if ( ADC26_OK == adc26_read_voltage ( &adc26, &voltage ) )
        {
            log_printf ( &logger, " Voltage between IN2 and GND: %.3f V\r\n", voltage );
        }
    }
    if ( ADC26_OK == adc26_start_conversion ( &adc26, ADC26_MUX_P_AIN3_N_GND, ADC26_PGA_4_096V ) )
    {
        while ( adc26_get_alert_pin ( &adc26 ) ); // Waits for a data ready indication
        
        if ( ADC26_OK == adc26_read_voltage ( &adc26, &voltage ) )
        {
            log_printf ( &logger, " Voltage between IN3 and GND: %.3f V\r\n\n", voltage );
        }
    }
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
