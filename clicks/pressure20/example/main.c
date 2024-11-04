/*!
 * @file main.c
 * @brief Pressure20 Click example
 *
 * # Description
 * This example demonstrates the use of Pressure 20 Click board by reading and displaying
 * the pressure and temperature data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, clears the interrupts and than reads 
 * the pressure [mBar] and temperature [Celsius] data and displays them on the USB UART 
 * at the set output data rate (25Hz by default).
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure20.h"

static pressure20_t pressure20;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure20_cfg_t pressure20_cfg;  /**< Click config object. */

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
    pressure20_cfg_setup( &pressure20_cfg );
    PRESSURE20_MAP_MIKROBUS( pressure20_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure20_init( &pressure20, &pressure20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE20_ERROR == pressure20_default_cfg ( &pressure20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    // Wait for the data ready interrupt
    while ( pressure20_get_int_pin ( &pressure20 ) );
    float pressure, temperature;
    if ( ( PRESSURE20_OK == pressure20_clear_interrupts ( &pressure20 ) ) &&
         ( PRESSURE20_OK == pressure20_read_data ( &pressure20, &pressure, &temperature ) ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
