/*!
 * @file main.c
 * @brief TempHum17 Click example
 *
 * # Description
 * This library contains API for the Temp&Hum 17 Click driver.
 * This demo application shows an example of 
 * relative humidity and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization and default settings, 
 * the app display retrieves the sensor parameters 
 * such as temperature and relative humidity.
 *
 * ## Application Task
 * This is an example that shows the use of a Temp&Hum 17 Click board™.
 * Logs the temperature [ degree Celsius ] and relative humidity [ % ] data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum17.h"

static temphum17_t temphum17;
static log_t logger;
static float temperature;
static float humidity;
static uint8_t status;

void application_init ( void ) {
    log_cfg_t log_cfg;             /**< Logger config object. */
    temphum17_cfg_t temphum17_cfg;  /**< Click config object. */

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

    temphum17_cfg_setup( &temphum17_cfg );
    TEMPHUM17_MAP_MIKROBUS( temphum17_cfg, MIKROBUS_1 );
    err_t init_flag = temphum17_init( &temphum17, &temphum17_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    temphum17_default_cfg ( &temphum17 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) {
    if ( temphum17_get_temp_hum( &temphum17, TEMPHUM17_RESOLUTION_14_BITS, &temperature, &humidity ) == TEMPHUM17_STATUS_VALID_DATA ) {
        log_printf( &logger, "  Temperature : %.02f C\r\n  Humidity    : %.02f %%\r\n", temperature, humidity );
    } else {
        log_printf( &logger, "     Measurement Error\r\n\tStale Data\r\n" );    
    }
    
    log_printf( &logger, "-------------------------\r\n" );
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
