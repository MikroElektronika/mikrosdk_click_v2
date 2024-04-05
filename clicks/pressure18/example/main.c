/*!
 * @file main.c
 * @brief Pressure 18 Click example
 *
 * # Description
 * This example demonstrates the use of Pressure 18 click board by reading and displaying
 * the pressure and temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt and then reads the pressure and temperature data
 * and displays them on the USB UART every 320ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure18.h"

static pressure18_t pressure18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure18_cfg_t pressure18_cfg;  /**< Click config object. */

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
    pressure18_cfg_setup( &pressure18_cfg );
    PRESSURE18_MAP_MIKROBUS( pressure18_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure18_init( &pressure18, &pressure18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE18_ERROR == pressure18_default_cfg ( &pressure18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( pressure18_get_int_pin ( &pressure18 ) )
    {
        float pressure, temperature;
        if ( PRESSURE18_OK == pressure18_read_data ( &pressure18, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure * PRESSURE18_PA_TO_MBAR );
            log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
