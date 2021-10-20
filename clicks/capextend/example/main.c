/*!
 * \file 
 * \brief CapExtend Click example
 * 
 * # Description
 * This example showcases the initialization and configuration of the logger and click modules
 * and later on shows how to read and display the 16-bit button map ( LSB + MSB ).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules.
 * 
 * ## Application Task  
 * This function collects map data and displays the 16-bit button map, where each bit that has
 * the value 1 represents a button that has been pressed.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "capextend.h"

// ------------------------------------------------------------------ VARIABLES

static capextend_t capextend;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    capextend_cfg_t cfg;

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

    capextend_cfg_setup( &cfg );
    CAPEXTEND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capextend_init( &capextend, &cfg );
    capextend_reset( &capextend );
}

void application_task ( )
{
    uint16_t buttons = 0;

    buttons = capextend_read_buttons( &capextend );


    log_printf( &logger, " * ---------BUTTTONS--------- * \r\n" );
    
    for ( uint8_t counter = 0; counter < 12; counter++ )
    {
        if ( ( buttons >> ( 11 - counter ) ) & 1 )
        {
            log_printf( &logger, " * " );
        }
        else
        {
            log_printf( &logger, " o " );
        }
    }

    log_printf( &logger, "\r\n * ------------------------------- * \r\n\r\n" );
    Delay_ms( 500 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
