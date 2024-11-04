/*!
 * @file main.c
 * @brief Current6 Click example
 *
 * # Description
 * This example demonstrates the use of Current 6 Click board by reading 
 * the input voltage and current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for the FIFO data interrupt and then reads the measurements of
 * the input voltage and current and displays the results on the USB UART 
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current6.h"

static current6_t current6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current6_cfg_t current6_cfg;  /**< Click config object. */

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
    current6_cfg_setup( &current6_cfg );
    CURRENT6_MAP_MIKROBUS( current6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current6_init( &current6, &current6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT6_ERROR == current6_default_cfg ( &current6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( current6_get_alert_pin ( &current6 ) )
    {
        uint16_t status;
        if ( CURRENT6_OK == current6_get_status ( &current6, &status ) )
        {
            if ( status & CURRENT6_FIFO_CFG_DATA_OVERFLOW_MASK )
            {
                float voltage, current;
                if ( CURRENT6_OK == current6_read_data ( &current6, &voltage, &current ) )
                {
                    log_printf( &logger, " Voltage: %.3f V\r\n Current: %.3f A\r\n\n", voltage, current );
                }
            }
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
