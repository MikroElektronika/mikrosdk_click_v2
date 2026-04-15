/*!
 * @file main.c
 * @brief Light 6 Click example
 *
 * # Description
 * This example demonstrates the use of the Light 6 Click board, which measures 
 * ambient light and infrared (IR) intensity. The application initializes the device 
 * and continuously reads ALS and IR data, displaying the results via UART logging.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and configures the Light 6 Click board. It establishes 
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
#include "light6.h"

static light6_t light6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light6_cfg_t light6_cfg;  /**< Click config object. */

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
    light6_cfg_setup( &light6_cfg );
    LIGHT6_MAP_MIKROBUS( light6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light6_init( &light6, &light6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT6_ERROR == light6_default_cfg ( &light6 ) )
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
    if ( LIGHT6_OK == light6_get_data ( &light6, &als_data, &ir_data ) )
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
