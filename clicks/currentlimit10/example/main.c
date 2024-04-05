/*!
 * @file main.c
 * @brief Current Limit 10 Click example
 *
 * # Description
 * This library contains API for the Current Limit 10 Click driver.
 * This driver provides the functions to set the current limiting conditions 
 * in order to provide the threshold of the fault conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration
 * and and sets the current limit threshold of 750 mA.
 *
 * ## Application Task
 * This example demonstrates the use of the Current Limit 10 Click board. 
 * The demo application checks the fault flag for overcurrent conditions.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "currentlimit10.h"

static currentlimit10_t currentlimit10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit10_cfg_t currentlimit10_cfg;  /**< Click config object. */

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
    currentlimit10_cfg_setup( &currentlimit10_cfg );
    CURRENTLIMIT10_MAP_MIKROBUS( currentlimit10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit10_init( &currentlimit10, &currentlimit10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT10_ERROR == currentlimit10_default_cfg ( &currentlimit10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    if ( CURRENTLIMIT10_ERROR == currentlimit10_set_limit( &currentlimit10, 0.75 ) )
    {
        log_error( &logger, " Current limit threshold." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    if ( CURRENTLIMIT10_FAULT_FLAG == currentlimit10_get_fault( &currentlimit10 ) )
    {
        log_printf( &logger, "Fault flag: Overcurrent\r\n" );
    }
    else
    {
        log_printf( &logger, " Current limit is 0.75 A\r\n" );
    }
    Delay_ms ( 1000 );
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
