/*!
 * \file 
 * \brief Touchkey2 Click example
 * 
 * # Description
 * This application is touch controller.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device and makes an initial log.
 * 
 * ## Application Task  
 * Checks if new data byte have received in rx buffer (ready for reading),
   and if ready than reads one byte from rx buffer, that show if and what key is pressed.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "touchkey2.h"

// ------------------------------------------------------------------ VARIABLES

static touchkey2_t touchkey2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey2_cfg_t cfg;

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

    touchkey2_cfg_setup( &cfg );
    TOUCHKEY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey2_init( &touchkey2, &cfg );
}

void application_task ( void )
{
    char tmp;

    tmp = touchkey2_generic_single_read( &touchkey2 );
    if( tmp == 0x00 )
    {
        log_printf( &logger, "   Key released\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x01 )
    {
        log_printf( &logger, "   Key A pressed\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x02 )
    {
        log_printf( &logger, "   Key B pressed\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x04 )
    {
        log_printf( &logger, "   Key C pressed\r\n" );
        log_printf( &logger, "------------------- \r\n" );
    }
    else if( tmp == 0x08 )
    {
        log_printf( &logger, "   Key D pressed \r\n" );
        log_printf( &logger, "------------------- \r\n" );
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
