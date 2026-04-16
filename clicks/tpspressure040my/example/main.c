/*!
 * @file main.c
 * @brief TPS Pressure 040MY Click example
 *
 * # Description
 * This example demonstrates the use of the TPS Pressure 040MY Click board.
 * The application continuously measures and logs the pressure in millibars
 * and the temperature in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, checks communication, and applies the default configuration.
 *
 * ## Application Task
 * Reads and logs pressure and temperature values every 100 ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tpspressure040my.h"

#ifndef MIKROBUS_POSITION_TPSPRESSURE040MY
    #define MIKROBUS_POSITION_TPSPRESSURE040MY MIKROBUS_1
#endif

static tpspressure040my_t tpspressure040my;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tpspressure040my_cfg_t tpspressure040my_cfg;  /**< Click config object. */

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
    tpspressure040my_cfg_setup( &tpspressure040my_cfg );
    TPSPRESSURE040MY_MAP_MIKROBUS( tpspressure040my_cfg, MIKROBUS_POSITION_TPSPRESSURE040MY );
    if ( I2C_MASTER_ERROR == tpspressure040my_init( &tpspressure040my, &tpspressure040my_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TPSPRESSURE040MY_ERROR == tpspressure040my_default_cfg ( &tpspressure040my ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float pressure = 0;
    float temperature = 0;
    if ( TPSPRESSURE040MY_OK == tpspressure040my_read_data ( &tpspressure040my, &pressure, &temperature ) )
    {
        log_printf( &logger, " Pressure: %.2f mBar\r\n", pressure );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", temperature );
    }
    Delay_ms ( 100 );
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
