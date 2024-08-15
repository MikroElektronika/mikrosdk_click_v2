/*!
 * @file main.c
 * @brief PIR 3 Click example
 *
 * # Description
 * This example demonstrates the use of PIR 3 click board by reading and displaying
 * the peak hold tracking data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the peak hold tracking data every 100ms and displays the results on the USB UART.
 *
 * @note
 * In order to establish communication with the sensor, some of the supported MCUs may require
 * the I2C lines to be pulled up additionally either with the external or internal weak pull-up resistor.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pir3.h"

static pir3_t pir3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pir3_cfg_t pir3_cfg;  /**< Click config object. */

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
    pir3_cfg_setup( &pir3_cfg );
    PIR3_MAP_MIKROBUS( pir3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pir3_init( &pir3, &pir3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIR3_ERROR == pir3_default_cfg ( &pir3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{ 
    int16_t peak_hold = 0;
    if ( PIR3_OK == pir3_read_peak_hold ( &pir3, &peak_hold ) )
    {
        log_printf( &logger, " PEAK HOLD: %d\r\n\n", peak_hold );
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
