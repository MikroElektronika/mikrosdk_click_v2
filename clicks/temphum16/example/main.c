/*!
 * @file main.c
 * @brief TempHum16 Click example
 *
 * # Description
 * This library contains API for the Temp&Hum 16 Click driver.
 * This demo application shows an example of 
 * humidity and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI or I2C module and log UART.
 * After driver initialization and default settings, 
 * the app display retrieves the sensor parameters 
 * such as temperature and humidity.
 *
 * ## Application Task
 * This is an example that shows the use of a Temp&Hum 16 Click board™.
 * Logs humidity [ % ] and temperature [ degree Celsius ] data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum16.h"

static temphum16_t temphum16;
static log_t logger;
static uint8_t device_id;
static float humidity;
static float temperature;


void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    temphum16_cfg_t temphum16_cfg;  /**< Click config object. */

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

    temphum16_cfg_setup( &temphum16_cfg );
    TEMPHUM16_MAP_MIKROBUS( temphum16_cfg, MIKROBUS_1 );
    err_t init_flag  = temphum16_init( &temphum16, &temphum16_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) {
        log_info( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    temphum16_default_cfg ( &temphum16 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );

    temphum16_get_device_id( &temphum16, &device_id );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Check communication  \r\n" ); 
    if ( device_id == TEMPHUM16_DEVICE_ID ){
        log_printf( &logger, "      Successful   \r\n" );    
    } else {
        log_printf( &logger, "        Failed     \r\n" );
        
        for ( ; ; );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   Start measurements  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void ) {
    if ( temphum16_check_ready( &temphum16 ) == TEMPHUM16_DRDY ) {
        temphum16_get_temperature( &temphum16, &temperature );
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature ); 
        
        temphum16_get_humidity( &temphum16, &humidity );
        log_printf( &logger, " Humidity    : %.2f %%\r\n", humidity ); 
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms( 1000 );
    }
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
