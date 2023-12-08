/*!
 * @file main.c
 * @brief CurrentLimit6 Click example
 *
 * # Description
 * This library contains API for the Current Limit 6 Click driver.
 * This driver provides the functions to set the current limiting conditions 
 * in order to provide the threshold of the fault conditions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the Current Limit 6 Click board™.
 * Reading user's input from Usart Terminal and using it as an index 
 * for an array of pre-calculated values that define the current limit level.
 * Results are being sent to the Usart Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static void display_selection ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "currentlimit6.h"

static currentlimit6_t currentlimit6;
static log_t logger;
const float limit_value[ 9 ] = { 0.100, 0.200, 0.300, 0.400, 0.500, 0.600, 0.700, 0.800, 0.999 };

static void display_selection ( void ) 
{
    log_printf( &logger, " To select current limit  \r\n" );
    log_printf( &logger, " Send one of the numbers: \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - \r\n" );
    log_printf( &logger, " '1' - Limited to 100 mA  \r\n" );
    log_printf( &logger, " '2' - Limited to 200 mA  \r\n" );
    log_printf( &logger, " '3' - Limited to 300 mA  \r\n" );
    log_printf( &logger, " '4' - Limited to 400 mA  \r\n" );
    log_printf( &logger, " '5' - Limited to 500 mA  \r\n" );
    log_printf( &logger, " '6' - Limited to 600 mA  \r\n" );
    log_printf( &logger, " '7' - Limited to 700 mA  \r\n" );
    log_printf( &logger, " '8' - Limited to 800 mA  \r\n" );
    log_printf( &logger, " '9' - Limited to 999 mA  \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
}

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit6_cfg_t currentlimit6_cfg;  /**< Click config object. */

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
    currentlimit6_cfg_setup( &currentlimit6_cfg );
    CURRENTLIMIT6_MAP_MIKROBUS( currentlimit6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == currentlimit6_init( &currentlimit6, &currentlimit6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT6_ERROR == currentlimit6_default_cfg ( &currentlimit6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Current Limit 6 Click  \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    Delay_ms( 100 );
    
    display_selection( );
    Delay_ms( 100 );
}

void application_task ( void )
{ 
    static char index;
    
    if ( log_read( &logger, &index, 1 ) != CURRENTLIMIT6_ERROR ) 
    {
        if ( ( index >= '1' ) && ( index <= '9' ) ) 
        {
            currentlimit6_set_current_limit ( &currentlimit6, limit_value[ index - 49 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
            log_printf( &logger, " Current limit is %.3f A \r\n", limit_value[ index - 49 ] );
            log_printf( &logger, "--------------------------\r\n" );
            Delay_ms( 100 );
        } 
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "--------------------------\r\n" );
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
