/*!
 * @file main.c
 * @brief Ambient 24 Click example
 *
 * # Description
 * This example demonstrates the use of the Ambient 24 Click board, which measures 
 * ambient light and infrared (IR) intensity. The application initializes the device 
 * and continuously reads ALS and IR data, displaying the results via UART logging.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the Ambient 24 Click board. It establishes 
 * I2C communication and applies the default configuration settings.
 *
 * ## Application Task
 * Continuously reads ambient light and infrared sensor data and logs the results 
 * in lux and raw IR values, respectively. The readings are updated every 200ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient24.h"

static ambient24_t ambient24;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient24_cfg_t ambient24_cfg;  /**< Click config object. */

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
    ambient24_cfg_setup( &ambient24_cfg );
    AMBIENT24_MAP_MIKROBUS( ambient24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient24_init( &ambient24, &ambient24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT24_ERROR == ambient24_default_cfg ( &ambient24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float als_data = 0;
    uint16_t ir_data = 0;
    if ( AMBIENT24_OK == ambient24_get_data ( &ambient24, &als_data, &ir_data ) )
    {
        log_printf ( &logger, " ALS Data: %.1f lux\r\n", als_data );
        log_printf ( &logger, " IR Data: %u\r\n\n", ir_data );
        Delay_ms ( 200 );
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
