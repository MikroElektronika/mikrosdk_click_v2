/*!
 * @file main.c
 * @brief I2C Scanner example
 *
 * # Description
 * This example demonstrates the use of the I2C Scanner application.
 * It performs a scan of the I2C bus and logs all detected device addresses
 * over the USB UART interface.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and I2C Scanner driver.
 *
 * ## Application Task
 * Scans the I2C bus and displays detected device addresses once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cscanner.h"

static i2cscanner_t i2cscanner;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cscanner_cfg_t i2cscanner_cfg;  /**< Config object. */

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

    // Scanner initialization.
    i2cscanner_cfg_setup( &i2cscanner_cfg );
    I2CSCANNER_MAP_MIKROBUS( i2cscanner_cfg, MIKROBUS_1 );
    if ( I2CSCANNER_OK != i2cscanner_init( &i2cscanner, &i2cscanner_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    i2cscanner_scan_t scan;
    if ( I2CSCANNER_OK == i2cscanner_scan_i2c ( &i2cscanner, &scan ) )
    {
        log_printf ( &logger, "I2C device(s) found [%u]: ", scan.num_addr );
        for ( uint8_t cnt = 0; cnt < scan.num_addr; cnt++ )
        {
            log_printf ( &logger, "0x%.2X", scan.address[ cnt ] );
            if ( ( cnt + 1 ) < scan.num_addr )
            {
                log_printf ( &logger, ", " );
            }
            else
            {
                log_printf ( &logger, "\r\n" );
            }
        }
    }
    else
    {
        log_printf ( &logger, "No I2C devices found!\r\n" );
    }
    log_printf ( &logger, "-----------------------------\r\n" );
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
