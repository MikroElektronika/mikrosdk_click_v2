/*!
 * \file 
 * \brief Htu21d Click example
 * 
 * # Description
 * The application is composed of two sections.
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, soft reset switch OFF
 * and ON the HTU21D sensor,hold ( required ) 
 * after reset 100 [ ms ] and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of
 * HTU21D Click board.Measured temperature and humidity 
 * data from the HDC1000 sensor.Convert temperature data
 * to degrees Celsius and humidity data to percentarg.
 * Results are being sent to the Usart Terminal
 * where you can track their changes.
 * All data logs on usb uart for aproximetly every 3 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "htu21d.h"

// ------------------------------------------------------------------ VARIABLES

static htu21d_t htu21d;
static log_t logger;
static float temperature;
static float humidity;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    htu21d_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    htu21d_cfg_setup( &cfg );
    HTU21D_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    htu21d_init( &htu21d, &cfg );
    
    htu21d_send_cmd ( &htu21d, HTU21D_SOFT_RESET );
    Delay_ms ( 500 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "         HTU21D\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.
    temperature = htu21d_get_temperature( &htu21d );
    log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
    
    humidity = htu21d_get_humidity( &htu21d );
    log_printf( &logger, " Humidity    : %.2f %%\r\n", humidity );
    log_printf( &logger, "-----------------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
