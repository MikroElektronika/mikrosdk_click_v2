/*!
 * @file main.c
 * @brief eFuse 4 Click example
 *
 * # Description
 * This library contains API for the eFuse 4 Click driver.
 * This driver provides the functions to set the current limiting conditions 
 * in order to provide the threshold of the fault conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the eFuse 4 Click board™.
 * Reading user's input from UART Terminal and using it as an index 
 * for an array of pre-calculated values that define the current limit level.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "efuse4.h"

static efuse4_t efuse4;
static log_t logger;

const efuse4_current_limit_t limit_value_op[ 7 ] = 
{ 
    EFUSE4_CURRENT_LIMIT_670_mA, 
    EFUSE4_CURRENT_LIMIT_750_mA,
    EFUSE4_CURRENT_LIMIT_990_mA,
    EFUSE4_CURRENT_LIMIT_2080_mA, 
    EFUSE4_CURRENT_LIMIT_3530_mA,
    EFUSE4_CURRENT_LIMIT_4450_mA,
    EFUSE4_CURRENT_LIMIT_5200_mA,
};

static void display_selection ( void ) 
{
    log_printf( &logger, "  To select current limit  \r\n" );
    log_printf( &logger, "  Send one of the numbers: \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " '0' - Limited to  670 mA  \r\n" );
    log_printf( &logger, " '1' - Limited to  750 mA  \r\n" );
    log_printf( &logger, " '2' - Limited to  990 mA  \r\n" );
    log_printf( &logger, " '3' - Limited to 2080 mA  \r\n" );
    log_printf( &logger, " '4' - Limited to 3530 mA  \r\n" );
    log_printf( &logger, " '5' - Limited to 4450 mA  \r\n" );
    log_printf( &logger, " '6' - Limited to 5200 mA  \r\n" );  
    log_printf( &logger, "---------------------------\r\n" );
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse4_cfg_t efuse4_cfg;  /**< Click config object. */

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
    efuse4_cfg_setup( &efuse4_cfg );
    EFUSE4_MAP_MIKROBUS( efuse4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == efuse4_init( &efuse4, &efuse4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE4_ERROR == efuse4_default_cfg ( &efuse4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
    
    display_selection( );
    Delay_ms( 100 );
}

void application_task ( void ) 
{  
    static char index;
    
    if ( EFUSE4_ERROR != log_read( &logger, &index, 1 ) ) 
    {
        if ( ( index >= '0' ) && ( index <= '6' ) ) 
        {
            efuse4_set_current_limit ( &efuse4, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 48 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms( 100 );
        }
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "---------------------------\r\n" );
            display_selection( );
            Delay_ms( 100 );
        }
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
