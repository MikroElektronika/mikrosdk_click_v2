/*!
 * @file main.c
 * @brief CurrentLimit7 Click example
 *
 * # Description
 * This library contains API for the Current Limit 7 Click driver.
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
 * This example demonstrates the use of the Current Limit 7 Click board™.
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
#include "currentlimit7.h"

static currentlimit7_t currentlimit7;
static log_t logger;

// #define CURRENTLIMIT_MODE_250_mA_500_mA
#define CURRENTLIMIT_MODE_500_mA_2500_mA

const uint16_t limit_value_op[ 14 ] = 
{ 
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_510_mA, 
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_625_mA, 
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_860_mA, 
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1320_mA, 
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1450_mA,
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1550_mA,
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1750_mA,
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2020_mA,
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2260_mA,
    CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2500_mA,
    CURRENTLIMIT7_OP_0_CURRENT_LIMIT_260_mA, 
    CURRENTLIMIT7_OP_0_CURRENT_LIMIT_280_mA, 
    CURRENTLIMIT7_OP_0_CURRENT_LIMIT_330_mA, 
    CURRENTLIMIT7_OP_0_CURRENT_LIMIT_450_mA
};

static void display_selection ( void ) 
{
    log_printf( &logger, "  To select current limit  \r\n" );
    log_printf( &logger, "  Send one of the numbers: \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
#ifdef CURRENTLIMIT_MODE_250_mA_500_mA
    log_printf( &logger, "  '0' - Limited to 260 mA  \r\n" );
    log_printf( &logger, "  '1' - Limited to 280 mA  \r\n" );
    log_printf( &logger, "  '2' - Limited to 330 mA  \r\n" );
    log_printf( &logger, "  '3' - Limited to 450 mA  \r\n" );
#else
    log_printf( &logger, " '0' - Limited to  510 mA  \r\n" );
    log_printf( &logger, " '1' - Limited to  625 mA  \r\n" );
    log_printf( &logger, " '2' - Limited to  860 mA  \r\n" );
    log_printf( &logger, " '3' - Limited to 1320 mA  \r\n" );
    log_printf( &logger, " '4' - Limited to 1450 mA  \r\n" );
    log_printf( &logger, " '5' - Limited to 1550 mA  \r\n" );
    log_printf( &logger, " '6' - Limited to 1750 mA  \r\n" );
    log_printf( &logger, " '7' - Limited to 2020 mA  \r\n" );
    log_printf( &logger, " '8' - Limited to 2260 mA  \r\n" );
    log_printf( &logger, " '9' - Limited to 2500 mA  \r\n" );
#endif        
    log_printf( &logger, "---------------------------\r\n" );
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit7_cfg_t currentlimit7_cfg;  /**< Click config object. */

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
    currentlimit7_cfg_setup( &currentlimit7_cfg );
    CURRENTLIMIT7_MAP_MIKROBUS( currentlimit7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit7_init( &currentlimit7, &currentlimit7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT7_ERROR == currentlimit7_default_cfg ( &currentlimit7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "   Current Limit 7 Click   \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
    
#ifdef CURRENTLIMIT_MODE_250_mA_500_mA
    currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_250_mA_500_mA, limit_value_op[ 10 ] );
    log_printf( &logger, "  >>> Selected mode %d     \r\n", 0 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Current limit is %d mA    \r\n", limit_value_op[ 10 ] );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
#else
    currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_500_mA_2500_mA, limit_value_op[ 0 ] );
    log_printf( &logger, "  >>> Selected mode %d     \r\n", 0 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Current limit is %d mA    \r\n", limit_value_op[ 0 ] );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
#endif
    
    display_selection( );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static char index;
    
    if ( CURRENTLIMIT7_ERROR != log_read( &logger, &index, 1 ) ) 
    {
    #ifdef CURRENTLIMIT_MODE_250_mA_500_mA
        if ( ( index >= '0' ) && ( index <= '3' ) )
        {
            currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_250_mA_500_mA, limit_value_op[ index - 38 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 38 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms( 100 );
        }
    #else
        if ( ( index >= '0' ) && ( index <= '9' ) ) 
        {
            currentlimit7_set_current_limit ( &currentlimit7, CURRENTLIMIT7_OP_MODE_500_mA_2500_mA, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 48 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms( 100 );
        }
    #endif
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "---------------------------\r\n" );
            display_selection( );
            Delay_ms( 100 );
        }
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
