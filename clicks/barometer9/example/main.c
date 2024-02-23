/*!
 * @file main.c
 * @brief Barometer 9 Click example
 *
 * # Description
 * This example demonstrates the use of  Barometer 9  Click board 
 * by reading and displaying the pressure and temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the Pressure [Pa] and Temperature [degree Celsius] data.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer9.h"

static barometer9_t barometer9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer9_cfg_t barometer9_cfg;  /**< Click config object. */

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
    barometer9_cfg_setup( &barometer9_cfg );
    BAROMETER9_MAP_MIKROBUS( barometer9_cfg, MIKROBUS_1 );
    err_t init_flag = barometer9_init( &barometer9, &barometer9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( BAROMETER9_ERROR == barometer9_default_cfg ( &barometer9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint16_t device_id = 0;
    barometer9_read_part_id ( &barometer9, &device_id );
    if ( BAROMETER9_DEVICE_ID != device_id )
    {
        log_error( &logger, " Read error " );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, " Device ID: 0x%.4X \r\n", device_id );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    float pressure = 0;

    barometer9_get_temperature( &barometer9, &temperature );
    barometer9_get_pressure( &barometer9, &pressure );
    log_printf( &logger, " Temperature: %.2f C \r\n Pressure %.3f Pa \r\n", temperature, pressure );
    log_printf( &logger, " - - - - - - - - - - \r\n" );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
