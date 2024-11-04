/*!
 * @file main.c
 * @brief HeartRate5 Click example
 *
 * # Description
 * This example showcases ability for device to read Heart Rate 5 Click Board
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configures the micro controller for communication and initializes the Click board. 
 *
 * ## Application Task
 * This section shows how the data is processed and sent to the MikroPlot application.
 * 
 * @note For testing this example application SerialPlot was used. 
 * There you can see heart rate graphicly shown.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "heartrate5.h"

static heartrate5_t heartrate5;
static log_t logger;
static uint32_t sensor_value;
static uint32_t time = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate5_cfg_t heartrate5_cfg;  /**< Click config object. */

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
    heartrate5_cfg_setup( &heartrate5_cfg );
    HEARTRATE5_MAP_MIKROBUS( heartrate5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate5_init( &heartrate5, &heartrate5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE5_ERROR == heartrate5_default_cfg ( &heartrate5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if( heartrate5_get_led2_aled2_val( &heartrate5 ) < 10 )
    {
        sensor_value = heartrate5_get_aled1_val( &heartrate5 );
        log_printf( &logger, "%lu,%lu \r\n", sensor_value, time );
        time += 10;
        Delay_ms ( 10 );
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
