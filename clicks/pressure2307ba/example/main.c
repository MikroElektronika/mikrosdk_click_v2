/*!
 * @file main.c
 * @brief Pressure 23 07BA Click example
 *
 * # Description
 * This example demonstrates the use of Pressure 23 07BA Click board by reading and displaying
 * the pressure and temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the Pressure [mBar] 
 * and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "pressure2307ba.h"

static pressure2307ba_t pressure2307ba;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure2307ba_cfg_t pressure2307ba_cfg;  /**< Click config object. */

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
    pressure2307ba_cfg_setup( &pressure2307ba_cfg );
    PRESSURE2307BA_MAP_MIKROBUS( pressure2307ba_cfg, MIKROBUS_1 );
    err_t init_flag = pressure2307ba_init( &pressure2307ba, &pressure2307ba_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE2307BA_ERROR == pressure2307ba_default_cfg ( &pressure2307ba ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " _______________________ \r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    static float temperature, pressure;
    if ( PRESSURE2307BA_OK == pressure2307ba_get_measurement_data( &pressure2307ba, &pressure, &temperature ) )
    {
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " _______________________ \r\n" );
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
