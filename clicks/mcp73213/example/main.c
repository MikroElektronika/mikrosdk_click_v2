/*!
 * \file 
 * \brief Mcp73213 Click example
 * 
 * # Description
 * This application is polymer battery charge management controller.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI, also write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of MCP73213 Click board.
 * This example sets the resistance to a given value, thus affecting the output current.
 * Controls output current using internal digital potentiometer.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 3 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp73213.h"

// ------------------------------------------------------------------ VARIABLES

static mcp73213_t mcp73213;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp73213_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp73213_cfg_setup( &cfg );
    MCP73213_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp73213_init( &mcp73213, &cfg );

    log_printf( &logger, "   SPI Driver Init     \r\n" );
    Delay_ms( 3000 );
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "  Set Current Output   \r\n" );
}

void application_task ( void )
{
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "   10 kOhm - 130 mA    \r\n" );
    mcp73213_set_current_output( &mcp73213, MCP73213_OUTPUT_130_mA );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---------------------- \r\n" );
    log_printf( &logger, "    5 kOhm - 250 mA    \r\n" );
    mcp73213_set_current_output( &mcp73213, MCP73213_OUTPUT_250_mA );
    Delay_ms( 5000 );
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
