/*!
 * @file main.c
 * @brief AC Current 2 Click Example.
 *
 * # Description
 * This example demonstrates how to use the AC Current 2 Click board for reading
 * the measurements from the AC Current sensor attached to the Click board input.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Continuously reads the AC current value and logs the measured data in amperes (A).
 *
 * @note
 * The AC Current sensor [MIKROE-2524] required for this Click board should
 * have a specification of 30A/1A.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accurrent2.h"

static accurrent2_t accurrent2;   /**< AC Current 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accurrent2_cfg_t accurrent2_cfg;  /**< Click config object. */

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
    accurrent2_cfg_setup( &accurrent2_cfg );
    ACCURRENT2_MAP_MIKROBUS( accurrent2_cfg, MIKROBUS_1 );
    err_t init_flag = accurrent2_init( &accurrent2, &accurrent2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    if ( ACCURRENT2_OK == accurrent2_read_current ( &accurrent2, &current ) ) 
    {
        log_printf( &logger, " AC Current : %.3f A\r\n\n", current );
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
