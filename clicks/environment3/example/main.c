/*!
 * @file main.c
 * @brief Environment3 Click example
 *
 * # Description
 * This example demonstrates the use of Environment 3 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, sets the default configuration, and disables the gas sensor heater.
 *
 * ## Application Task
 * Reads the temperature, humidity, pressure, and gas resistance data from the sensor and 
 * displays all values on the USB UART approximately every second.
 *
 * @note
 * The heater is disabled by default, enable it in the Application Init if you need gas resistance data.
 * Gas resistance data is RAW data, if you need VOCs, please contact Bosch Sensortec for VOC calculation library.
 * The temperature and humidity data don't represent the real environmental data when the heater is enabled.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "environment3.h"

static environment3_t environment3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    environment3_cfg_t environment3_cfg;  /**< Click config object. */

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

    environment3_cfg_setup( &environment3_cfg );
    ENVIRONMENT3_MAP_MIKROBUS( environment3_cfg, MIKROBUS_1 );
    err_t init_flag  = environment3_init( &environment3, &environment3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( ENVIRONMENT3_OK != environment3_default_cfg ( &environment3 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    environment3_enable_heater ( &environment3, ENVIRONMENT3_DISABLE );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature, pressure, humidity;
    uint32_t gas_resistance;
    if ( ENVIRONMENT3_OK == environment3_get_all_data ( &environment3, 
                                                        &temperature, 
                                                        &humidity, 
                                                        &pressure, 
                                                        &gas_resistance ) )
    {
        log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    
        log_printf( &logger, " Humidity : %.2f %%\r\n", humidity );
        
        log_printf( &logger, " Pressure : %.3f mBar\r\n", pressure );
        
        if ( ENVIRONMENT3_ENABLE == environment3.gas_sett.enable )
        {
            log_printf( &logger, " Gas Resistance : %ld Ohms\r\n", gas_resistance );
            log_printf( &logger, "--------------------------------\r\n" );
        }
        else
        {
            log_printf( &logger, "--------------------------------\r\n" );
            Delay_ms( 1000 );
        }
    }
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
