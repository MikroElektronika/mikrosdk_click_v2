/*!
 * @file main.c
 * @brief Altitude6 Click example
 *
 * # Description
 * This library contains API for Altitude 6 Click driver.
 * The demo application reads and calculate 
 * temperature, pressure and altitude data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C or SPI driver and log UART.
 * After driver initialization the app set 
 * driver interface setup and  default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Altitude 6 Click board™.
 * In this example, display the Altitude ( m ), 
 * Pressure ( mBar ) and Temperature ( degree Celsius ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "altitude6.h"

static altitude6_t altitude6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    altitude6_cfg_t altitude6_cfg;  /**< Click config object. */

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
    altitude6_cfg_setup( &altitude6_cfg );
    altitude6_drv_interface_selection( &altitude6_cfg, ALTITUDE6_DRV_SEL_I2C );
    ALTITUDE6_MAP_MIKROBUS( altitude6_cfg, MIKROBUS_1 );
    err_t init_flag  = altitude6_init( &altitude6, &altitude6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ALTITUDE6_ERROR == altitude6_default_cfg ( &altitude6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    static float temperature;
    static float pressure;
    static float altitude;
    
    if ( altitude6_get_data( &altitude6, &temperature, &pressure, &altitude ) == ALTITUDE6_OK )
    {
        log_printf( &logger, " Altitude    : %.2f m       \r\n", altitude );
        log_printf( &logger, " Pressure    : %.2f mbar    \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f C       \r\n", temperature );
        log_printf( &logger, "----------------------------\r\n" );   
    }
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
