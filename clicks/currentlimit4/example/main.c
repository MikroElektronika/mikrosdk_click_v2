/*!
 * @file main.c
 * @brief Current Limit 4 Click Example.
 *
 * # Description
 * This library contains API for the Current Limit 4 Click driver 
 * for the current limiting to a certain value and 
 * displays the sources a current proportional to the load current [A].
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C and ADC module and log UART.
 * After driver initialization, the app executes a default configuration 
 * and set the minimum current limit threshold to 1.0 [A].
 *
 * ## Application Task
 * This example demonstrates the use of the Current Limit 4 Click board. 
 * The demo application displays the source current proportional to the load current
 * and an appropriate message when the current reaches the limit.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "currentlimit4.h"

static currentlimit4_t currentlimit4;   /**< Current Limit 4 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit4_cfg_t currentlimit4_cfg;  /**< Click config object. */

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
    currentlimit4_cfg_setup( &currentlimit4_cfg );
    CURRENTLIMIT4_MAP_MIKROBUS( currentlimit4_cfg, MIKROBUS_1 );
    err_t init_flag = currentlimit4_init( &currentlimit4, &currentlimit4_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT4_ERROR == currentlimit4_default_cfg ( &currentlimit4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    static float current = 0;
    if ( CURRENTLIMIT4_OK == currentlimit4_get_current( &currentlimit4, &current ) ) 
    {
        if ( CURRENTLIMIT4_POWER_GOOD == currentlimit4_get_power_good( &currentlimit4 ) )
        {
            log_printf( &logger, " Current : %.3f [A]\r\n", current );
        }
        else
        {
            log_printf( &logger, " Input voltage is lower then undervoltage protection threshold.\r\n" );
        }
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
