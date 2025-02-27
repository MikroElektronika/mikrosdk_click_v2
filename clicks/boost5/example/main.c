/*!
 * @file main.c
 * @brief Boost 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Boost 5 Click board by enabling the device
 * and continuously reading and logging the measured output voltage (VOUT).
 * If a failure is detected during voltage reading, the device is reset.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Boost 5 Click board. Configures the ADC for voltage
 * measurements and enables the device to prepare it for operation.
 *
 * ## Application Task
 * Reads the output voltage level and logs it on the USB UART. In case of an error during
 * the reading process, or the user changes VOUT using an on-board VOUT SEL switch,
 * the device is reset to recover from potential issues or to apply new settings.
 *
 * @note
 * The VOUT is configured using an on-board VOUT SEL 4-position switch.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "boost5.h"

static boost5_t boost5;   /**< Boost 5 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost5_cfg_t boost5_cfg;  /**< Click config object. */

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
    boost5_cfg_setup( &boost5_cfg );
    BOOST5_MAP_MIKROBUS( boost5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == boost5_init( &boost5, &boost5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "\r\n Enable device\r\n\n" );
    boost5_enable_device ( &boost5 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float vout = 0;
    if ( BOOST5_OK == boost5_read_vout ( &boost5, &vout ) ) 
    {
        log_printf( &logger, "\r\n VOUT : %.3f V\r\n", vout );
    }
    else
    {
        log_printf( &logger, "\r\n Reset device\r\n" );
        boost5_reset_device ( &boost5 );
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
