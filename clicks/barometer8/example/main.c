/*!
 * @file main.c
 * @brief Barometer8 Click example
 *
 * # Description
 * This example demonstrates the use of Barometer 8 click board by reading and
 * displaying the pressure and temperature values.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and displays the pressure and temperature data on the USB UART every 250ms approximately,
 * as per output data rate (ODR) bits configuration.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer8.h"

static barometer8_t barometer8;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer8_cfg_t barometer8_cfg;  /**< Click config object. */

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
    barometer8_cfg_setup( &barometer8_cfg );
    BAROMETER8_MAP_MIKROBUS( barometer8_cfg, MIKROBUS_1 );
    err_t init_flag  = barometer8_init( &barometer8, &barometer8_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER8_ERROR == barometer8_default_cfg ( &barometer8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float pressure, temperature;
    if ( BAROMETER8_OK == barometer8_read_data ( &barometer8, &pressure, &temperature ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    Delay_ms ( 5 );
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
