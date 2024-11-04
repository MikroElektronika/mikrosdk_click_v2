/*!
 * \file 
 * \brief TempHum 3 Click example
 * 
 * # Description
 * This application reads temperature and humidity data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and performs the Click default configuration.
 * 
 * ## Application Task  
 * Reads the temperature and huminidy and logs results to the USB UART every 500 ms.
 * 
 * \author Petar Suknjaja
 *
 */
#include "board.h"
#include "log.h"
#include "temphum3.h"

static temphum3_t temphum3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum3_cfg_t temphum3_cfg;

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
    temphum3_cfg_setup( &temphum3_cfg );
    TEMPHUM3_MAP_MIKROBUS( temphum3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum3_init( &temphum3, &temphum3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    temphum3_default_cfg( &temphum3 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    temperature = temphum3_get_temperature( &temphum3 );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    humidity = temphum3_get_humidity( &temphum3 );
    log_printf( &logger, " Humidity : %.1f %% \r\n", humidity );
    Delay_ms ( 500 );
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
