/*!
 * @file main.c
 * @brief Ambient 12 Click Example.
 *
 * # Description
 * This example demonstrates the use of Ambient 12 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the gain mode to M-Gain which can detect the illuminance of up to 10000 lux.
 *
 * ## Application Task
 * Reads the ADC voltage and then calculates the illuminance from it.
 * The calculated value of illuminance in lux is being displayed on the USB UART approximately once per second. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient12.h"

static ambient12_t ambient12;       /**< Ambient 12 Click driver object. */
static log_t logger;                /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    ambient12_cfg_t ambient12_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ambient12_cfg_setup( &ambient12_cfg );
    AMBIENT12_MAP_MIKROBUS( ambient12_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ambient12_init( &ambient12, &ambient12_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ambient12_set_gain_mode ( &ambient12, AMBIENT12_MODE_M_GAIN );
    log_printf( &logger, " M-Gain mode selected.\r\n Up to 10000 lux can be measured.\r\n" );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    
    if ( AMBIENT12_OK == ambient12_read_adc_voltage ( &ambient12, &voltage ) )
    {
        log_printf( &logger, " Illuminance : %ld Lux\r\n\n", ambient12_voltage_to_lux( &ambient12, voltage ) );
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
