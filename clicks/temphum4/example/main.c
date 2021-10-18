/*!
 * \file 
 * \brief Temp&Hum4 Click example
 * 
 * # Description
 * This application reads temperature and humidity data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and settings chip mode ACTIVE and configuration Measurement and Interrupt, 
 * then settings maximum / minimum possible Temperature and Huminidy.
 * 
 * ## Application Task  
 * Reads the temperature and huminidy and logs to the USBUART every 500 ms.
 * 
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum4.h"

// ------------------------------------------------------------------ VARIABLES

static temphum4_t temphum4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum4_cfg_t cfg;

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

    //  Click initialization.

    temphum4_cfg_setup( &cfg );
    TEMPHUM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum4_init( &temphum4, &cfg );
    
    temphum4_set_mode( &temphum4, TEMPHUM4_MODE_ACTIVE );
    Delay_ms( 500 );
    
    uint16_t dev_id = temphum4_get_manifacturer_id( &temphum4 );
    log_printf( &logger, " ID[HEX] : 0x%X\r\n", dev_id );
    
    if ( TEMPHUM4_MANUFACTURER_ID != dev_id )
    {
        log_info( &logger, "---- Error Init ----" ); 
        for(;;);
    }
    Delay_ms( 500 );
    
    temphum4_default_cfg( &temphum4 );

    log_info( &logger, "---Temp&Hum 4 Configured---" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    float temperature;
    float humidity;
    
    temperature = temphum4_get_temperature( &temphum4 );
    log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
    humidity = temphum4_get_humidity( &temphum4 );
    log_printf( &logger, " Humidity : %.2f %%\r\n", humidity );
    log_printf( &logger, "*********************************\r\n" );
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
