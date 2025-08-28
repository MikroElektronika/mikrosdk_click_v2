/*!
 * @file main.c
 * @brief Barometer 11 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Barometer 11 Click board by initializing
 * the device and reading the barometric pressure data in millibar units.
 * The pressure value is periodically logged to the USB UART every second.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Barometer 11 Click driver.
 *
 * ## Application Task
 * Reads and displays the pressure data every second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer11.h"

static barometer11_t barometer11;   /**< Barometer 11 Click driver object. */
static log_t logger;                /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer11_cfg_t barometer11_cfg;  /**< Click config object. */

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
    barometer11_cfg_setup( &barometer11_cfg );
    BAROMETER11_MAP_MIKROBUS( barometer11_cfg, MIKROBUS_1 );
    err_t init_flag = barometer11_init( &barometer11, &barometer11_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float pressure = 0;
    if ( BAROMETER11_OK == barometer11_read_pressure ( &barometer11, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %.1f mBar\r\n\n", pressure );
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
