/*!
 * @file main.c
 * @brief Altitude5 Click example
 *
 * # Description
 * This library contains API for Altitude 5 Click driver.
 * The demo application reads ADC value, calculate pressure and altitude.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C or analog driver and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Altitude 5 Click board™.
 * In this example, we read ADC values and 
 * display the Pressure ( mBar ) and Altitude ( m ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "altitude5.h"

static altitude5_t altitude5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    altitude5_cfg_t altitude5_cfg;  /**< Click config object. */

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
    altitude5_cfg_setup( &altitude5_cfg );
    ALTITUDE5_MAP_MIKROBUS( altitude5_cfg, MIKROBUS_1 );
    err_t init_flag = altitude5_init( &altitude5, &altitude5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    altitude5_default_cfg ( &altitude5 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static float pressure;
    static float altitude;
    
    altitude5_get_pressure( &altitude5, &pressure );
    log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
    Delay_ms( 100 );
    
    altitude5_get_altitude( &altitude5, &altitude );
    log_printf( &logger, " Altitude    : %.2f m \r\n", altitude );
    log_printf( &logger, "----------------------------\r\n" );
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
