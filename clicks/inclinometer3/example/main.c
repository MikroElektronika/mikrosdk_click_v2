/*!
 * @file main.c
 * @brief Inclinometer 3 Click example
 *
 * # Description
 * This library contains API for the Inclinometer 3 Click driver.
 * The library initializes and defines the SPI drivers to 
 * write and read data from registers, as well as the default configuration 
 * for the reading accelerator and temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the SPI module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Inclinometer 3 Click board.
 * Measures and displays acceleration data for the XY-axis [mg] 
 * and temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "inclinometer3.h"

static inclinometer3_t inclinometer3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer3_cfg_t inclinometer3_cfg;  /**< Click config object. */

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
    inclinometer3_cfg_setup( &inclinometer3_cfg );
    INCLINOMETER3_MAP_MIKROBUS( inclinometer3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == inclinometer3_init( &inclinometer3, &inclinometer3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER3_ERROR == inclinometer3_default_cfg ( &inclinometer3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ________________________ \r\n" );
}

void application_task ( void )
{
    float temperature = 0, x_axes = 0, y_axes = 0;
    if ( ( INCLINOMETER3_OK == inclinometer3_get_temperature( &inclinometer3, &temperature ) ) && 
         ( INCLINOMETER3_OK == inclinometer3_get_axes( &inclinometer3, &x_axes, &y_axes ) ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", x_axes );
        log_printf( &logger, " Accel Y: %.2f mg\r\n\r\n", y_axes );
        log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
        log_printf( &logger, " ________________________ \r\n" );
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
