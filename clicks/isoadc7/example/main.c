/*!
 * @file main.c
 * @brief ISO ADC 7 Click example
 *
 * # Description
 * This example demonstrates the use of ISO ADC 7 Click board by reading and displaying
 * the voltage levels from 3 isolated analog input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 * The full-scale voltage input range is set to +-1.2V for all channels.
 *
 * ## Application Task
 * Reads the voltage levels from all 3 isolated analog input channels and displays
 * the results on the USB UART once per second approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "isoadc7.h"

static isoadc7_t isoadc7;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc7_cfg_t isoadc7_cfg;  /**< Click config object. */

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
    isoadc7_cfg_setup( &isoadc7_cfg );
    ISOADC7_MAP_MIKROBUS( isoadc7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc7_init( &isoadc7, &isoadc7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISOADC7_ERROR == isoadc7_default_cfg ( &isoadc7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float ch0 = 0;
    float ch1 = 0;
    float ch2 = 0;
    if ( ISOADC7_OK == isoadc7_read_voltage ( &isoadc7, &ch0, &ch1, &ch2 ) )
    {
        log_printf ( &logger, " CH0: %.1f mV\r\n", ch0 );
        log_printf ( &logger, " CH1: %.1f mV\r\n", ch1 );
        log_printf ( &logger, " CH2: %.1f mV\r\n\n", ch2 );
        Delay_ms ( 1000 );
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
