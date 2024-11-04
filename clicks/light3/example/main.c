/*!
 * @file main.c
 * @brief Light 3 Click example
 *
 * # Description
 * This example demonstrates the use of Light 3 Click board by measuring 
 * the ambient light level in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reading channel 0 ambient light level in lux as soon as it is available 
 * ( once in 1.6 seconds ) and displaying it on the UART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "light3.h"

static light3_t light3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light3_cfg_t light3_cfg;  /**< Click config object. */

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
    light3_cfg_setup( &light3_cfg );
    LIGHT3_MAP_MIKROBUS( light3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light3_init( &light3, &light3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT3_ERROR == light3_default_cfg ( &light3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float lux_data = 0;
    if ( LIGHT3_PIN_STATE_LOW == light3_get_int_pin( &light3 ) )
    { 
        light3_get_ch0_data( &light3, &lux_data );
        log_printf( &logger, "Light level: %f lux \r\n", ( float ) lux_data );
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
