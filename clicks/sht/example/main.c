/*!
 * \file 
 * \brief Sht Click example
 * 
 * # Description
 * This application enables usage of the temperature and humidity sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize the communication interface and configure the click board.
 * 
 * ## Application Task  
 * Temperature and humidity data is measured and read from the sensor. 
 * After the data has been read it is displayed on the serial port.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "sht.h"

// ------------------------------------------------------------------ VARIABLES

static sht_t sht;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    sht_cfg_t cfg;

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

    //  Click initialization.
    sht_cfg_setup( &cfg );
    SHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sht_init( &sht, &cfg );
    
    sht_reset( &sht );
    sht_hw_reset( &sht );
    Delay_ms( 2000 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    temperature = sht_temp_ss( &sht );
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    humidity = sht_hum_ss( &sht );
    log_printf( &logger, " Humidity: %.2f %%\r\n\n", humidity );

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
