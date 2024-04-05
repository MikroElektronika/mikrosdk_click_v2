/*!
 * @file main.c
 * @brief Ambient 21 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 21 click board by measuring 
 * the ambient light level in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the ambient light level in Lux
 * and displays the results on the USB UART. By default, the data ready interrupt triggers 
 * upon every ADC cycle which occurs every 200ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient21.h"

static ambient21_t ambient21;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient21_cfg_t ambient21_cfg;  /**< Click config object. */

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
    ambient21_cfg_setup( &ambient21_cfg );
    AMBIENT21_MAP_MIKROBUS( ambient21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient21_init( &ambient21, &ambient21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT21_ERROR == ambient21_default_cfg ( &ambient21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t lux;
    if ( !ambient21_get_int_pin ( &ambient21 ) )
    {
        if ( AMBIENT21_OK == ambient21_measure_light_level ( &ambient21, &lux ) )
        {
            log_printf ( &logger, " Ambient light level [Lux]: %u\r\n\n", lux );
        }
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
