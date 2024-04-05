/*!
 * \file 
 * \brief TempHum9 Click example
 * 
 * # Description
 * This example demonstrates the use of TempHum 9 click board by reading and displaying
 * the temperature and humidity measurement results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and sends SLEEP and WAKEUP commands.
 * 
 * ## Application Task  
 * Performs simultaneous temperature and relative humidity measurements and logs both values
 * on the USB UART once per second.
 * 
 * \author MikroE Team
 *
 */
#include "board.h"
#include "log.h"
#include "temphum9.h"

static temphum9_t temphum9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum9_cfg_t cfg;

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
    temphum9_cfg_setup( &cfg );
    TEMPHUM9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum9_init( &temphum9, &cfg );
    Delay_ms ( 100 );

    temphum9_send_command( &temphum9, TEMPHUM9_SLEEP );
    Delay_ms ( 500 );
    temphum9_send_command( &temphum9, TEMPHUM9_WAKEUP );
    Delay_ms ( 500 );
    
    log_info( &logger, " Application Task " );
}

void application_task( )
{
    float temperature = 0;
    float humidity = 0;
    
    temhum9_get_data ( &temphum9, TEMPHUM9_NORMAL_MODE, &temperature, &humidity );
    
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    log_printf( &logger, " Relative humidity: %.2f %%\r\n", humidity );
    
    log_printf( &logger, "-----------------------------\r\n" );
    
    Delay_ms ( 1000 );
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
