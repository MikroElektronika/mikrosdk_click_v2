/*!
 * @file main.c
 * @brief Cooler Click Example.
 *
 * # Description
 * This example demonstrates the use of the Cooler click board 
 * by reading the target object temperature and controlling the cooler.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application measures the temperature of the target object in degrees Celsius 
 * and enables a cooler if the temperature exceeds the temperature high limit value.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "cooler.h"

// Object temperature high limit
#define COOLER_TEMP_HIGH_LIMIT    30.0

static cooler_t cooler;   /**< Cooler Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cooler_cfg_t cooler_cfg;  /**< Click config object. */

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
    cooler_cfg_setup( &cooler_cfg );
    COOLER_MAP_MIKROBUS( cooler_cfg, MIKROBUS_1 );
    err_t init_flag = cooler_init( &cooler, &cooler_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COOLER_ERROR == cooler_default_cfg ( &cooler ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    if ( COOLER_OK == cooler_get_object_temperature( &cooler, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf( &logger, " Cooler: " );
        if ( COOLER_TEMP_HIGH_LIMIT < temperature )
        {
            if ( COOLER_OK == cooler_set_out_state( &cooler, COOLER_ENABLE ) )
            {
                log_printf( &logger, " Enabled.\r\n\n" );
            }
        }
        else
        {
            if ( COOLER_OK == cooler_set_out_state( &cooler, COOLER_DISABLE ) )
            {
                log_printf( &logger, " Disabled.\r\n\n" );
            }
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
