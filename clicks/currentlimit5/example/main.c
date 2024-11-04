/*!
 * @file main.c
 * @brief CurrentLimit5 Click example
 *
 * # Description
 * This example demonstrates the use of Current Limit 5 Click board by limiting
 * the current to a certain value and displaying an appropriate message when the current
 * reaches the limit.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets
 * the current limit to 200mA.
 *
 * ## Application Task
 * Displays the fault indicator state on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "currentlimit5.h"

static currentlimit5_t currentlimit5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit5_cfg_t currentlimit5_cfg;  /**< Click config object. */

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
    currentlimit5_cfg_setup( &currentlimit5_cfg );
    CURRENTLIMIT5_MAP_MIKROBUS( currentlimit5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit5_init( &currentlimit5, &currentlimit5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT5_ERROR == currentlimit5_default_cfg ( &currentlimit5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t currentlimit_ind = 2;
    if ( currentlimit5_get_fault_pin ( &currentlimit5 ) )
    {
        if ( currentlimit_ind != 0 )
        {
            log_printf ( &logger, " The switch is in normal operation \r\n\n" );
            currentlimit_ind = 0;
        }
    }
    else
    {
        if ( currentlimit_ind != 1 )
        {
            log_printf ( &logger, " The switch is in the current limiting or thermal shutdown operation \r\n\n" );
            currentlimit_ind = 1;
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
