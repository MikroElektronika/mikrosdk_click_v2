/*!
 * @file main.c
 * @brief TempHum 26 Click example
 *
 * # Description
 * This example demonstrates the use of TempHum 26 Click board by reading the temperature
 * and humidity values in periodic intervals. The device is initialized and placed into 
 * single-shot measurement mode, then both environmental values are read and logged to the USB UART.
 * Data is updated every 200 ms.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the default configuration including device reset
 * and communication check. It then logs the DIE revision number and unique ID.
 *
 * ## Application Task
 * Starts a new temperature and humidity measurement, waits for the results,
 * and logs the readings to the terminal every 200 ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum26.h"

static temphum26_t temphum26;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum26_cfg_t temphum26_cfg;  /**< Click config object. */

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
    temphum26_cfg_setup( &temphum26_cfg );
    TEMPHUM26_MAP_MIKROBUS( temphum26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum26_init( &temphum26, &temphum26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM26_ERROR == temphum26_default_cfg ( &temphum26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " DIE revision number: 0x%.4X\r\n", temphum26.info.die_rev );
    log_printf ( &logger, " Unique ID: 0x%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\r\n", 
                 ( uint16_t ) temphum26.info.uid[ 0 ], ( uint16_t ) temphum26.info.uid[ 1 ],
                 ( uint16_t ) temphum26.info.uid[ 2 ], ( uint16_t ) temphum26.info.uid[ 3 ],
                 ( uint16_t ) temphum26.info.uid[ 4 ], ( uint16_t ) temphum26.info.uid[ 5 ],
                 ( uint16_t ) temphum26.info.uid[ 6 ], ( uint16_t ) temphum26.info.uid[ 7 ] );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    float humidity = 0;
    if ( TEMPHUM26_OK == temphum26_start_measurement ( &temphum26, TEMPHUM26_FLAG_TEMP_HUM ) )
    {
        if ( TEMPHUM26_OK == temphum26_read_data ( &temphum26, &temperature, &humidity ) )
        {
            log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
            log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
            Delay_ms ( 200 );
        }
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
