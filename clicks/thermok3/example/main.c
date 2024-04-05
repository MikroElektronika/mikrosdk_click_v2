/*!
 * @file main.c
 * @brief Thermo K 3 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo K 3 click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the temperature measurement in Celsius and displays the results on the USB UART
 * approximately once per second. If there's no thermocouple type-K probe inserted an
 * appropriate message will be displayed instead.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermok3.h"

static thermok3_t thermok3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermok3_cfg_t thermok3_cfg;  /**< Click config object. */

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
    thermok3_cfg_setup( &thermok3_cfg );
    THERMOK3_MAP_MIKROBUS( thermok3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermok3_init( &thermok3, &thermok3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    err_t error_flag = thermok3_read_temperature ( &thermok3, &temperature );
    if ( THERMOK3_OK == error_flag )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    else if ( THERMOK3_OPEN_THERMOCOUPLE == error_flag )
    {
        log_printf( &logger, " NO thermocouple input\r\n\n" );
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
