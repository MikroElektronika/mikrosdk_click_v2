/*!
 * @file main.c
 * @brief Charger 19 Click Example.
 *
 * # Description
 * This example demonstrates the use of Charger 19 click board by enabling the device
 * and then reading and displaying the battery voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the device, sets the output 
 * voltage to 3 V.
 *
 * ## Application Task
 * Tracking charging status, reading battery voltage.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "charger19.h"

static charger19_t charger19;   /**< Charger 19 Click driver object. */
static log_t logger;            /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    charger19_cfg_t charger19_cfg;  /**< Click config object. */

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
    charger19_cfg_setup( &charger19_cfg );
    CHARGER19_MAP_MIKROBUS( charger19_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == charger19_init( &charger19, &charger19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER19_ERROR == charger19_default_cfg ( &charger19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( CHARGER19_OK == charger19_get_vbat ( &charger19, &voltage ) ) 
    {
        log_printf( &logger, " Battery Voltage : %.3f[V]\r\n\n", voltage );
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
