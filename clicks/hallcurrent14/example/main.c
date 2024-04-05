/*!
 * @file main.c
 * @brief Hall Current 14 Click Example.
 *
 * # Description
 * This example demonstrates the use of Hall Current 14 click board by reading and
 * displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the input current measurements and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent14.h"

static hallcurrent14_t hallcurrent14;   /**< Hall Current 14 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent14_cfg_t hallcurrent14_cfg;  /**< Click config object. */

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
    hallcurrent14_cfg_setup( &hallcurrent14_cfg );
    HALLCURRENT14_MAP_MIKROBUS( hallcurrent14_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent14_init( &hallcurrent14, &hallcurrent14_cfg );
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
    if ( HALLCURRENT14_OK == hallcurrent14_read_current ( &hallcurrent14, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", current );
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
