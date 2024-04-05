/*!
 * \file 
 * \brief ThermoK Click example
 * 
 * # Description
 * Demo application shows basic temperature reading using Thermo K click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Reads the device ID and also checks the click and MCU communication.
 * 
 * ## Application Task  
 * Reads Temperature data(Type K probe) and this data logs to USBUART every 500ms.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermok.h"

// ------------------------------------------------------------------ VARIABLES

static thermok_t thermok;
static log_t logger;

static uint16_t device_info;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermok_cfg_t cfg;

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

    thermok_cfg_setup( &cfg );
    THERMOK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermok_init( &thermok, &cfg );

    // Check communication and reads device ID

    device_info = thermok_get_device_info( &thermok );

    if ( ( device_info >> 8 ) == THERMOK_DEVICE_ID )
    {
        log_info(&logger, "---- Communication OK!!! ----" );
    }
    else
    {
        log_info(&logger, "---- Communication ERROR!!! ----" );
        for ( ; ; );
    }
    Delay_1sec( );
}

void application_task ( void )
{
    float temperature;

    //  Task implementation.

    temperature = thermok_get_temperature( &thermok, 
                                           THERMOK_REG_HOT_JUNCTION_TEMP_THR, 
                                           THERMOK_TEMP_IN_CELSIUS );
    log_printf( &logger, ">> Temperature is %.2f C\r\n", temperature );

    Delay_ms ( 1000 );
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
