/*!
 * \file 
 * \brief UART1Wire Click example
 * 
 * # Description
 * This example reads and processes data from UART 1-Wire Clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger.
 * 
 * ## Application Task  
 * Reads the temperature data from DALLAS temperature sensors and logs the results
 * on the USB UART every second.
 * 
 * @note
 * Connect only DQ and GND pins to the UART 1-Wire Click connector.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uart1wire.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static uart1wire_t uart1wire;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uart1wire_cfg_t cfg;

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

    uart1wire_cfg_setup( &cfg );
    UART1WIRE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uart1wire_init( &uart1wire, &cfg );
    
    Delay_ms ( 100 );
}

void application_task ( void )
{
    float temp_f;
    uint8_t res_flag;
    
    res_flag = uart1wire_read_temperature ( &uart1wire, &temp_f, UART1WIRE_TEMP_SENSOR_RESOLUTION_9BIT );
    if ( res_flag == UART1WIRE_OK )
    {
        log_printf( &logger, " * Temperature:     %.2f C\r\n", temp_f );
        log_printf( &logger, "------------------------------\r\n" );
        Delay_ms ( 1000 );
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
