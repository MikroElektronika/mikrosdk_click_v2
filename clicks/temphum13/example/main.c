/*!
 * \file 
 * \brief TempHum13 Click example
 * 
 * # Description
 * This demo shows basic TempHum13 click functionality - temperature
 * and humidity measurement. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize device.
 * 
 * ## Application Task  
 * Measure temperature and humidity values on every 0,5 seconds,
 * and log them to UART Terminal if they are valid.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum13.h"

// ------------------------------------------------------------------ VARIABLES

static temphum13_t temphum13;
static log_t logger;

static float temperature;
static float humidity;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum13_cfg_t cfg;

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

    temphum13_cfg_setup( &cfg );
        Delay_ms(500);
    TEMPHUM13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
        Delay_ms(500);
    temphum13_init( &temphum13, &cfg );
        Delay_ms(500);
    
    temphum13_default_cfg( &temphum13 );
}

void application_task ( void )
{
    temperature = temphum13_get_temperature( &temphum13 );
    humidity = temphum13_get_humidity( &temphum13 );
    
    if ( temperature != 65536.0 )
    {
        log_printf( &logger, "\r\n> Temperature : %.2f C", temperature );
    }

    if ( humidity != 65536.0 )
    {       
        log_printf( &logger, "\r\n> Humidity    : %.2f%%RH\r\n", humidity );
    } 

    Delay_ms( 500 );
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
