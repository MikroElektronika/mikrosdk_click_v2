/*!
 * \file 
 * \brief DualLin Click example
 * 
 * # Description
 * This example reads and processes data from Dual LIN clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, and sets bus.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - duallin_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "duallin.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

#define TEXT_TO_SEND "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITER

static duallin_t duallin;
static log_t logger;

static char current_rsp_buf[ PROCESS_RX_BUFFER_SIZE ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    duallin_cfg_t cfg;

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

    duallin_cfg_setup( &cfg );
    DUALLIN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    duallin_init( &duallin, &cfg );

    duallin_bus1_status( &duallin, DUALLIN_PIN_STATE_HIGH );
    duallin_bus2_status( &duallin, DUALLIN_PIN_STATE_LOW );
    Delay_ms( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    int32_t rsp_size = duallin_generic_read( &duallin, current_rsp_buf, PROCESS_RX_BUFFER_SIZE );
    if ( rsp_size> 0)
    {
        log_printf( &logger, "%s", current_rsp_buf );
    }
#endif    

#ifdef DEMO_APP_TRANSMITER
    duallin_send_command( &duallin, TEXT_TO_SEND );
    Delay_ms( 2000 );    
#endif
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
