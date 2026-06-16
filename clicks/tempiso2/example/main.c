/*!
 * @file main.c
 * @brief Temp ISO 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Temp ISO Click board by reading
 * and displaying the temperature measurements.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the temperature measurement in degrees Celsius and displays
 * the results on the USB UART approximately once per second.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "tempiso2.h"

#ifndef MIKROBUS_POSITION_TEMPISO2
    #define MIKROBUS_POSITION_TEMPISO2 MIKROBUS_1
#endif

static tempiso2_t tempiso2;   /**< Temp ISO 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempiso2_cfg_t tempiso2_cfg;  /**< Click config object. */

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
    tempiso2_cfg_setup( &tempiso2_cfg );
    TEMPISO2_MAP_MIKROBUS( tempiso2_cfg, MIKROBUS_POSITION_TEMPISO2 );
    if ( ADC_ERROR == tempiso2_init( &tempiso2, &tempiso2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;

    if ( TEMPISO2_OK == tempiso2_read_temperature ( &tempiso2, &temperature ) ) 
    {
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", temperature );
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
