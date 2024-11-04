/*!
 * @file main.c
 * @brief ADC16 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 16 Click board by reading 
 * the voltage from the two analog input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which
 * sets the two analog input channels to single-ended mode.
 *
 * ## Application Task
 * Reads and displays the voltage from the two analog input channels 
 * on the USB UART approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc16.h"

static adc16_t adc16;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc16_cfg_t adc16_cfg;  /**< Click config object. */

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
    adc16_cfg_setup( &adc16_cfg );
    ADC16_MAP_MIKROBUS( adc16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc16_init( &adc16, &adc16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC16_ERROR == adc16_default_cfg ( &adc16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float ain0_voltage, ain1_voltage;
    if ( ADC16_OK == adc16_get_voltage ( &adc16, &ain0_voltage, &ain1_voltage ) )
    {
        log_printf ( &logger, " AIN0 voltage: %.3f V \r\n", ain0_voltage );
        log_printf ( &logger, " AIN1 voltage: %.3f V \r\n\n", ain1_voltage );
        Delay_ms ( 100 );
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
