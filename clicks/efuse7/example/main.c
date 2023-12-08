/*!
 * @file main.c
 * @brief eFuse 7 Click Example.
 *
 * # Description
 * This library contains API for the eFuse 7 Click driver.
 * This driver provides the functions to set the current limiting conditions 
 * in order to provide the threshold of the fault conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of click module and UART log, then performing default 
 * configuration and setting a current limit to 1 A.
 *
 * ## Application Task
 * This example demonstrates the use of the eFuse 7 Click board.
 * Reading user's input from UART Terminal and using it as an index 
 * for an array of pre-calculated values that define the current limit level.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "efuse7.h"

static efuse7_t efuse7;   /**< eFuse 7 Click driver object. */
static log_t logger;      /**< Logger object. */

const uint8_t limit_value_op[ 8 ] = 
{ 
    EFUSE7_CURRENT_LIMIT_1A, 
    EFUSE7_CURRENT_LIMIT_2A,
    EFUSE7_CURRENT_LIMIT_2A5,
    EFUSE7_CURRENT_LIMIT_3A, 
    EFUSE7_CURRENT_LIMIT_3A5,
    EFUSE7_CURRENT_LIMIT_4A,
    EFUSE7_CURRENT_LIMIT_4A5,
    EFUSE7_CURRENT_LIMIT_5A,
};

static void display_selection ( void ) 
{
    log_printf( &logger, "  To select current limit  \r\n" );
    log_printf( &logger, "  Send one of the numbers: \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " '0' - Limited to 1   A  \r\n" );
    log_printf( &logger, " '1' - Limited to 2   A  \r\n" );
    log_printf( &logger, " '2' - Limited to 2.5 A  \r\n" );
    log_printf( &logger, " '3' - Limited to 3   A  \r\n" );
    log_printf( &logger, " '4' - Limited to 3.5 A  \r\n" );
    log_printf( &logger, " '5' - Limited to 4   A  \r\n" );
    log_printf( &logger, " '6' - Limited to 4.5 A  \r\n" );  
    log_printf( &logger, " '7' - Limited to 5   A  \r\n" );  
    log_printf( &logger, "---------------------------\r\n" );
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse7_cfg_t efuse7_cfg;  /**< Click config object. */

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
    efuse7_cfg_setup( &efuse7_cfg );
    EFUSE7_MAP_MIKROBUS( efuse7_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == efuse7_init( &efuse7, &efuse7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE7_ERROR == efuse7_default_cfg ( &efuse7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    display_selection( );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static char index;
    
    if ( 1 == log_read( &logger, &index, 1 ) ) 
    {
        if ( ( index >= '0' ) && ( index <= '7' ) ) 
        {
            efuse7_set_limit ( &efuse7, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %c     \r\n", index );
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
