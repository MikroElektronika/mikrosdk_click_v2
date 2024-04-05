/*!
 * @file main.c
 * @brief HeartRate7 Click example
 *
 * # Description
 * This example showcases ability for device to read Heart Rate 7 Click Board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configures the micro controller for communication and initializes the click board. 
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
#include "heartrate7.h"

static heartrate7_t heartrate7;
static log_t logger;
static uint32_t sensor_value;
static uint32_t time = 0;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate7_cfg_t heartrate7_cfg;  /**< Click config object. */

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
    heartrate7_cfg_setup( &heartrate7_cfg );
    HEARTRATE7_MAP_MIKROBUS( heartrate7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate7_init( &heartrate7, &heartrate7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE7_ERROR == heartrate7_default_cfg ( &heartrate7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    sensor_value = heartrate7_get_aled1_val( &heartrate7 );
    log_printf( &logger, "%lu,%lu \r\n", sensor_value, time );
    time += 10;
    Delay_ms ( 10 );
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
