/*!
 * @file main.c
 * @brief Barometer4 Click example
 *
 * # Description
 * This library contains API for the Barometer 4 Click driver.
 * The library initializes and defines the I2C bus drivers 
 * to write and read data from registers.
 * This demo application shows an example of 
 * atmospheric pressure and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module and log UART.
 * After driver initialization and default settings, 
 * the app display device ID.
 *
 * ## Application Task
 * This is an example that shows the use of a Barometer 4 Click board™.
 * Logs the atmospheric pressure [ Pa ] and temperature [ degree Celsius ] data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer4.h"

static barometer4_t barometer4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    barometer4_cfg_t barometer4_cfg;  /**< Click config object. */

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
    barometer4_cfg_setup( &barometer4_cfg );
    BAROMETER4_MAP_MIKROBUS( barometer4_cfg, MIKROBUS_1 );
    err_t init_flag = barometer4_init( &barometer4, &barometer4_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    barometer4_default_cfg ( &barometer4 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 100 );
    
    static uint16_t device_id;
    err_t err_flag = barometer4_get_device_id( &barometer4, &device_id );
    if ( BAROMETER4_ERROR == err_flag ) 
    {
        log_error( &logger, " Communication Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Device ID   : 0x%.4X \r\n", device_id );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void ) 
{  
    static float pressure;
    static float temperature;
    
    barometer4_get_pressure_and_temperature( &barometer4, &pressure, &temperature );
    log_printf( &logger, " Pressure    : %.2f Pa\r\n", pressure );
    log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
