/*!
 * \file 
 * \brief Key Lock 2 Click example
 * 
 * # Description
 * Keylock 2 Click carries antistatic process sealed keylock mechanism that
 * has three positions.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init.
 * 
 * ## Application Task  
 * Checks the current key position and logs the current position on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "keylock2.h"

// ------------------------------------------------------------------ VARIABLES

static keylock2_t keylock2;
static log_t logger;

uint8_t old_position = 1;
uint8_t key_position;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    keylock2_cfg_t cfg;

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

    keylock2_cfg_setup( &cfg );
    KEYLOCK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    keylock2_init( &keylock2, &cfg );
}

void application_task ( void )
{
    
    key_position = keylock2_get_position( &keylock2 );
    
    if ( old_position != key_position )
    {
        if ( key_position == KEYLOCK2_POSITION_1 )
        {
            log_printf( &logger, " -- FIRST position -- \r\n " );
        }
        else if ( key_position == KEYLOCK2_POSITION_2 )
        {
            log_printf( &logger, " -- SECOND position -- \r\n " );
        }
        else
        {
            log_printf( &logger, " -- THIRD position -- \r\n " );
        }
        old_position = key_position;
    }

    Delay_ms( 500 );
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
