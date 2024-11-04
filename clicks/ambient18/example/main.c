/*!
 * @file main.c
 * @brief Ambient 18 Click Example.
 *
 * # Description
 * This example demonstrates the use of Ambient 18 Click board by measuring and displaying
 * the illuminance value in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the gain mode to M-Gain which can detect 
 * the illuminance of up to 1000 lux.
 *
 * ## Application Task
 * Reads the ADC voltage and then calculates the illuminance from it.
 * The calculated value of illuminance in lux is being displayed on the USB UART 
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient18.h"

static ambient18_t ambient18;   /**< Ambient 18 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient18_cfg_t ambient18_cfg;  /**< Click config object. */

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
    ambient18_cfg_setup( &ambient18_cfg );
    AMBIENT18_MAP_MIKROBUS( ambient18_cfg, MIKROBUS_1 );
    err_t init_flag = ambient18_init( &ambient18, &ambient18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ambient18_set_gain_mode ( &ambient18, AMBIENT18_MODE_M_GAIN );
    log_printf( &logger, " M-Gain mode selected.\r\n Up to 1000 lux can be measured.\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( AMBIENT18_OK == ambient18_read_voltage ( &ambient18, &voltage ) ) 
    {
        log_printf( &logger, " Illuminance : %ld Lux\r\n\n", ambient18_voltage_to_lux( &ambient18, voltage ) );
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
