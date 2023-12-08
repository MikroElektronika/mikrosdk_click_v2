/*!
 * @file main.c
 * @brief Pressure16 Click example
 *
 * # Description
 * This library contains API for the Pressure 16 Click driver.
 * This demo application shows an example of pressure and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C and SPI module and log UART.
 * After driver initialization and default settings, 
 * the app display retrieves the sensor parameters 
 * such as pressure and temperature.
 *
 * ## Application Task
 * This is an example that shows the use of a Pressure 16 Click board™.
 * Logs the pressure [ mbar ] and temperature [ degree Celsius ] data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure16.h"

static pressure16_t pressure16;
static log_t logger;
static uint8_t device_id;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    pressure16_cfg_t pressure16_cfg;  /**< Click config object. */

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
    pressure16_cfg_setup( &pressure16_cfg );
    PRESSURE16_MAP_MIKROBUS( pressure16_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure16_init( &pressure16, &pressure16_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    pressure16_default_cfg ( &pressure16 );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    
    pressure16_get_device_id( &pressure16, &device_id );
    if ( device_id == PRESSURE16_DEVICE_ID ) {
        log_info( &logger, " Communication OK" );    
    } else {
        log_info( &logger, " Communication ERROR" ); 
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Start measuring\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static float pressure, temperature;
    
    pressure16_get_press_temp( &pressure16, &pressure, &temperature );
    log_printf( &logger, " Pressure    : %.2f mbar \r\n", pressure );
    log_printf( &logger, " Temperature :  %.2f C \r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" ); 
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
