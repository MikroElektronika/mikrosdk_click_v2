/*!
 * \file 
 * \brief FLAME Click example
 * 
 * # Description
 * This application detects fire.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Flame Click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flame.h"

// ------------------------------------------------------------------ VARIABLES

static flame_t flame;
static log_t logger;

static uint8_t flame_state = 0;
static uint8_t flame_state_old = 1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flame_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    flame_cfg_setup( &cfg );
    FLAME_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flame_init( &flame, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    flame_state = flame_check_status ( &flame );

    if ( ( flame_state == 1 ) && ( flame_state_old == 0) )
    {
        log_printf( &logger, "  ~  FLAME   ~ \r\n " );
       
        flame_state_old = 1;
    }

    if ( ( flame_state == 0 ) && ( flame_state_old == 1 ) )
    {
        log_printf( &logger, "   NO FLAME  \r\n " );
        flame_state_old = 0;
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
