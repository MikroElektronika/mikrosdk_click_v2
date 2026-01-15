/*!
 * @file main.c
 * @brief PIR 4 Click example
 *
 * # Description
 * This example demonstrates how to read motion-detection data from
 * the PIR 4 Click board using either continuous output mode or
 * upper/lower counter mode, depending on the configuration.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the PIR 4 Click driver, then applies
 * the default configuration.
 *
 * ## Application Task
 * Continuously reads motion-detection data.  
 * In continuous mode, raw PIR output is logged for plotting.  
 * In counter mode, upper and lower event counts are displayed.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pir4.h"

static pir4_t pir4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pir4_cfg_t pir4_cfg;  /**< Click config object. */

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
    pir4_cfg_setup( &pir4_cfg );
    PIR4_MAP_MIKROBUS( pir4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pir4_init( &pir4, &pir4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIR4_ERROR == pir4_default_cfg ( &pir4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( PIR4_INT_SEL_DEFAULT == PIR4_INT_SEL_CONTINUOUS_OUT )
    int16_t pir_out = 0;
    if ( PIR4_OK == pir4_read_continuous_out ( &pir4, &pir_out ) )
    {
        // Use serial plotter to visualize data
        log_printf ( &logger, "%d\r\n", pir_out );
    }
#else
    uint8_t oc_upper = 0;
    uint8_t oc_lower = 0;
    if ( PIR4_OK == pir4_read_out ( &pir4, &oc_upper, &oc_lower ) )
    {
        log_printf ( &logger, " Motion detected! Upper count: %u, lower count: %u\r\n\n", 
                     ( uint16_t ) oc_upper, ( uint16_t ) oc_lower );
    }
#endif
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
